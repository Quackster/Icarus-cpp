class session
{
public:
	session(sessionConnection session_connection);
	~session();
	void disconnected();

private:
	sessionConnection &session_connection;
};