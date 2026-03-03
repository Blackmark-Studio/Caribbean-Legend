//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Tenho uma pergunta pra você.","Preciso de informações.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Ei, capitão! Isso, você mesmo. Venha cá, tenho uma proposta pra você...";
					link.l1 = "E qual é o esquema?";
					link.l1.go = "passenger";
					link.l2 = "Estou com pressa, amigo. Talvez numa próxima vez.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Ei, capitão, estou ocupado agora. O que você precisa?","O que você quer, capitão?","Capitão, não estou com vontade de conversar. O que você quer?");
				link.l1 = "Saudações, "+GetAddress_FormToNPC(NPChar)+". Espere um momento, quero que me conte uma coisa.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Tenho uma pergunta para você.","Preciso de informações.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Não é nada, estou indo para a taverna...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Você é capitão de um navio, mas não parece um mercador. Parece que tem algumas moedas no bolso... Que tal conseguir uma informação interessante em troca de um punhado de dobrões?";
				link.l1 = "Primeiro, prove que sua informação vale pelo menos uma peça de oito.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "É sim, capitão, é sim. Vale muito mais do que estou pedindo. Você me dá o ouro e eu te digo quando e em qual navio uma certa pessoa muito importante vai embarcar. Você vai poder pedir um resgate bem alto por ela... Eu até te conto o nome de quem vai comprar. Negócio fechado?";
				link.l1 = "De jeito nenhum! Eu não sou sequestrador. Cai fora!";
				link.l1.go = "exit_quest";
				link.l2 = "E como posso saber que está dizendo a verdade?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Seria muito imprudente tentar te enganar, lobo do mar. Eu moro nesta cidade e não preciso de problemas. Por apenas "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" dobrões e eu te dou todas as informações. Você vai lucrar muito mais.";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Você tem razão. Pegue o ouro e comece a falar.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Não tenho moedas suficientes comigo agora.";
				link.l2.go = "passenger_3";
				link.l3 = "Você tá brincando comigo? Pagar ouro de verdade por promessas vazias? Cai fora...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Não quer? Tudo bem, capitão. Posso esperar mais alguns dias, e essa informação também. Me procure quando tiver seu ouro. Não vai ser difícil me achar... hoje, ha-ha-ha!";
				link.l1 = "Não mostre os dentes desse jeito. Tá bom, eu trago o ouro pra você... se eu não mudar de ideia. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Você trouxe meu ouro?";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Sim. Pegue. Nem tente mentir agora...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Ainda não. Talvez mais tarde...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveDublonsFromPCharTotal(sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Mantenha sua pólvora seca, você vai precisar dela em breve, capitão. Agora escute, em "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" um navio vai partir da nossa colônia, o navio está "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" chamado de '"+pchar.GenQuest.Marginpassenger.ShipName+"' e estará indo para "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". Haverá um passageiro -  "+pchar.GenQuest.Marginpassenger.Text+", chamado de "+pchar.GenQuest.Marginpassenger.q1Name+"\nO capitão "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Gen"))+" é um covarde de marca maior, igual a todo comerciante, ha-ha-ha! Talvez você nem precise lutar. Só meter um bom susto nele que ele mesmo entrega o alvo, he-he\nComo você entende, "+pchar.GenQuest.Marginpassenger.Text1+", você provavelmente vai receber suas moedas, sim, mas as autoridades locais vão te caçar depois disso. É melhor você trazer sua presa para "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". Você vai encontrar um homem lá chamado "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" e você nem vai precisar dizer seu nome. A decisão de onde resgatar seu homem é sua, mas não tente dar um passo maior que a perna... Mas "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" Dúbloons você pode pedir, claro. Entendeu?";
				link.l1 = "Sim. Vou voltar para o meu navio e registrar isso no diário de bordo.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Exatamente! A escolha certa. Muito bem, Capitão, boa sorte com essa tarefa fácil. Ah, sim, quase me esqueci: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" não vai partir do porto, mas de uma das baías próximas. Então fique de olho. Boa sorte e obrigado pelo ouro!";
				link.l1 = "De nada. Não gaste tudo numa noite só.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute, se acalme e guarde sua arma.","Escute, se acalme e guarde sua arma.");
			link.l1 = LinkRandPhrase("Certo.","Certo.","Como quiser.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Não fique enrolando, Capitão. Diga logo o que quer!","Ah, tá bom. O que você quer?","Perguntas? Tudo bem, marinheiro, estou ouvindo.");
			link.l1 = LinkRandPhrase("Pode me contar as últimas fofocas?","Aconteceu algo interessante por aqui recentemente?","O que está acontecendo no Caribe?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
