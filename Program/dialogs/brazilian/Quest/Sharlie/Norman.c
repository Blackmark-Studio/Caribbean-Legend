// Абрахам Норман
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Precisa de alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("O que você quer? Siga seu caminho, cuide da sua vida. Só me deixe em paz.","Ei, ei, camarada. Vai dar uma volta? Então continue andando e deixe o senhor Abraham em paz. Ele também está dando uma volta. Só está pegando um pouco de ar fresco do mar.","Olá, amigo. Quer bater um papo? Só tem um problema: não estou com vontade de conversar. Então vá procurar outra pessoa para incomodar. Vai relaxar na taverna. Toma um rum...");
				link.l1 = "Escuta, Abraham, por acaso você encontrou um homem chamado Miguel Dichoso recentemente na Isla Tesoro? Ele é meio conhecido por aqui.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("O que você quer? Siga seu caminho, cuide da sua vida. Só me deixe em paz.","Ei, ei, camarada. Vai dar uma volta? Então continue andando e deixe o senhor Abraham em paz. Ele também está dando uma volta. Só quer sentir um pouco do ar fresco do mar.","Olá, camarada. Quer bater um papo? Só tem um problema: não estou com vontade de conversar. Então vai incomodar outro. Vai relaxar na taverna. Toma um rum..."),LinkRandPhrase("Ei, marinheiro. O quê, você é cabeça-dura ou algo assim? Achei que tinha sido bem claro.","Amigo, vai descansar um pouco. Você parece estar meio surdo.","Ei, camarada, você é burro ou o quê? Já deixei tudo bem claro pra você."),"Amigo, não me faça perder a paciência. Já mandei tantos marinheiros de primeira viagem pro inferno que um a mais ou a menos não faz diferença nenhuma.","Certo, você me irritou de verdade. Agora ou saca essa sua espada enferrujada, ou corre o mais rápido que puder. Eu recomendo a segunda opção...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudo bem, amigo. Não vou te incomodar.","Tá bom, tá bom. Já entendi...","Opa, olha, você parece ser o trovão dos mares! Tá bom, tô saindo daqui.","O quê?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("O que você quer, rapaz? Vai cuidar da sua vida. Só me deixa em paz.","Ei, ei, camarada. Vai dar uma volta? Então continue andando e deixe o senhor Abraham em paz. Ele também está dando uma volta. Só está pegando um pouco de ar fresco do mar.","Olá, camarada. Quer bater um papo? Só tem um problema: não estou com vontade de conversar. Então vai incomodar outro. Vai relaxar na taverna. Toma um rum...");
				link.l1 = "Escuta, Abraham, por acaso você encontrou um homem chamado Miguel Dichoso na Isla Tesoro recentemente? Ele é uma figura bem conhecida por aqui.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Parado! Eu sou o governador desta ilha. O quê, não acredita em mim?!";
					link.l1 = "Claro que conheço! Quem não conhece o governador de Isla Tesoro...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, se chama de almirante também, que aí eu compro mesmo!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Atenção! Vejam só - Almirante Barbarigo! Não reconhece minha famosa espada de cavalaria?";
					link.l1 = "Me desculpe, Almirante! De agora em diante, vou prestar mais atenção.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Sua espada de cavalaria é bem conhecida. Pena que está nas mãos de um tolo.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Como pode ver, estou aqui no exílio. Aguardo novas instruções do General Monck. Peço que não revele minha identidade real oculta. A inteligência de Cromwell tem ouvidos atentos.";
					link.l1 = "Mas é claro, Majestade. Ninguém jamais saberá que Karl II está escondido nas Índias Ocidentais.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Bom, então eu sou o Papa Inocêncio X.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "O que aconteceu com você, Blaze? Estou te procurando há dois dias. Você esqueceu completamente do seu pai, Nicolas!";
					link.l1 = "Não tenho tempo para você, pai! Estou atolado.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "O senhor está enganado. Meu nome é "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Sh-sh... Eu sou Davy Jones. Me diga, você tem medo da morte?";
					link.l1 = "Claro que estou, Sr. Jones. Principalmente depois de uma ressaca.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Uma morte é uma tragédia, mil mortes são apenas uma estatística.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Estou com pressa para terminar minha nova peça. Você precisa me ajudar a completar a frase 'Ser ou não ser'?!";
					link.l1 = "Essa é a questão! Devemos suportar a ofensa e seguir em frente...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Uma bebida, com certeza. Mas não me surpreenderia se eu pegasse uma doença num bordel!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "O que diabos você está falando? 'Tesoro'?! Você podia muito bem chamar de Bermudas! Esta ilha se chama Ilha Norman por minha causa, e não se esqueça disso! Acho que vou ter que te ensinar geografia...";
			link.l1 = "Hã! Como assim?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Você está certo, marinheiro. Eu sou mesmo o Almirante Barbarigo, mas isso fica só entre nós. Prepare-se para marchar. Vamos partir em breve. Isso vai ser útil para você.";
			link.l1 = "Estou extremamente agradecido!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Vamos ver quem é o tolo agora. Em guarda!";
			link.l1 = "Você está falando sério?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "O que eu te disse! Aqui, beba à minha saúde.";
			link.l1 = "Saúde, Almirante!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Eu pedi pra você não espalhar meu nome! Agora vou ter que me livrar de você como uma testemunha perigosa...";
			link.l1 = "Ah, eu estava esperando por isso!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Perdoe-me, sua Graça! Não o reconheci com essas roupas. Por favor, aceite este modesto presente de um verdadeiro católico.";
			link.l1 = "A insanidade se manifesta...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Todo mundo está atrás de mim! Peguei um espião que é a cara do meu filho! Tenho certeza de que foi o Thomas que mandou ele pra arrancar meu outro olho!";
			link.l1 = "Cai fora, seu idiota!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Você está cansado e não parece muito bem, garoto. Vai lá e procura um médico.";
			link.l1 = "Obrigado!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Não tenha medo, amigo. Viu só? Morrer não é assustador nem um pouco...";
			link.l1 = "Parece que você não estava brincando!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Aparentemente você não tem medo. Eu sabia. Isso é coragem!";
			link.l1 = "Você é um velho engraçado...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Você é um poeta péssimo, Marinheiro. Será que sua espada é mais ágil que sua língua?";
			link.l1 = "Caramba! Essa sua espada de cavalaria não é de brincadeira mesmo!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Droga! As coisas têm dado muito certo pra você! Que tal isso pra sua imaginação!";
			link.l1 = "Volte sempre.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, eu reconheço você! Ha-ha!";
			link.l1 = "De novo...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "Tá certo, camarada, já conversamos. Agora pode ir.";
			link.l1 = "Como você disser...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso? Pra que você precisa dele, hein?";
			link.l1 = "Bem, eu preciso dele. Eu simplesmente preciso dele. Então, você o viu?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Como assim, pra que eu preciso dele? Miguel é um velho camarada meu, dá pra dizer que é um amigo. Ele deveria...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Quero que ele consiga um novo navio pra mim, do mesmo jeito que fez uma vez pro Tubarão Dodson.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso matou um homem. É por isso que estou procurando por ele.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Você só precisa dele... Você só precisa dele! Tudo o que você precisa é do Miguel Dichoso! Não, eu não o vi. Faz muito tempo que não vejo ele. Não posso te ajudar em nada, Marinheiro.";
			link.l1 = "Hm... Tudo bem, tchau.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Um amigo, é o que você diz... Parece que ele colecionou uma porção de amigos. Está prestes a ficar com um a menos...";
			link.l1 = "E aí, velho. O que aconteceu com você?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Sim, Dichoso é um mestre nesses ofícios, não importa como você veja. Mas eu não sei onde ele está. Ele apareceu por aqui, mas já foi embora. Então vá até o Alexus, Marinheiro. Ele vai montar um belo barco pra você.";
			link.l1 = "Hum... Valeu pela dica, amigo.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "Então quem foi que o Dichoso eliminou pra você estar no encalço dele, hein, camarada?";
			link.l1 = "Blaze Sharp";
			link.l1.go = "tieyasal_5_1";
			link.l2 = "Nicolas Sharp";
			link.l2.go = "tieyasal_5";
			link.l3 = "Alonso de Maldonado";
			link.l3.go = "tieyasal_5";
			link.l4 = "O Papa";
			link.l4.go = "tieyasal_5_bud_joke";
		break;

		case "tieyasal_5_1":
			dialog.text = "Shhh... (olha em volta) Então você também acha que o Dichoso matou o Blaze Sharp?";
			link.l1 = "É. E não é só um palpite — eu tenho provas. Anotações no diário de bordo...";
			link.l1.go = "tieyasal_6"
		break;

		case "tieyasal_5_bud_joke":
			dialog.text = "Então agora estamos fazendo piada? Nenhum respeito mesmo! Vamos, chegue mais perto...";
			link.l1 = "De jeito nenhum.";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_5":
			dialog.text = "Ah... Bem. Ele matou o sujeito e é isso. Sabe quantos assassinos andam por aqui? Quase todo homem! Não, Marinheiro. Faz tempo que não vejo o Dichoso. Não posso te ajudar com nada.";
			link.l1 = "Pena...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Fique quieto, camarada. Qual é o seu nome, hein? Parece que me escapou da memória...";
			link.l1 = "Capitão "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Escute, "+pchar.name+". Dichoso matou o pobre Blaze. Eu vi com meus próprios olhos, sim-sim. Mas eles não acreditam em mim. Sabe, acham que eu sou louco. Um dos deles, mas louco. E eu já fui o melhor oficial de abordo da tripulação do próprio Nicolas Sharp! Bons tempos! Mas, no fim, perdi minhas garras, casco e lente, e fiquei preso em terra.\nO quê? Ah, claro! Todos achavam que a culpa era do Shark, mas não era. Não, não, não. Havia um dente de tubarão, um talismã do Dodson, mas foi o Dichoso quem colocou aquilo lá.\nEle deve ter roubado do Shark quando navegavam juntos numa fragata chamada Fortune. Naquele dia, não dormi direito e saí para dar uma volta. Vi o Dichoso entrando de fininho na casa do Sharp, ouvi alguém gritar e depois gemer. Logo depois, Dichoso saiu da casa com as mãos cobertas de sangue.\nNinguém acreditou em mim, não, não. Porque naquele dia não havia nenhum Dichoso na ilha, mas o Shark estava. E encontraram o dente dele. Mas eu vi o Dichoso, tenho certeza. Ninguém sabia que ele estava lá naquele dia. 'O Sortudo' é um homem muito astuto e perigoso...";
			link.l1 = "Você não é o primeiro a chamar o Dichoso de 'Sortudo'. Por quê? Esse é o apelido dele?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Você não sabe espanhol, rapaz? 'Dichoso' quer dizer 'sortudo' na língua dos papistas. Miguel Sortudo, Miguel o Sortudo. É isso que significa o nome dele.";
			link.l1 = "Miguel, o Sortudo?... Hm. Isso me lembra alguma coisa. Hm. Essa frase me soa tão familiar...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Bem, mesmo que o sobrenome dele seja Dichoso, ainda assim não acho que ele seja espanhol. Não, não. Ele não é espanhol. Embora pareça espanhol.";
			link.l1 = "Então o que ele poderia ser? Inglês, francês?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Não é disso que estou falando, Marinheiro... Ah, me perdoe, Capitão. Sim, Dichoso fala francês de forma impressionante, tão bem quanto você. E também domina o inglês. Mas corre sangue indígena nas veias dele. Já vi muita gente assim na minha vida. Não é fácil perceber, mas ele é mestiço. Eu te garanto.";
			link.l1 = "Ele fala a língua nativa?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Ah, sei lá. Talvez saiba. Espera, sabe sim! Ele vivia soltando umas frases estranhas numa língua esquisita, fazia uma cara de sábio assustador e estufava as bochechas enquanto falava. Por exemplo, dizia algo tipo: cogito ergo sum! Aí revirava os olhos e ficava olhando a reação dos marinheiros. Ou então exclamava assim: aut Caesar, aut nihil! Ele soltava várias outras coisas também. Não lembro de tudo que ele falava.";
			link.l1 = "Isso não é uma língua indígena. Isso é latim. Latim... Latim?! Puta merda!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Por que esse susto todo, homem? Pra que tanto grito? Foi picado por uma cobra, é isso? Pra onde ela foi?";
			link.l1 = "Como eu não percebi isso desde o começo! Estava tudo bem diante dos meus olhos! Latim! Miguel... Miguel, o Sortudo!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Ei, camarada. Pode parar de gritar, por favor? Todo mundo está olhando pra gente. O que foi que te mordeu, Marinheiro... digo, Capitão?";
			link.l1 = "Eu sei quem Miguel Dichoso realmente é. Ele não é espanhol. Ele é francês! Ah, como fui cego!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Que nada, seu bobo. Ele não é francês. É mestiço. O pai branco dele se deitou com uma índia, dessas Arawak ou Miskito do Caribe, ou talvez até uma Itza, e foi assim que o santo Miguel Dichoso veio ao mundo. Você não percebe, mas eu vejo. Está escrito nos olhos dele...";
			link.l1 = "Vamos deixar a questão da origem dele de lado por um instante. Onde ele está, Abraão?! Ele esteve aqui?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Sh-sh... Sim, ele esteve aqui. Mas já foi embora. Ele não está mais na Isla Tesoro.";
			link.l1 = "Por que ele veio aqui? Que tipo de navio ele tem?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "O navio dele é um galeão. Um grande galeão de guerra. O que ele veio fazer aqui... Bem, ele estava fuçando, fazendo perguntas. Mas eu ouvi as conversas dele, sim, sim! Ele estava procurando por um tal de Charles de Maure. Isso mesmo. Charles de Maure. Espera, esse é você, Charles de Maure! Ele estava atrás de você, rapaz.";
			link.l1 = "Você sabe para quê?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Bom, com certeza não era para visitar a taverna e tomar um rum com você. Ele estava planejando te capturar. Isso mesmo, te capturar! Você está encrencado até o pescoço, capitão!";
			link.l1 = "Eu não duvido...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "E você? Por que está procurando por ele? Ah, já entendi, já entendi: para matá-lo! Mata ele, mata esse desgraçado! Vingue o Blaze Sharp! Blaze era um cara incrível. Eu me lembro dele, mesmo quando criança ele já era igual ao Nicholas.";
			link.l1 = "Onde foi parar o Dichoso?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Ele estava a caminho de Blueweld. Disse que Charles de Maure deve ser procurado sob a proteção do Diabo da Floresta. Mas deixou seus homens aqui... Espere. Acho que você já foi visto!";
			link.l1 = "Quem reparou em mim?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Os homens do Dichoso. Ele mandou eles ficarem de olho em você aqui. Ah, eu sei, eu sei! Fique atento, capitão: os recifes da Isla Tesoro estão cercados de navios e estão lá esperando pela sua cabeça. O capitão é astuto como uma raposa. Não se deixe enganar.";
			link.l1 = "Vou tentar...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "E mais uma coisa: aqui, pegue minha espada de cavalaria. Pegue, pegue. Você vai precisar. Esta é a própria espada do Capitão Barbarigo. É uma lâmina excelente. A melhor do arquipélago. Não tenha vergonha, pegue. Blaze Sharp será vingado!";
			link.l1 = "Obrigado, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Vá agora. Vá, estão te observando. Finja que é esperto. Ou tolo. Tanto faz. Só tome cuidado!";
			link.l1 = "Valeu, amigo. Você nem imagina o quanto me ajudou. Boa sorte!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
