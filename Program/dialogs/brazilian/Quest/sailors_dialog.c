// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Fale com o nosso capitão. Não tenho nada pra te dizer.";
			Link.l1 = "Certo.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Fale com o nosso capitão. Não tenho nada pra te contar.";
			Link.l1 = "Tudo bem.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Senhor, está procurando por alguém?";
					Link.l1 = "Sim, camarada. Posso ver o capitão?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Se você está procurando pelo nosso capitão, ele desembarcou há pouco.";
					Link.l1 = "Tudo bem";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Ah, você veio aqui sozinho. Ha! Nesse caso, vá falar com o nosso capitão. Conte a ele sobre suas lamentáveis ações...","Por todos os santos, parece que você está maluco, amigo. Vá falar com o nosso capitão, ele vai conversar com você.");
				Link.l1 = "Que pena...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "É melhor você procurá-lo no porto.";
			Link.l1 = "Obrigado, meu amigo.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Olha, aquilo foi uma baita confusão, capitão! A gente estava na taverna, bebendo como sempre, quando ouvimos uns gritos. Saímos correndo da taverna e vimos que estavam tentando te prender. Malditos! Então resolvemos sair desse porto hostil.";
			link.l1 = "É, realmente algumas pessoas têm uma noção bem estranha de justiça.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Capitão! Não se preocupe assim! Estava claro que não havia como escapar discretamente, então decidimos visitar o banqueiro local para dar uma olhada nos cofres dele. Aqui está a sua parte - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Capitão! Não se preocupe assim! Estava claro que não havia como escapar discretamente, então resolvemos visitar o banqueiro local e dar uma olhada nos baús dele. Também tinha uma bela espada na caixa de penhores. Aqui está a sua parte - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos e uma espada...";
			}		
			link.l1 = "Muito bem, rapazes! Muito bem! Estou orgulhoso de vocês.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Capitão, seu amigo fugiu.";
			link.l1 = "Que amigo?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Bem, o amigo que você tirou das masmorras.";
			link.l1 = "Como diabos você conseguiu perder ele?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Não foi culpa nossa, capitão. Ele pulou pela latrina direto pro mar... Tentamos atirar nele, mas estava escuro demais lá dentro...";
			link.l1 = "Maldição! Vocês realmente perderam o controle! Todos vocês vão ser deixados em terra e mandados trabalhar nos canaviais! Perder um figurão tão valioso assim! Inacreditável!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Capitão, nos perdoe, a culpa foi nossa – o prisioneiro escapou.";
			link.l1 = "Que prisioneiro? Quem fugiu?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Bem, ah, esqueci o nome dele, "+pchar.GenQuest.Hold_GenQuest.CapName+", não é?";
			link.l1 = "Droga! Onde você estava olhando?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Ele saiu do porão de carga e pulou por cima do costado. Não atiramos nele para evitar barulho, e enquanto preparávamos o bote, ele foi salvo por aqueles malditos pescadores.";
			link.l1 = "E por que eu te pago! Açoite o chefe da guarda e tire o rum dele por uma semana. Atenção! Vamos levantar âncora...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Saudações, capitão. Não houve nenhum incidente durante o seu...";
			link.l1 = "Tá bom, tá bom, eu entendi.... Tem um prisioneiro no nosso porão de carga. O nome dele é "+pchar.GenQuest.Hold_GenQuest.CapName+". Leve alguns homens e escolte-o até o porto. Ele está livre agora.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Ele está mesmo livre? Vamos entregá-lo em um bote?";
			link.l1 = "Não, em uma maldita tartaruga... Achei que tinha sido claro o bastante. E anda logo! Precisamos levantar âncora antes da maré baixar.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Capitão, não há uma alma viva a bordo do navio! Tem algo muito errado aqui... O Tommy disse que viu um gato no convés, e era o único ser vivo...";
			Link.l1 = "Idiota, gatos não têm alma. Parece que ele não vai à igreja faz tempo, ou talvez nunca tenha ido. Você já foi à cabine do capitão? Preciso do diário de bordo.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Não, eles têm alma sim. Não havia diário de bordo nem um único instrumento de navegação. Nem sequer um escaler...";
			Link.l1 = "Eles não. Será que foi levado embora por uma tempestade?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Eles têm, capitão. Gatos têm alma. Capitão, o bote foi levado e encontramos uma espada no chão do cockpit. Está enferrujada e ensanguentada. Aqui, dê uma olhada...";
			Link.l1 = "Para de me dar essa porcaria, joga isso fora e para de falar de gatos, caramba! Vamos verificar o porão e ir embora... Ah, tem algo muito errado aqui e eu não gosto nem um pouco disso...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Capitão, estou com um mau pressentimento sobre este lugar... Talvez seja hora de irmos embora?";
					Link.l1 = "Sim... Vá para o bote do navio.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Capitão, não vou ficar neste navio estranho se você pretende levá-lo ao porto. Prefiro me jogar no mar.";
					Link.l1 = "Eu não estou disposto a fazer isso... Também estou um pouco assustado...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Talvez devêssemos afundá-lo, Capitão?";
					Link.l1 = "Para deixar as almas dos marinheiros mortos que habitam aqui nos visitarem em nossos pesadelos?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Meu Deus, não! Capitão... por que está dizendo isso?";
			Link.l1 = "Não fique pálido, eu estava brincando... Vá para o bote do navio. E acho que você tem razão no fim das contas, talvez os gatos realmente tenham alma...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Fale com o chefe. Não tenho nada pra te dizer.","Estou no meu posto. Todas as perguntas devem ser direcionadas ao comandante do forte.");
			Link.l1 = "Certo.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Estou realmente ocupado agora. Me deixe em paz.","Não me distraia do meu trabalho. Não há nada para conversar.");
			Link.l1 = "Pena...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan queria te contar 'umas coisas'... Ele está por aqui, no convés.","Heh, encontre Morgan. Más notícias estão te esperando...");
			Link.l1 = "Certo.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
