// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("A cidade está em alerta. Parece que chegou a minha hora de pegar em armas também...","Você não está sendo perseguido por todos os guardas da cidade? Guardas, comigo!","Você não vai encontrar abrigo aqui. Mas vai encontrar alguns centímetros de aço frio debaixo das suas costelas!"),LinkRandPhrase("O que você quer, canalha?! A guarda da cidade já está no seu encalço, você não vai longe, "+GetSexPhrase("pirata imundo!","canalha")+"!","Pare! "+GetSexPhrase("Assassino imundo! Guarda!!!","Eu não tenho medo de você! Logo você vai ser enforcado no nosso forte, não tem onde se esconder...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Parece que você está cansado de viver...","E por que vocês não querem viver em paz, cidadãos..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Vá para o inferno!","Restam apenas alguns segundos para você neste mundo..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, é você... Quem é você? O que te traz ao cemitério?";
				link.l1 = "Meu nome é "+GetFullName(pchar)+". E quem é você, o que está fazendo aqui? E por que está tão assustado?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Então, como foi? Conferiu? Agora acredita em mim?";
				link.l1 = "Não, ainda não desci até a cripta. Espere mais um pouco, vou conferir tudo.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "E aí? Você deu uma olhada? Conseguiu ver?";
				link.l1 = "Sim, eu consegui! Você estava certo!";
				link.l1.go = "Lantern_10";
				link.l2 = "Não foi bem o que você imaginava.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Olá, marinheiro! Meu nome é "+GetFullName(npchar)+", e eu sou a única alma viva aqui. Na verdade, todos nós ainda vamos morrer, ha-ha-ha! Por que você veio?","Olá! Faz muito tempo que não vejo um homem vivo... Permita-me apresentar - "+GetFullName(npchar)+", e este cemitério é meu último refúgio. Pelo visto, é aqui que serei enterrado. Como posso ajudá-lo?");
				link.l1 = "Olá, "+npchar.name+"! Meu nome é "+GetFullName(pchar)+", e eu sou capitão. Atravessei a selva e cheguei até aqui. Pensei em dar uma olhada nesta casa aconchegante, pra ver quem é corajoso o bastante pra morar aqui...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, meu velho amigo, Capitão "+GetFullName(pchar)+"! Entre, entre!";
				link.l1 = "Bem-vindo, amigo! Fico muito feliz em te ver. Você já viu esqueletos dançando à noite e mortos com moedas de cobre nos olhos nos seus sonhos?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "E por que eu deveria ter medo, capitão? São os vivos que devemos temer, não os mortos — eles não mordem. Eh! Já tive uma vida bem diferente, e agora sou o vigia deste cemitério. Cuido das sepulturas. E, de vez em quando, faço uns negócios estranhos também...";
			link.l1 = "E com que mercadorias você negocia, me diga, por favor?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "O que te traz aqui desta vez?";
			link.l1 = "Mostre-me o que você tem à venda hoje.";
			link.l1.go = "trade";
			link.l2 = "Quero te fazer uma pergunta...";
			link.l2.go = "quests";
			link.l3 = "Nada de mais. Só vim te cumprimentar.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Tenho bastante tempo livre, então gosto de caminhar pela selva para coletar plantas úteis e pedras interessantes. Depois vendo tudo na cidade. Não dá muito dinheiro, mas é melhor do que nada. E ainda ganho todo tipo de coisa dos meus amigos...";
			link.l1 = "Amigos? Quer dizer que você revende o que os outros trazem pra você?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Não, eles me dão tudo de graça. Quem mais seria amigo do vigia do cemitério, se não os mortos?";
			link.l1 = "O quê... Você saqueia cadáveres?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "I don't rob; I just take things off those who don't need them anymore. Many different people are buried here-some unknown and not from our lands. The commandant brings a dead body from the town and says: 'This is for you, "+npchar.name+", send him on his final journey.' Homeless, hanged pirates, bandits killed by guardians-all are buried here. And old "+npchar.name+" buries their bodies on a Christian custom.";
			link.l1 = "Entendi. Bem, dinheiro é dinheiro, me mostre o que você tem.";
			link.l1.go = "trade";
			link.l2 = "Entendido. Preciso ir. Foi um prazer conhecê-lo.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("E você, "+GetFullName(pchar)+", você é um ladrão! Guardas!!!","Mas que diabos! Olhei pro outro lado por um instante e você já tá tentando roubar o que é meu! Peguem o ladrão!!!","Guarda! Roubo!!! Peguem o ladrão!!!");
			link.l1 = "Ah, droga!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Ufa, então você é só um viajante... Meu nome é "+GetFullName(npchar)+", eu sou o zelador deste lugar amaldiçoado.";
			link.l1 = "Por que você sente isso em relação ao cemitério? Pelo contrário, é daqui que nosso Senhor leva os justos após seu sepultamento.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "Mas os ímpios, ao que parece, continuam aqui mesmo depois de enterrados! Nas últimas noites, tem saído uns barulhos da cripta. E os gemidos são tão assustadores que me dão arrepios... Parece que uma alma perdida não consegue descansar! Agora só consigo dormir de dia – à noite, não posso sair do meu posto nem pregar o olho...";
			link.l1 = "Barulhos? Gemidos? Mas não há ninguém lá além dos mortos.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "É isso que eu tô dizendo, entendeu? É melhor você sair daqui antes que o fantasma perceba você... Senão, não vai conseguir dormir, igual a mim.";
			link.l1 = "Hum, sim, acho melhor eu sair daqui.";
			link.l1.go = "Lantern_04";
			link.l2 = "Talvez eu possa te ajudar? Deixe-me investigar esses barulhos estranhos esta noite.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Você ficou maluco?! Vejo que está armado, mas como pretende lutar contra os mortos-vivos com isso? E se acabar batendo as botas lá, o que vai acontecer? O fantasma vai ficar solto, e ainda pode te transformar em servo dele!";
			link.l1 = "Bem, isso é só superstição...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Que superstição? Aqui não é a terra piedosa da Europa, droga... Os nativos, aquele povo de pele vermelha, conseguem invocar qualquer coisa – e agora temos que viver aqui!";
			link.l1 = "Ainda assim, deixe-me tentar. Vou esperar até anoitecer e então descer à cripta.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Tudo bem, faça como quiser. Mas se você não voltar até o amanhecer, vou trancar tudo, barricar e sair daqui sozinha! Seja esfregando o convés como marinheira ou carregando caixas como estivadora – de qualquer jeito, não volto mais pra cá!";
			link.l1 = "Calma... Vai dar tudo certo.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Espere... Leve esta lanterna. Tenho uma de sobra. Você vai precisar dela lá. Está um breu total!";
			link.l1 = "Obrigado, uma lanterna vai ser mesmo útil num lugar desses.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Certo? O que tinha lá? Me conta!";
			link.l1 = "Era o espírito inquieto de uma mulher! Por sorte, pedi ao padre local para abençoar minha lâmina e expulsar o mal, então deu tudo certo. Esse espírito não vai mais te incomodar.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Ó Senhor, salva nossas almas pecadoras! Eu avisei! E você não acreditou em mim!";
			link.l1 = "Sim, e lamento muito por isso. Mas agora está tudo bem – eu aspergi este lugar com água benta, e nenhum espírito vai ousar se levantar do túmulo. Pode dormir tranquilo.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Muito obrigado! Você não faz ideia do quanto isso significa pra mim! Aqui, por favor, aceite isto. Não é muito, mas não posso deixar você ir embora sem uma recompensa.";
			link.l1 = "Obrigado, não posso recusar. Boa sorte pra você!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Não? Então que diabo... digo, o que, em nome de Deus, aconteceu lá?";
			link.l1 = "Não havia fantasma algum. Um casal jovem escolheu esta cripta como lugar para se encontrarem. Os pais deles são contra essa união, então eles estavam procurando um lugar para ficarem a sós.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Sozinha?.. Aqueles moleques! Quero ver se eles têm coragem de aparecer aqui de novo! Ou boto os dois pra correr no chicote, ou tranco eles na cripta pra aprenderem a lição!!!";
			link.l1 = "Eles não vão voltar aqui mais. Eu disse a eles que as travessuras deles realmente assustaram a guarda local. Era isso que eles queriam. E, aliás, a fechadura da porta está quebrada mesmo.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Sem problema, eu vou substituir. Mas se algum dia eu pegar esses caras...";
			link.l1 = "Não fique tão bravo. Todos nós já tivemos essa idade. Eles não vieram aqui porque este era o melhor lugar para namorar.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Justo... Fazer o quê, que Deus os acompanhe. Obrigado por não deixar um velho na mão. Aqui, por favor, aceite isto. Não é muito, mas não posso deixar você sair sem uma recompensa.";
			link.l1 = "Obrigado, não posso recusar. Boa sorte pra você!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
