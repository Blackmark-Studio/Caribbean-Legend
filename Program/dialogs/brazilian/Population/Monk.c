//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Bom dia para você, meu filho. Peço que seja generoso e doe algumas moedas de prata para o bem dos pobres, da sua alma e da Santa Madre Igreja.";
					link.l1 = "Bem, padre, acredito que todos devemos ajudar uns aos outros, como Cristo e Sua Igreja nos ensinam. Pode me dizer para onde vai o dinheiro?";
					link.l1.go = "donation";
					link.l2 = "Me perdoe, padre, mas estou mais pobre que rato de igreja agora.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Bom dia para você, meu filho. Gostaria de lhe pedir um favor. Naturalmente, vou pagar.";
					link.l1 = "Estou ouvindo, padre. O que o senhor precisa?";
					link.l1.go = "passenger";
					link.l2 = "Me desculpe, pai, mas eu preciso ir.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Saudações, meu filho. Imagino que você seja capitão. Então tenho uma proposta para você.";
					link.l1 = "Estou ouvindo, padre.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Saudações, meu filho. O que te aflige?","Saudações, meu filho. Procure o padre se quiser se confessar.","Saudações, meu filho. 'Lembra-te do teu Criador nos dias da tua juventude.'"),LinkRandPhrase("Saudações, meu filho. O que te aflige?","Bom dia para você, meu filho, que Deus te abençoe!","Bom dia para você, meu filho, que o rosto de Deus brilhe sobre você!"));
				link.l1 = LinkRandPhrase("O mesmo para o senhor, padre. Como está indo?","Bom dia para o senhor, padre. Como vai a sua paróquia?","Como vai, padre?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Tenho uma pergunta para o senhor, padre.","Preciso de informações.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Padre, tenho pessoas no meu navio. São escravos, tanto cristãos quanto pagãos não batizados. Quero que o senhor batize os pagãos e dê a comunhão aos cristãos. Depois, vou libertar todos eles para a glória de Deus e da nossa Igreja.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Padre, quero que abençoe meu navio e celebre uma missa para minha tripulação. Quanto isso vai custar?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Com licença, padre, mas eu preciso ir.","Desculpe incomodá-lo, Padre.","Preciso voltar para o meu navio, padre. Adeus!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Você de novo, meu filho? O que você quer?","Tem mais alguma coisa para me contar, meu filho?","É bom ver você de novo, meu filho.");
				link.l1 = LinkRandPhrase("O mesmo para o senhor, padre. Como está indo?","Bom dia, padre. Como vai a sua paróquia?","Como vai, padre?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Tenho uma pergunta para o senhor, padre.","Preciso de informações.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Padre, tenho pessoas no meu navio. São escravos, tanto cristãos quanto pagãos não batizados. Quero que o senhor batize os pagãos e dê a comunhão aos cristãos. Depois disso, vou libertar todos eles para a glória de Deus e da nossa Igreja.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Padre, quero que abençoe meu navio e celebre uma missa para minha tripulação. Quanto isso vai custar?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Com licença, padre, mas preciso ir.","Desculpe incomodá-lo, Padre.","Preciso ir para o meu navio, Padre. Adeus!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "Tenho uma questão urgente para você, meu filho. Preciso que entregue estes papéis ao pastor de  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+". Você está indo para lá? Os documentos precisam ser entregues em até duas semanas...";
				link.l1 = "Fácil demais, padre. Me dê esses papéis e eu os entregarei para "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Eu ficaria feliz em ajudar, padre, mas estou navegando para outra direção.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Meu filho, você aceitaria me ajudar com um assunto urgente? Nossa igreja está ficando sem Bíblias e livros de oração, que oferecemos a todos que precisam\nVocê poderia navegar até a colônia mais próxima "+NationNameGenitive(sti(npchar.nation))+", pegar algumas Bíblias e livros de orações na igreja local e trazê-los aqui? E tente fazer isso dentro de um mês, não temos muitos sobrando.";
				link.l1 = "Vou ajudar sua igreja com prazer. Posso conseguir esses livros com qualquer pastor?";
				link.l1.go = "Churchbooks";
				link.l2 = "Eu ficaria feliz em fazer isso, padre, mas agora não posso.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Está tudo bem, meu filho. Obrigado por suas palavras gentis.","Nossa paróquia está bem, meu filho. Obrigado pela sua preocupação.");
			link.l1 = "Então eu preciso ir, Padre.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Claro, meu filho. "+sTemp+"";
			link.l1 = "Que valor de doação seria considerado suficiente?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Tudo depende da sua generosidade e do seu desejo, meu filho. 'Deus ama quem dá com alegria.' Ficamos profundamente gratos por qualquer doação.";
			link.l1 = "100 pesos";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pesos";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pesos";
			link.l3.go = "donation_rate_3";
			link.l4 = "10.000 pesos";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Obrigada pelas moedas, meu filho! Elas serão usadas para uma boa causa!";
				link.l1 = "De nada, padre.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Be not deceived, God is not mocked. For whatsoever a man soweth, that shall he also reap. For he that soweth to his flesh shall of the flesh reap corruption; but he that soweth to the Spirit shall of the Spirit reap life everlasting.'";
				link.l1 = "Ha-ha! Poupe o sermão, eu não faço caridade. Cai fora!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Eu lhe agradeço, meu filho. Esta quantia vai realmente ajudar a nossa missão da paróquia. Que Deus te abençoe!";
				link.l1 = "Boa sorte, padre!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "A retribuição de Deus te espera, patife! Zombar de um servo da santa igreja de Cristo é blasfêmia!";
				link.l1 = "Ha-ha! Eu não faço caridade. Cai fora!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Eu jamais poderia imaginar que você seria tão generoso, meu filho! Vou mencioná-lo na minha próxima carta ao nosso bispo, e vamos rezar por você todos os dias! Que Deus te abençoe, e aceito seu dinheiro com gratidão!";
				link.l1 = "Dinheiro não vale nada se não for usado para os propósitos de Deus! Boa sorte, Padre!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "A retribuição de Deus te espera, patife! Zombar de um servo da santa igreja de Cristo é blasfêmia!";
				link.l1 = "Ha-ha! Eu não faço caridade. Cai fora!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "O quê... Eu ouvi direito? Você vai mesmo doar dez mil pesos!? Que Deus te abençoe, eu aceito sua generosidade com gratidão. Vou mencionar seu nome na minha próxima carta ao nosso bispo, e rezaremos por você todos os dias! Isso é uma grande ajuda para a Igreja!";
				link.l1 = "'A quem muito é dado, muito será cobrado', não é? Boa sorte, padre.";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "A retribuição de Deus está esperando por você, patife! Zombar de um servo da santa igreja de Cristo é blasfêmia!";
				link.l1 = "Ha-ha! Eu não faço caridade. Cai fora!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Claro, meu filho. É nosso dever sagrado ajudar essas pessoas pobres e miseráveis. Farei como você pediu.";
			link.l1 = "Obrigado, padre. Vou doar dez peças de oito por cada prisioneiro que for batizado e receber os sacramentos.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Embora não seja necessário, aceito com gratidão sua taxa roubada. Seu dinheiro será destinado a várias missões em nossa paróquia. Você poderia me levar até seu navio?";
			link.l1 = "Sim, padre. Siga-me.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Two hours later"+ NewStr() +"Slaves were freed", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "I have only one ship in my squadron and it's "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "I have two ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "I have three ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "I have four ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "I have five ships in my squadron and the biggest one is "+iTemp+" rank.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Tudo depende do número total de navios no seu esquadrão e do tamanho deles.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Vai te custar "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", meu filho.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Posso te pagar essa quantia, padre. Pegue o dinheiro.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Infelizmente, eu não tenho tanto dinheiro comigo.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Muito bem, meu filho. Deixe-me pegar os vasos sagrados e iremos ao porto.";
			link.l1 = "Venha comigo, padre.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Several hours later"+ NewStr() +"The priest has held mass aboard your ship and blessed it", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Olá, capitão, permita-me apresentar-me. Sou padre e tenho bastante experiência como capelão em navios de guerra. Deixei meu último navio porque o capitão e eu tivemos algumas... divergências morais. Gostaria de me aceitar em sua tripulação?";
			link.l1 = "Um padre a bordo? Diga-me, padre, o que faz um capelão de navio?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = " Ora, é bastante óbvio. Rezo a Deus por você e sua tripulação, celebro missa diariamente, abençoo seus homens e ouço confissões antes das batalhas. A palavra de Deus fortalece as mãos e os espíritos da sua tripulação. Seus homens terão a oportunidade de comungar e se confessar regularmente. Acredite, um marinheiro em estado de graça resiste firme em situações onde um ímpio vacilaria.\nNão peço muito para mim: um pagamento único de cinquenta mil pesos para minha paróquia de origem, um beliche simples em uma cabine e refeições iguais às dos seus oficiais. Só isso.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Interessante... Você tem razão, um bom capitão deve cuidar não só do corpo da sua tripulação, mas também da alma deles. Seja bem-vindo a bordo, padre!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Não, padre. Me desculpe, mas não posso pagar pelos seus serviços.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Obrigado pela sua confiança, meu filho. Você gastou seu dinheiro com sabedoria. Mas aviso: só sirvo capitães dignos, sejam mercadores ou corsários, não importa. Mas jamais pregarei a bordo de um navio pirata!\nPortanto, se algum dia você içar a bandeira do diabo, deixarei seu navio no primeiro porto que encontrarmos.";
			link.l1 = "Vou pensar nisso, padre, e vou tentar não te decepcionar. Por favor, suba a bordo e se apresente à tripulação!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
		
		case "capellan_4":
			dialog.text = "Precisa de algo, meu filho?";
			link.l1 = "Não, não é nada, padre.";
			link.l1.go = "exit";
			link.l2 = "Padre, quero que o senhor desembarque no próximo porto. Não vou me explicar mais.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Muito bem, meu filho. Agora é você quem manda aqui. Vou deixar seu navio no próximo povoado.";
			link.l1 = "Obrigado por sua compreensão, padre.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Que vergonha, capitão! Eu te avisei que te deixaria se você hasteasse a bandeira pirata! Vou abandonar seu navio no próximo porto. Vou rezar para que você se arrependa logo e volte ao seio da Santa Madre Igreja.";
			link.l1 = "Bem, droga...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "Meu "+GetSexPhrase("filho","filha")+", eu preciso chegar a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" está ligado "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", por "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". Eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" por isso. O que me diz?";
			}
			else
			{
				dialog.text = "Meu "+GetSexPhrase("filho","filha")+", o Senhor age de maneiras misteriosas, e por isso procuro um capitão de confiança. Pode me ajudar a chegar a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", que fica em "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"? Eu entendo que isso é como uma viagem ao ardente Geena, já que nossos inimigos nunca dormem. E eu entendo que você não é Jesus Cristo, mas eu também não sou um apóstolo, então tenho algumas economias. Vai "+FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money))+" isso basta para você?";
			}
			link.l1 = "Concordo, padre.";
			link.l1.go = "passenger_1";
			link.l2 = "Me desculpe, padre, mas estou navegando em outra direção. Não posso ajudá-lo.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "É a vontade de Deus para todos, meu filho. Vou esperar por outro navio. Que a paz esteja com você!";
			link.l1 = "Adeus, padre.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Deus te abençoe! Você receberá seu pagamento quando chegarmos ao nosso destino.";
			link.l1 = "Vá para o meu navio, padre. Vamos partir em breve.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Obrigado, meu "+GetSexPhrase("filho","filha")+". Você cumpriu sua palavra, agora é minha vez. Pegue seu dinheiro, como prometi.";
			link.l1 = "Obrigado. Boa sorte, Padre.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Aqui. Pegue este pacote, meu filho. Lembre-se, você tem apenas duas semanas para entregá-lo. O pastor está esperando por ele. Vá, e que Deus esteja com você!";
			link.l1 = "Não vou decepcionar você, pai. Adeus.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Sim. Você pode encontrá-los em qualquer colônia "+NationNameGenitive(sti(npchar.nation))+". Traga todos os livros que encontrar para o nosso pastor na igreja. Que Deus te abençoe!";
			link.l1 = "Obrigado! Em breve você receberá seus livros.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "I am gathering money for building "+LinkRandPhrase("a chapel","an almshouse","a hospital")+". The local citizens give little in alms so I must ask prosperous men like you." break;
		case 1: sText = "I am gathering donations for our church. Sailors don't usually have much time to visit the house of God, but everyone must do his best in saving his own soul." break;
		case 2: sText = "I am gathering money to buy food and medicines for our poorhouse for the sick, widows, orphans, and infirm. Please donate sir, because there but for the grace of God go all of us." break;
		case 3: sText = "I am gathering money for new sacred vessels, the ones which we brought from Europe are battered with continual use. It's a duty for every Christian to take care of our Church." break;
		case 4: sText = "I am gathering money for our church's renovation, the roof is leaking terribly and the pews have to be repaired too. It's a duty for every Christian to take care of our Church." break;
		case 5: sText = "I am gathering money to pay the good artist who is able to paint the walls of our church and draw scenes from the Bible on them for those of our parish who cannot read. It's a duty for every Christian to take care about his Church." break;
		case 6: sText = "I am gathering money for a new high altar for our church. Our parish is poor and we would like a noble seat for the Blessed Sacrament. I do hope for your help." break;
		case 7: sText = "There are a lot of wounded sailors from pirate raids in our hospital. They need medicines and bandages. Pray help them, for you can really understand sufferings of the common sailors." break;
		case 8: sText = "I am trying to get money for clothes and food for our poorest citizens. The only hope they have is our holy church. Please help them." break;
		case 9: sText = "I am going to go deep in our island for missionary work to bring the light of Christ's Gospel to the lost souls of the pagan Indians. I am gathering funds for this expedition. Please help our good deed!" break;
	}
	return sText;
}
