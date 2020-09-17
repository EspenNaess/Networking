#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <boost/asio.hpp>

#include "templatmetaprogrammering.hpp"
#include "boost_client.hpp"

Klient::Klient(boost::asio::io_service & io_service, tcp::resolver::iterator adresseitr) :
io_serv(io_service), socket(io_service), buffer(25) {
  opprett_kobling(adresseitr);
}

void Klient::skriv_data(string data) {
  boost::asio::async_write(socket, boost::asio::buffer(data),
    [this](boost::system::error_code ek, size_t) {
      if (ek) {
        throw "Error code: "+to_string(ek.value());
      }
    });
}

void Klient::opprett_kobling(tcp::resolver::iterator itr) {
  boost::asio::async_connect(socket, itr,
    [this](boost::system::error_code ek, tcp::resolver::iterator) {
      if (!ek) { // koplet til
        // kjør les/skriv operasjoner til socketen
        les_data();
      } else {
        cout << ek.message() << endl;
      }

    });
}

void Klient::les_data() {
  boost::asio::async_read(socket,
  boost::asio::buffer(buffer),
  [this](boost::system::error_code ek, size_t) {
    if (ek) {
      cout << ek.message() << endl;
    }
    cout << "mottatt melding: ";
    for (char t : buffer) {
      cout << t;
    } cout << endl;
  });
}

int main(int argc, char const *argv[]) {
  // objekt som blir brukt til å kjøre alle asynkrone operasjoner
  boost::asio::io_service io_serv;

  // DNS lookup, gir iterator med tilkoplingsmulighetene til klientobjektet
  tcp::resolver DNSl(io_serv);
  auto itr = DNSl.resolve({"127.0.0.1", "7864"});
  Klient k{io_serv, itr};

  // oppretter beskjed
  bool er_int_i_typesettet = er_i_typesettet<int, short, long, double, float>::resultat;

  string beskjed = er_int_i_typesettet ? "Heisann! Typesettet inneholdt en int" : "Heisann! Typesettet inneholdt ikke en int";

  thread t([&io_serv](){
    io_serv.run();
  });

  k.skriv_data(beskjed);

  t.join();
  return 0;
}
