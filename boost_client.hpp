class Klient {
public:
  Klient(boost::asio::io_service & io_service, tcp::resolver::iterator adresseitr);
  void skriv_data(string data);

private:
  void opprett_kobling(tcp::resolver::iterator itr);
  void les_data();

  boost::asio::io_service& io_serv;
  tcp::socket socket;
  vector<char> buffer;
};
