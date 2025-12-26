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
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Bug. Avisem os desenvolvedores.";
		link.l1 = "Claro.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, outro marinheiro corajoso! Eu conheço o seu tipo, meu olho maldito está de olho em você, ha! Sabe por quê?";
			link.l1 = "Vou lhe perguntar sobre outro assunto, é sobre a dívida que você tem com a dona do... hmm, estabelecimento local. Ela me pediu para lembrá-lo dessa dívida, então sugiro que faça algo a respeito, senão ela vai pedir aos guardas para fazerem o mesmo amanhã.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Local está... ah, merda! Johanna, ela não pode fazer isso comigo! Tem certeza? Ela realmente disse que ia me mandar para as masmorras por algumas malditas moedas?";
			link.l1 = "Com certeza. Foi isso mesmo que ela disse. Acho que minha missão terminou, adeus, senhor Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Espere! Por favor, espere! Você parece um capitão experiente. Com certeza tem algumas moedas, eu estou quebrado, só o bom e velho barman ainda me serve fiado por causa da nossa antiga amizade. Ouça a minha pro... proposta! Você paga minha dívida e eu te dou uma parte\nTem um negócio... um negócio muito lucrativo, que o diabo me leve! Juro pela minha âncora maldita, só confie em mim, capitão – seja lá qual for seu nome!\nBasta quitar uma pequena dívida, dez mil pesos, e você vai ter a chance de ganhar moedas suficientes pra comprar todos os bordéis do Novo-maldito-Mundo! O que me diz? Você me ajuda, eu te ajudo, como gente honesta faz...";
			link.l1 = "Um sujeito esfarrapado prometendo tesouros. Poupe-me dessa bobagem, não faço caridade para gente como você. Arranje o dinheiro ou logo vai acabar nas casamatas do forte. Adeus!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Uma parte? E por que eu deveria confiar na palavra de um bêbado? Por causa de promessas inventadas?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Escute aqui, capitão! Hic, pode me matar se eu estiver mentindo! Mas estou falando a verdade! Pensa bem, se me pegar mentindo, pode arrancar minhas tripas com essa beleza que você carrega no cinto! Droga, o cabo dela vale cinco vezes mais que a minha dívida miserável! E então, o que me diz? Você não tem nada a perder!";
			link.l1 = "Já cansei dos seus discursos. Adeus.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Tá bom, Hugo... Vou arriscar acreditar nessa história que você conta. Mas lembre-se, você vai ter que me convencer e garantir que meu dinheiro não foi jogado fora quando eu voltar, senão é o seu pescoço que está em jogo.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Não precisa ameaçar, eu entendi. Dou minha palavra, capitão! Vamos ficar ricos! Volte quando essa maldita dívida estiver paga e nós v... vamos conversar! Sim, vamos! Você não vai ser deixado de lado!";
			link.l1 = "Certo, vou apagar sua dívida, mas é bom rezar, Hugo Avendell, para que sua 'proposta' me agrade.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Capitão, volte o mais rápido que puder – esse negócio pode escapar.";
			link.l1 = "Sim, sim, vou pagar sua dívida em breve.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Você voltou, capitão! Pela tempestade e pelo trovão de Deus, que alegria te ver! E a minha dívida?";
			link.l1 = "Já resolvi a minha parte, agora é sua vez, Hugo. Conte sua história e tente fazer com que pareça pelo menos um pouco crível!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Não se preocupe, capitão! Sabia que eu sou um caçador de recompensas? Ou melhor... eu era. Acho que não tive sorte o bastante. Talvez até o próprio Diabo, com todas as suas maldades, não tenha sido tão azarado quanto eu. Perdi tudo no meu último trabalho... A tripulação me abandonou e tive que vender meu navio por causa das dívidas...";
			link.l1 = "Já estou informado sobre o seu passado heroico. Vamos direto ao assunto, Hugo, não teste a minha paciência.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Sim, sim, capitão..."+GetFullName(pchar)+", não é mesmo? Eu também sei uma ou duas coisas sobre você. Mas que se dane se isso importa. Já ouviu falar de Bartolomeu, o Português?";
			link.l1 = "Bart, o Português? Claro que já ouvi falar dele. Todo mundo já ouviu. Ele é pirata, carniceiro e, pelo que sei, um verdadeiro canalha. E que papel ele tem na sua história?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Ele está desempenhando um papel enorme nisso! Estou caçando esse desgraçado há um ano e meio. A Companhia Holandesa colocou uma bela recompensa pela cabeça dele. Mas eu falhei, perdi tudo. E a Companhia triplicou a recompensa por ele recentemente—vivo, e só vivo, maldito seja!";
			link.l1 = "Com razão, não é nada fácil capturá-lo vivo. Mas afinal, por que eu deveria me importar com isso, Hugo? Parece até que você está tentando me passar a perna!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Eu nem ia fazer isso, capitão! Sabe, o médico daqui, Peter Van Stal, um homem muito gente boa, me deu uma poção pra curar minhas dores de cabeça! Então, o doutor ficou fora de casa por quase três dias e...";
			link.l1 = "Hugo, minha paciência está quase no fim! Prometi à dama que não te furaria com minha lâmina, mas meus punhos vão servir muito bem! Juro que amanhã nem poção vai dar jeito na sua cabeça!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Espere, capitão! Por favor! Me escute, eu vi alguns homens perto da casa do doutor e os reconheci. Eles são do 'Albatross', uma fragata dos malditos portugueses! E um deles estava falando sobre a saúde do capitão deles! Olhe agora, "+pchar.name+", Bartolomeo está aqui, nesta cidade! Bem debaixo dos nossos narizes, ele está ferido ou doente, por isso precisam de um maldito médico!\nDuvido que o português tenha trazido toda a tripulação, mas não posso começar essa confusão sozinho! Você sabe muito bem como manejar essa sua espada maldita! Leve alguns homens fortes com você e vamos encontrar esse rato! Depois, capturamos ele e entregamos às autoridades!\nE dois mil bons dobrões de ouro vão para os nossos bolsos!";
			link.l1 = "Não, Hugo, já cansei das suas conversas. Não vou me meter nessa confusão, mesmo que você esteja certo. Adeus.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, interessante. Você sabe onde ele está se escondendo? Se der certo, podemos conversar sobre as partes, mas se o que você está dizendo for verdade, então precisamos nos apressar agora!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Não, eu não sei onde ele está, capitão. Fiquei com medo demais pra ir atrás daqueles caras. Se o Caolho tivesse me visto... vixe! Mas juntos, com seus homens, a gente consegue vasculhar essa cidade inteira, chame sua tripulação e vamos começar! Droga, os dobrões holandeses estão esperando por nós! Uma chance dessas só aparece uma vez na vida, pode apostar!";
			link.l1 = "Um entusiasmo admirável... Espero que consiga sair da mesa, 'grande' caçador de recompensas. Vou começar a procurar agora mesmo, e você pode me seguir se quiser—só não atrapalhe demais.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Sim, sim, capitão, só me deixe terminar minha bebida e já vou com você... Por onde começamos?";
			link.l1 = "Onde?!... Eu vou, com ou sem você.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Casa errada, camarada. Cai fora, agora!";
			link.l1 = "Hum. E eu acho que esta é a casa certa...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Bem, eu te avisei...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Cheios e firmes, voando alto, filhos de... preparem os canhões!... ah-ha-ha... ah, minha beleza...";
			link.l1 = "Hmm, ele teve sorte de sair vivo...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Meu Deus, quem é você? Por favor, abaixe sua arma! Tem um homem doente aqui!";
			link.l1 = "Esse 'doente' aí já matou mais gente do que você viu na vida, doutor. Cai fora!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "Ele é meu paciente e mal consegue ficar de pé! Não está vendo? Por favor, abaixe sua espada! Eu lhe imploro!";
			link.l1 = "E o que há de errado com ele, caramba!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Eu acho que é tudo por causa do ferimento dele, um golpe de uma arma envenenada dos caribes... e os homens que o trouxeram aqui disseram que, se ele morrer, eu também morro! Mas estou fazendo tudo o que posso, diga isso a eles!";
			link.l1 = "Não se preocupe com esses homens, doutor. Meus rapazes vão ficar de olho na sua casa e eu preciso ir ver o governador. Aposto que ele vai se mijar de alegria. Não saia daqui até eu voltar, doutor.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Eu não vou embora, pode ficar tranquilo quanto a isso. Vamos logo entregá-lo às autoridades e acabar com esse pesadelo.";
			link.l1 = "Claro, estou a caminho.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Conseguimos, capitão! Encontramos ele e logo estaremos ricos, como eu te disse! Qual é o nosso plano?";
			link.l1 = "Espero que sim, Hugo. De qualquer forma, ainda não acabou. Acho que preciso ir até o governador e discutir nossa recompensa?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Não, não, capitão! Não vá até aquele maldito Thomas! Acredite, esse canalha vai tomar nosso prisioneiro e, com sorte, só vai nos oferecer uma xícara de café! Sua Excelência é um sujeito escorregadio, então se quiser receber toda a recompensa, tem que navegar até Curaçao! Caso contrário, os portugueses vão levar o prisioneiro para o forte e a gente vai ser enxotado feito mendigo!";
			link.l1 = "Bem, se você tem mesmo certeza disso...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Eu sou, capitão, tenho certeza disso, por Deus! Mas lembre-se que os homens do Bartolomeo devem estar em algum lugar da cidade e também não queremos chamar a atenção da guarnição, isso é certo! Precisamos decidir como levar o português até o seu navio e como fazer isso sem sermos notados.";
			link.l1 = "Tá bom... Não quero enfrentar a fragata dele a caminho de Willemstad. Tem alguma ideia?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Sim, eu tenho uma ideia. Primeiro precisamos arrumar uma roupa mais nobre pra ele, depois o levamos pela entrada dos fundos fingindo ser um oficial bêbado! Ninguém vai suspeitar que ele é um maldito pirata, pode confiar!";
			link.l1 = "Hum, não tenho certeza disso, mas ainda não temos um plano melhor. Vou tentar conseguir um bom tecido para o nosso passageiro. Fique aqui e cuide do Bart e do doutor.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Não se preocupe, capitão. O português está sob minha guarda confiável, he-he...";
			link.l1 = "Eu gostaria de acreditar que...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Não vejo os soldados, "+GetAddress_Form(NPChar)+". Onde eles estão? Você disse que ele seria preso assim que você contasse a situação para eles. Então por que os soldados ainda não chegaram?";
			link.l1 = "Não haverá soldados, senhor Van Stal. Eu mesmo vou cuidar disso e preciso levar seu paciente para Curaçao o quanto antes.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Capitão, escute, eu não consigo cuidar do ferimento dele, só posso baixar um pouco a febre. Ele está quase sempre inconsciente e delirando, não há dúvida de que vai morrer mesmo sem qualquer interferência, e o balanço do mar vai acabar com ele em poucos dias. Vou lhe dar algumas misturas que podem ajudar...";
			link.l1 = "Não, doutor, você vai navegar conosco. Primeiro, eu sou péssimo com medicina, e segundo, duvido que queira ficar aqui e explicar para os portugueses onde foi parar o capitão deles?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Sim, acho que você tem razão. Mas saiba que esse pirata é muito resistente. Já vi gente com ferimentos leves de armas indígenas, e todos morreram em menos de três dias. E, segundo os 'amigos' dele, ele está assim há uma semana! Mesmo assim, mantenho que ele só vai aguentar pouco tempo num navio em alto-mar. Três dias, não mais!  É todo o tempo que temos.";
			link.l1 = "Nem um pássaro conseguiria chegar a Curaçao em três dias. Mas acho que sei o que posso fazer! Tenho um... amigo, ele mora em St. John's, Antígua. Ele sabe como curar pessoas de ferimentos mortais. É a única pessoa que pode nos ajudar agora. Nosso objetivo é simples: chegar lá antes que o português morra. Arrume suas coisas, doutor, vamos zarpar imediatamente e seu paciente será transferido em seguida!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Que pena, capitão. Perdemos, e não vamos ver aquele maldito ouro. Adeus.";
			link.l1 = "Adeus, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doc, prepare seu paciente para desembarcar. O bote está pronto. Depressa!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Estou a caminho, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "This house stinks of bloody mixtures! It would be a real surprise if the Portuguese died here; even breathing this smell could cure any disease!\nAnd the man's crew could easily find us thanks to the stench!";
			link.l1 = "Hugo, spare me your jokes. I have left a few men on the streets to watch over the house, but one more guard won't be unnecessary for our guest. Keep an eye on him and try to stop the swearing, or Gino will make you drink some mixture of his; I am sure he can cure that.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Don't worry, captain! I will watch over our money most vigilantly; he wouldn't escape even if he were healthy! And I beg you, please, no more mixtures!";
			link.l1 = "Viu, você consegue ser gentil quando quer. Fique atento, eu preciso ir.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Já vai embora, capitão? Ótimo! Já está na hora! Vi uns caras suspei... suspeitos na rua. Não parecem portugueses, mas estavam procurando por alguma coisa. Temos que tomar cuidado, capitão!";
			link.l1 = "Tudo bem, obrigado pelo aviso, Hugo. Vamos para o navio.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Capitão, já faz tempo demais que esperamos por este encontro! E quem está com você? O próprio Bartolomeu, o Português, ha, parece que o Destemido Pierre estava certo – é ele mesmo! Fique para trás, capitão, vamos levá-lo conosco e ninguém vai se machucar.";
			link.l1 = "Me desculpe, senhor, mas quem diabos é você? Saia do meu caminho ou nenhum de vocês vai ver o amanhã!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, such a menacing fellow, just look at him, lads! Ha-ha-ha! Listen here, pup, don't stand between Leo Cord and his money! We've been tracking down the Portuguese for almost half a year, and now we've finally got him. So put down that toothpick of yours and get lost while you're still breathing! We're not that greedy; a dead man will do just fine, ha-ha!";
			link.l1 = "Chega. Vamos dançar, senhores!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Eu sabia que tinha algo errado aqui! Muito bem, capitão! Mas está na hora de irmos, aquele maldito Leo Cord tem muitos bandidos por aqui e um navio de primeira! Temos que sair desta ilha!";
				link.l1 = "Bem lembrado, Hugo, e fico muito aliviado que nenhum tiro tenha sido disparado no buraco onde você estava escondido.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Que pena, capitão. Perdemos e não veremos aquele maldito ouro. Adeus.";
				link.l1 = "Adeus, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Eu... Eu estava protegendo nossa retaguarda, capitão! Você estava indo muito bem sem mim, mas e se alguém tivesse nos atacado do outro lado da rua? Você não teria tempo de correr para o navio.";
			link.l1 = "Talvez seja por isso que você não teve sucesso na sua profissão? Enfim, chega de conversa, precisamos ir para o navio! O tempo está acabando!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Capitão, o português está se sentindo muito mal, precisamos parar!";
			link.l1 = "É por isso que estamos aqui, senhor van Stal, nossa jornada está quase no fim. Vou alugar um quarto na taverna e nosso prisioneiro ficará lá por alguns dias.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer capitão, eu vou cuidar do português, ele precisa de repouso absoluto.";
			link.l1 = "Entendi, doutor, tudo bem. Droga, até quando vou ter que cuidar desse pirata? Isso faz mal pra ele, não é o que ele precisa! Parece que fui contratado como babá e... ah, me desculpe, doutor, é que já passou dos limites... Nos vemos depois.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, você é o capitão "+GetFullName(pchar)+", cujo navio acabou de chegar ao nosso porto hoje?";
			link.l1 = "Você está certo, como posso ajudar?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Sua Excelência Jacques Dille du Parquet, o governador da nossa colônia, está esperando por você. O assunto é urgente!";
			link.l1 = "Certo, monsieur, vou visitar Sua Excelência hoje.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Chegamos à Martinica, capitão! Nosso dinheiro não está longe agora...";
			link.l1 = "Só se os portugueses sobreviverem até chegarmos a Willemstad. Hugo, preciso ir até o navio, então você vai ter que cuidar do doutor e do paciente dele.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = " Ir para o navio? Por quê? Vai me emprestar alguns dos seus homens para me ajudar? E se acontecer alguma coisa enquanto você estiver fora?";
			link.l1 = "Me desculpe, mas não. Duvido que algo possa te ameaçar aqui. A guarnição está em alerta e há mais soldados nas ruas do que o normal, então, se algo acontecer, chame por eles. Viram um navio grande não muito longe desta ilha, talvez um pirata. E Sua Excelência, o Governador, me pediu para reforçar a ilha patrulhando com meu navio.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Um navio? Pirata? Pode ser o Albatroz! Ou talvez algum colega do nosso velho amigo Leo Cord!";
			link.l1 = "Ou talvez seja apenas um navio pirata comum. De qualquer forma, Hugo, se essa embarcação veio atrás das nossas cabeças, é melhor eu enfrentá-la com a patrulha local ao meu lado e pelo ouro do governador. Isso é muito melhor do que ficar olhando para trás o resto da viagem. Mas se esse alarme for falso, pelo menos me poupa de ficar sentado de bunda na taverna por alguns dias.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Pense bem, capitão, será sensato deixar a represa... o português desprotegido enquanto a fragata dele pode estar rondando por aí? Você está arriscando nossa recompensa ao aceitar o pagamento do governador!";
			link.l1 = "Chega de conversa, Hugo Avendell! Aqui quem manda sou eu, e a decisão final é minha! Então faça o que estou mandando. Vá até a taverna e fique de olho no doutor e no português até eu voltar.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Você voltou, capitão, finalmente! Receio que tenho más notícias para você – o português se foi, e o doutor também!";
			link.l1 = "Como assim?! E o que você estava fazendo então, seu idiota?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Posso apostar que aquele navio era o 'Albatross'. Eu vi os portugueses, eles entraram na taverna e eu... eu fugi. Me desculpe, mas encontrar o Cão de Um Olho foi demais, mesmo por tanto dinheiro!";
			link.l1 = "Mas que droga! Pelo menos me diga o que aconteceu na taverna?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Eu já disse que não vi nada. Corri pela cozinha assim que vi Franz Garcke e os homens dele... Foi por um triz! Isso aconteceu ontem à noite e eu não sabia como te avisar...";
			link.l1 = "Yes, you are a very brave and resourceful man... Fine, let's give you one more chance, we are going to find them. I have been saving this scoundrel for too long and now I consider him my property. We still have some time to catch them, so let's start from the tavern; perhaps someone has seen more than your fleeing heels. Go, prepare yourself!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Ouviu ele, capitão? Ele estava falando do Cão de Um Olho, aquele de quem te falei recentemente. E o castelhano que fala com língua presa é o Hernando Vasquez, o maldito Don – o açougueiro de Vera Cruz. Eu não vi ele!";
			link.l1 = "Relax, Hugo. I am sure that Bartholomeo is still on the island; he might be feeling better, but he is still too weak. And I think I know where to find him! We will get them, I won't walk away from my reward. If you are no coward, then follow me – it is not over yet.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Você faz perguntas demais, capitão... Espera aí, você não é aquele sujeito sorrateiro de Philipsburg? Você anda fugindo da gente faz tempo e agora veja só - aqui está você...";
			link.l1 = "Que pena pra você, verme!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... seu desgraçado de merda de caranguejo, você vai contar tudo pra gente, pode confiar, seu maldito rato! Depois vai acabar pendurado no mastro em vez da vela grande... E quem diabos é você? Droga, esses macacos não valem nada! Sempre tenho que fazer tudo sozinho...";
			link.l1 = "Estou incomodando vocês, senhores?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Gosto do seu timing... Acho que devo te agradecer por ter me mantido vivo até hoje?";
			link.l1 = "Você está certo. Meu nome é "+GetFullName(pchar)+" e você, português, ainda é meu prisioneiro. Então não me faça perguntas, temos que ir.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Espere, capitão... Tem muitos homens do Vasquez na cidade, eles não vão nos deixar sair assim tão fácil. Me dê uma espada e teremos muito mais chance.";
			link.l1 = "Você não está se dando bem com seus parceiros, né? Tudo bem, uma lâmina extra sempre é bem-vinda. Pegue a arma do cadáver e fique perto de mim!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Nem pense que eu vou te dar uma arma pra você me atacar assim que eu virar as costas! Só fique perto de mim.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Não se preocupe, capitão, prefiro morrer a cair nas mãos do Vasquez de novo.";
			link.l1 = "Olha, a questão é que ainda não quero você morto. Vamos, o tempo está acabando!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Que pena, eu teria ajudado o Caolho se quisesse você morto...";
			link.l1 = "Mas você também não me ajudou, então cala a boca e anda!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Droga! São eles! Matem todos!";
			link.l1 = "Lá vamos nós de novo... Venham, seus vira-latas!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Excelente! Você matou o Cão de Um Olho, isso sim é uma obra-prima! Quantos dos homens dele você mandou direto pro inferno?";
				link.l1 = "Eu estava lutando, não contando. E onde você estava, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Que pena, capitão. Perdemos e não veremos aquele maldito ouro. Adeus.";
				link.l1 = "Adeus, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Eu... estava garantindo uma retirada segura... protegendo nossa retaguarda, por assim dizer.";
			link.l1 = "Pois é, Hugo Avendell, sua covardia superou todas as minhas expectativas. Você faz ideia de como aquela luta foi difícil pra gente? Mal conseguimos sair vivos!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Calma, capitão... Eu admito que estava me escondendo. Mas encontrei essa oportunidade para você! Lembre-se, fui eu quem te levou até os portugueses! Bem... considerando sua justa indignação, concordo em ficar só com um terço da recompensa.";
			link.l1 = "Isso é simplesmente glorioso! Agora você quer negociar? Não, meu amigo, sua parte nesse negócio acabou! Você perdeu seu dinheiro na taverna em Saint-Pierre. Deixou lá e fugiu, então pra você acabou.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Capitão, você está claramente exagerando... Tudo bem, eu aceito um quarto... um quinto! Dez por cento!";
			link.l1 = "Não teste a minha paciência! Cai fora! Não preciso de covardes na minha tripulação, ainda mais agora, com o tempo correndo!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", você não acha que isso é um pouco injusto?";
			link.l1 = "Cause and effect, Hugo... You have made your choice, so farewell. Draw your own conclusions and don't plunge into adventures like that; this is clearly not for you.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Jogando o lastro fora, capitão? É verdade, ha... Vasquez ainda está solto e tem muitos homens e canhões no Albatross. Aposto minhas calças finas contra um lenço velho que Hernando não vai deixar a gente escapar.";
			link.l1 = "Bem, parece que teremos que ir cumprimentá-lo nós mesmos. Vá, monsieur Português, e tente manter a boca fechada. Vamos levantar âncora o quanto antes.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "O que você está esperando, caramba?!";
			link.l1 = "Onde está Hernando Vasquez? Fale e eu poupo sua vida.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Vá para o inferno com essas suas malditas perguntas!";
			link.l1 = "Depois de você...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "E aqui está você, meu valente amigo, finalmente podemos ter uma conversa de verdade! Parabéns, capitão – matar o Cão de Um Olho e destruir o 'Albatroz' não foi tarefa fácil! De verdade, você fez muito para salvar minha vida... Talvez eu até devesse lhe agradecer?";
				link.l1 = "Você vai me agradecer quando estiver dançando na forca, ou seja lá o que tenham preparado para você em Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "E aqui está você, meu valente amigo, finalmente podemos conversar! Parabéns, capitão – matar o Cão de Um Olho merece uma canção de honra! De verdade, você fez tanto para salvar minha vida... Talvez eu devesse até te agradecer?";
				link.l1 = "Você vai me agradecer quando estiver dançando na forca, ou seja lá o que tenham preparado para você em Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Incrível! Você tem salvado minha vida nas últimas duas semanas, me trouxe para sua casa e me protegeu em brigas... e agora vai me mandar para a morte? Mal posso acreditar... Na verdade, até começo a te considerar meu amigo agora, ha-ha.";
			link.l1 = "Um pirata falando de honra? Português, você só pode estar brincando comigo! Eu estava te poupando por um único motivo – para que o assassino e canalha enfrentasse o tribunal da justiça!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Amigo meu... soa como uma provocação. Mas, de qualquer forma, você está certo. Seria estranho da minha parte fazer isso, português...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Ah, já chega, capitão. Aposto que você fez tudo isso só pra pegar o dinheiro que a Companhia prometeu pelo prazer de me ver vivo! Não tente bancar o honesto mais do que realmente é, senhor, isso não combina com você.";
			link.l1 = "Só eu posso me julgar. Então vamos encerrar essa conversa. Está na hora de zarpar para Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Parece que ainda existe um pouco de honestidade nas pessoas hoje em dia... Pena que o dinheiro sempre atrapalha - não é, capitão?";
			link.l1 = "É estranho ouvir isso de um pirata condenado à forca, português. Vou te deixar ir... não me pergunte por quê, só suma no primeiro porto que encontrar. E lembre-se, não serei tão generoso se nos encontrarmos de novo.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Sério? Eu ia gostar disso, capitão! Não vai pedir um pouco de rum pra trazerem aqui? Sabe, só pra celebrar suas qualidades de cavalheiro, nosso relacionamento e o adiamento da minha sentença?";
			link.l1 = "Não faça piadas maldosas, você ainda é meu prisioneiro até chegarmos à primeira costa. Adeus.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Entendo... então é a forca, hein. Já era de se esperar. Agora escute o que tenho a dizer, capitão. Você fez tanta questão de me manter vivo só para me executar do jeito certo depois, e eu até agradeço por isso. Imagino que seria tolice da minha parte pedir para você mudar de ideia assim, não é? E o que diria se eu lhe oferecesse algo em troca? Um acordo, digamos assim, hmm?";
			link.l1 = "Não vou dizer nada, português. Você é um pirata e um canalha. Vai responder pelos seus crimes em Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Um acordo? O que você pode oferecer?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Não preciso do seu acordo, apenas suma no primeiro porto que encontrar. Hoje é seu dia de sorte.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Sabe, esse seu esforço incansável pra salvar minha vida, mesmo com os motivos desagradáveis por trás, ainda merece um pouco de gratidão. E Bartolomeu, o Português, entende bem de ser grato. Escute, um mês antes de a gente se conhecer, nós capturamos um navio da Companhia. Eles lutaram feito demônios até o último homem. Mas nos porões só tinha bala de canhão e rato\nMinha tripulação não gostou nada, mas eu achei um baú bem interessante e uns papéis na cabine do capitão. Era um navio-correio, levando amostras de minas em algum lugar da Amazônia. Diamantes puros e rubis, uma verdadeira fortuna!";
			link.l1 = "Um prêmio interessante... Agora entendo por que a Companhia está tão interessada em você, mas qual é o sentido da sua história?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "My first mates Vazquez and Franz Garcke had been keeping the crew in order, so I decided to take my chances. I hid the stones from them and burnt the papers. The Dutch had badly damaged our rigging during the boarding, and we had to take the 'Albatross' into a small bay of a small island in the north. I went deeper into the jungle alone while the whole crew were repairing the frigate\nI buried the stones; keeping them aboard was too risky considering the circumstances. My plan was to escape from my beloved crew at the very first port, buy or steal a small boat and sail to the island, collect my prize, and then... farewells to my old life! Europe, a decent mansion, a beautiful wife, you know the rest...";
			link.l1 = "Deixa eu adivinhar, alguma coisa deu errado.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Tudo deu errado! A maldita ilha era lar de uma horda de canibais locais. Eles nos atacaram assim que voltei para a praia. Tivemos que zarpar o mais rápido possível, foi aí que fui atingido. Achei que era só um arranhão.\nAlguns dias depois, eu estava largado, meio morto de febre, e aparentemente falei algo sobre as pedras. Franz e Vazquez perceberam que eu tinha escondido alguma coisa na ilha, mas não sabiam o lugar exato. Eles não gostaram nada da ideia de ficar vagando por lá, sendo constantemente atacados pelos índios. Então os desgraçados me arrastaram até o porto mais próximo, já que nosso médico tinha sido morto na briga com os holandeses, eles precisavam de outro.\nFoi assim que fui parar na casa daquele doutor, eles queriam me trazer de volta à consciência só tempo suficiente para me torturar e descobrir onde estavam as pedras. Acredito que depois iriam me cortar em pedaços e dar minha carne suculenta para os caranguejos.";
			link.l1 = "Não posso dizer que os julgo – você tentou enganar seus homens. Então pergunto de novo, por que está me contando isso?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Esses cães não eram gente, pode acreditar, agora todos estão no lugar que merecem – no inferno, ha-ha! Como pagamento pela minha liberdade e pela minha vida, posso te contar a localização exata dos tesouros holandeses.";
			link.l1 = "Não, Bart, sua traição me convenceu completamente da sua maldade. Willemstad e a justiça te aguardam. Sem acordo.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "E eu devo acreditar que essas joias realmente existem? Tanto faz, não tenho nada a perder mesmo... O acordo foi o começo dessa história e o acordo será o fim dela. Aceito seus termos, português.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Considere isso a minha modesta gratidão. Ah, queria saber quanto vale a pele do Bartolomeu, o Português, em pesos reluzentes, ha! Sei que seus objetivos eram puramente práticos, mas mesmo assim, obrigado por tudo, capitão, ha-ha\nÉ em Turks, nas selvas não muito longe da costa. Procure por uma árvore seca e torta—só tem uma dessas lá. Enterrei o baú perto dela. Então não esqueça de levar uma pá. Boa caçada...";
			link.l1 = "Está bem, vou me lembrar disso, e você pode pegar um bote agora mesmo e sair do meu navio. Adeus.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Mais uma coisa, capitão. Acho que ainda há muitos selvagens por aí, mas não são só eles que você deve temer. Vasquez não estava no 'Albatross', certo? O Maldito Don é esperto demais... fique de olho até vê-lo enforcado ou com uma bala na cabeça.";
			link.l1 = "Obrigado pelo aviso, português. Agora, poderia sair do meu navio de uma vez... não teste a minha paciência.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, e quem é esse! Capitão "+pchar.name+" ele mesmo! Quer uma bebida?";
			link.l1 = "Sabe, na verdade fico feliz em te ver de novo. Mas talvez eu tenha sido duro demais com você na Martinica.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Tanto faz, capitão! O que aconteceu, aconteceu... Mas, pra ser sincero, eu realmente te dei motivo pra me mandar embora... Mas olha, você não vai acreditar quem está de visita em Phillipsburg hoje!";
			link.l1 = "Não me diga que é...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Não, não, capitão, não são os portugueses. E também não é mais um desgraçado ferido. É muito melhor! É Hernando Vasquez... O próprio Don Sangrento! Ele tem sido hóspede do governador local nos últimos dias.";
			link.l1 = "Vasquez? O hóspede do governador? Agora entendi. Hugo, me conte mais sobre isso, o que diabos está acontecendo aqui?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Bem, eu sei muita coisa... mas graças à nossa viagem, estou falido de novo. Talvez a sua necessidade por essa informação valha uns pesos?";
			link.l1 = "Hugo, você continua sendo um chantagista e um canalha! Fale logo o que tem pra dizer, pegue esses 5000 pesos só por causa da nossa velha amizade.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "De alguma forma, não estou surpreso. Aqui, pegue 10.000 pesos, e é bom que sua informação valha tudo isso!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Tenho uma proposta melhor para você. Que tal se juntar à minha tripulação? Pelo que vejo, você tem talento para fechar e encontrar bons negócios, então, se estiver cansado de fingir que é um grande lutador, será muito bem-vindo como meu intendente.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Não, capitão, não vai ser assim! Você já arrancou uma boa grana com aquele maldito português, tenho certeza. Então considere isso como a minha parte, não seja tão ganancioso. 15.000 moedas e nem um peso a menos!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Ah, vai pro inferno, fica com eles!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Bem, dizem que a ganância faz bem... Mas isso aí não é demais pra você, hein?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Agora sim, esse é o prêmio pra mim! ... Olha, o Vasquez estava navegando comigo no mesmo navio, mas enquanto eu limpava o convés pra pagar a passagem, ele descansava numa cabine, então graças a Deus a gente quase não se via e ele nem me reconheceu. Mas comecei a seguir esse diabo logo de cara... Aconteceu uma história interessante com ele.";
			link.l1 = "Continue! O que ele está fazendo no palácio do governador?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Eu não sei muito, mas a guarnição está em alerta há alguns dias desde a chegada dele, e o enorme navio de guerra de repente levantou âncora e partiu às pressas. Acho que seguiu para noroeste. A cidade inteira está perdida em especulações e fofocas...";
			link.l1 = "Então era aquele o navio que encontrei! Interessante... Não fuja do assunto, Hugo, por favor, continue sua história.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Bem, como eu disse, o navio já tinha partido e o Vasquez virou uma espécie de hóspede do nosso governador, Martin Thomas. Às vezes vejo ele pela cidade, sempre acompanhado de alguns soldados. Não sei se é escolta ou comboio, ha-ha. Mas só o pessoal da residência poderia te contar mais sobre o Don.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Talvez você tenha razão. Mas tínhamos um acordo, lembra? Não tente bancar o herói, vá para o meu navio e espere eu voltar. Vou tentar conversar com o nosso hospitaleiro governador.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Bem, isso foi interessante. Você realmente me ajudou, Hugo. Beba seu rum, o resto não é da sua conta.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Você está falando sério, capitão? O que há de errado com você? Você me expulsou apontando uma arma na minha cara, e agora vem até mim com esse tipo de proposta?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Esqueça isso, eu não tenho sido eu mesmo e peço desculpas, acho que a ganância me consumiu. Aqui, pegue 10.000 pesos e me diga o que sabe sobre Vasquez, estou com pressa.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Talvez eu deva pedir desculpas por aquilo. Você é um lutador patético, mas sabe lidar bem com dinheiro. Repito minha proposta, o que me diz?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "O que posso dizer... Eu topo, mas só depois de receber minha parte, capitão. Dez por cento, lembra? Você recebeu dois mil por aquele canalha, então se quer que eu entre na sua tripulação, é melhor começar quitando suas dívidas. Dez por cento, e sem discussão!";
			link.l1 = "Você é um trapaceiro mesmo, Hugo. Não tenho tudo isso comigo agora, mas volto logo. Fique aqui.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Espero que você esteja à altura das minhas expectativas com esse seu faro para negócios, hein! Fique com a sua parte!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "A decisão é sua, capitão. Vou ficar aqui por um tempo. Volte se mudar de ideia.";
			link.l1 = "Tudo bem, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = " Mudou de ideia, capitão? Então vou esperar pelo meu dinheiro.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Pegue suas moedas, seu canalha, ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Eu ainda não tenho essa quantia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Bom dia, capitão. Quer alguma coisa?";
			link.l1 = "Não, não, só estou esperando. Quando o senhor Thomas vai estar disponível? Estou aguardando uma audiência... sim. Me diga, Sua Excelência realmente considera o famoso pirata Hernando Vasquez seu amigo?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Não se preocupe, senhor, ele deve ser solto a qualquer momento agora, e claro que não, senhor! Esse bandido se entregou às autoridades, mas de alguma forma não foi enforcado. Talvez tenha comprado a própria vida traindo os antigos comparsas... Não tenho certeza. Ele está preso aqui há vários dias... Foi um pesadelo, senhor! Aquela fera em forma de gente estava morando na nossa mansão!";
			link.l1 = "Que pesadelo! O que será que aquela criatura contou ao senhor Thomas para escapar da forca? Nem consigo imaginar!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Também não sei, mas posso te contar em segredo que todos os criados ficaram aliviados quando Sua Excelência se livrou de um hóspede desses...";
			link.l1 = "Se livrou dele? Ele finalmente teve o que merecia?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Not quite so. Yet. A few days ago, he was taken to a military brig which sailed to Willemstad. You see, mynheer Thomas had lost interest in the scoundrel; it seems he tried to deceive him.\nAlso, they say that his former captain was caught - Bartolomeo the Portuguese! Just think of it! Looks like the Company wants to hang them together. Word is the trial will be in a month, but why wait so long?";
			link.l1 = "Os portugueses?! Hm... obrigado por me fazer companhia, amigo... parece que o senhor Thomas está livre agora, vou me retirar.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Agora vocês estão mortos... os dois!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Agora sim, essa é uma visita que eu não esperava, capitão! Mas não parece nada amigável, com todo esse sangue, barulho e tiros, ou será que é algum tipo de festa com fogos de artifício, hein?";
				link.l1 = "Pare de fazer essas piadas maldosas, português. Eu só não gosto de como você usou a liberdade que comprou de mim. Me esforcei demais para salvar sua bunda miserável para te ver sendo pego de forma tão idiota logo depois da nossa despedida!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Ah, eu estava entediado! Então vim aqui te visitar. Está confortável aqui, amigo!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Cuidado, amigo! Ah, que pena que não posso te ajudar!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Então, a nobreza às vezes não se deixa comprar por moedas, hein? Hah... CUIDADO, LOGO ATRÁS DE VOCÊ!";
			link.l1 = "Agh, não esse maldito problema de novo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Então, a nobreza às vezes não se deixa levar por moedas, né? Ha... CUIDADO, ATRÁS DE VOCÊ!";
			link.l1 = "Agh, não de novo essa maldita confusão!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "E eu te avisei que esse cara era encrenca!";
			link.l1 = "Ele quase conseguiu atirar em mim pelas costas! Como ele conseguiu passar?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Eu vi que ele tinha uma gazua, parece que alguém deu isso pra ele... ele sempre teve contatos nos lugares mais baixos. Bem, capitão, acho que devíamos sair daqui, não acha?";
			link.l1 = "Não me diga! Tá bom, vamos logo antes que a guarnição inteira chegue. Vou arrombar sua tranca num instante...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Sabe, capitão, esse ar fresco... a gente só começa a valorizar depois de passar algumas semanas numa masmorra, logo depois que o bote do seu navio foi encontrado pela patrulha local. Acho que ainda te devo pela minha fuga.";
			link.l1 = "Não precisa, português. Eu não sou um cavaleiro honrado, eu só... faço o que acho certo e o que precisa ser feito.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, e isso é uma qualidade perfeita! Mas eu insisto, aqui, pegue... isso é a única coisa que consegui esconder na prisão... Sim, você entendeu direito. Este é meu talismã. Sempre me trouxe sorte no mar. Você é um ótimo marinheiro, e tenho certeza de que você ou seu navegador vão saber usar isso.";
			link.l1 = "Sim, e você ainda teve a sorte de cair direto nas mãos dos holandeses com esse talismã.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Ei! Ainda estou vivo, não estou? E só pra você saber, não estou mais na prisão. Pegue, capitão, chegou a hora do talismã servir a você. E agradeço de novo!";
			link.l1 = "Adeus então, português. E, por favor, tente ficar longe da forca! Só pelo bem do meu trabalho duro, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
