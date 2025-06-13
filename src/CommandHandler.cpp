#include "../includes/CommandHandler.hpp"

// NICK: atualiza nickname do cliente
// USER: armazena info do usuário
// JOIN: adiciona cliente a canal (criar canal se não existir)
// PRIVMSG: envia mensagem para o cliente ou canal alvo

// por parte do operador:
// KICK: remove um client do canal
// INVITE: permite convidar um user para canal
// TOPIC: define o tópico do canal
// MODE: define o modo
    // i: canal com entrada por INVITE
    // t: o tópico do canal só pode ser modificado pelo operador
    // k <senha>: o user precisa de senha para aceder canal
    // o <username>: garante privilegios de operador
    // l <n>: define limite de users

CommandHandler::CommandHandler() {
    _commands["PASS"] = new PassCommand();
    _commands["NICK"] = new NickCommand();
    _commands["USER"] = new UserCommand();
    _commands["JOIN"] = new JoinCommand();
    // _commands["PART"] = new PartCommand();
    _commands["PRIVMSG"] = new PrivmsgCommand();
    //_commands["PING"] = new PingCommand();
    // _commands["QUIT"] = new QuitCommand();
    // _commands["LIST"] = new ListCommand();
    // _commands["NAMES"] = new NamesCommand();
    // _commands["KICK"] = new KickCommand();
    // _commands["INVITE"] = new InviteCommand();
    // _commands["TOPIC"] = new TopicCommand();
    // _commands["MODE"] = new ModeCommand();
}

CommandHandler::~CommandHandler() {
    for (std::map<std::string, ACommand*>::iterator it = _commands.begin(); it != _commands.end(); ++it) {
        delete it->second;
    }
}

void CommandHandler::handle(Server &server, Client &client, const std::string &line) {
    std::vector<std::string> args = split(line);
    if (args.empty()) {
        return;
    }

    std::map<std::string, ACommand*>::iterator it = _commands.find(args[0]);

    if (it != _commands.end()) {
        it->second->execute(server, client, args);
    }
    else {
        sendMessage(client.getFd(), "421 " + args[0] + " : Unkown command\n");
    }
}