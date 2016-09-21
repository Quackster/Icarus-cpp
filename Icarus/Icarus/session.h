class session
{
public:
	session(sessionConnection session_connection);
	~session();

private:
	sessionConnection &session_connection;
};