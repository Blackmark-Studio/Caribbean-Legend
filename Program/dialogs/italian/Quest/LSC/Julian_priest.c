// брат Юлиан - священник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Non ho alcuna voglia di parlare con te. Aggredisci la povera gente di qui senza motivo e la provochi a menar le mani. Sparisci, miscredente!";
				link.l1 = "Come desideri...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Non mi stupisce che tu sia sopravvissuto. I sentieri del Signore sono misteriosi. La vita e la morte son nelle Sue mani.";
				link.l1 = "Sono pienamente d'accordo con te, fratello Julian.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Benvenuto nella santa chiesa della nostra Isola Giustizia, figliolo. Le porte son sempre aperte per te. Son frate Giuliano, e mi rallegra veder qualunque servo del nostro grande Signore.";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". Lieto d’incontrarti, fratello Giuliano.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Desideri qualcosa?";
				link.l1 = "Vorrei farti alcune domande sull'isola.";
				link.l1.go = "int_quests"; //информационный блок
				link.l2 = "Posso acquistare qualche pozione da te?";
				link.l2.go = "potion";
				link.l3 = "Hai qualche oggetto sacro da vendere?";
				link.l3.go = "amulet";
				link.l5 = "Volevo solo pregare un po’ qui e vedere come te la cavi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Spero che tu venga a trovarci più spesso nella nostra chiesa. Abbi cura della tua anima, figliolo. Posso anche curare il tuo corpo: qui non sono solo il pastore, ma pure il medico.";
			link.l1 = "Vorrei farti alcune domande sull’isola.";
			link.l1.go = "int_quests"; //информационный блок
			link.l2 = "Posso comprare qualche pozione da te?";
			link.l2.go = "potion";
			link.l3 = "Hai forse qualche reliquia sacra da vendere?";
			link.l3.go = "amulet";
			link.l4 = "Devo andare, fratello Giuliano. Ci vediamo!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "potion":
			dialog.text = "Certo, figliolo. Quale intruglio ti serve?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Una semplice pozione curativa.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Un elisir curativo.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Un antidoto.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Un miscuglio d’erbe.";
				link.l4.go = "potion4";
			}
			link.l5 = "Mi dispiace, fratello Giuliano, ho cambiato idea.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Una pozione? 90 pesos, figliolo.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Prendili, fratello Giuliano.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Non ho abbastanza monete adesso... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Un elisir? 500 pesos, figliolo.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Prendili, fratello Giuliano.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Non ho abbastanza monete adesso... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Un antidoto? 200 pesos, figliolo.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Prendili, fratello Giuliano.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Non ho abbastanza monete adesso... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Un miscuglio? 900 pesos, figliolo.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Prendili, fratello Giuliano.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Non ho abbastanza monete adesso... Tornerò più tardi.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ecco. Prendi la tua medicina. Che Dio ti accompagni!";
			link.l1 = "Grazie, fratello Giuliano.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
		break;
		
		case "amulet":
			bool bOK = (!CheckAttribute(npchar, "amulet_date")) || (GetNpcQuestPastDayParam(npchar, "amulet_date") >= 3)
			if (bOk && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > (10+hrand(110)))
			{
				npchar.quest.amulet = SelectLSCChurchAmulet();
				dialog.text = "Sì, posso darti degli amuleti sacri che tengono lontane ferite e malanni. Il prezzo è lo stesso per ogni amuleto – dieci dobloni d’oro. Posso offrirti "+XI_ConvertString(npchar.quest.amulet)+" oggi.";
				if (PCharDublonsTotal() >= 10)
				{
					link.l1 = "Sì, voglio comprare questo amuleto. Ecco il tuo oro.";
					link.l1.go = "amulet_pay";
					link.l2 = "Non ho bisogno di quest’amuleto, fratello Giuliano. Aspetterò finché non avrai ciò che mi serve.";
					link.l2.go = "exit";
					SaveCurrentNpcQuestDateParam(npchar, "amulet_date");
				}
				else
				{
					link.l1 = "Non ho abbastanza monete adesso... Tornerò più tardi.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "No, figliolo, purtroppo non ho altro da offrirti. Torna a trovarmi un altro giorno, magari allora avrò qualcosa per te.";
				link.l1 = "Affare fatto, fratello Julian.";
				link.l1.go = "exit";
			}
		break;
		
		case "amulet_pay":
			RemoveDublonsFromPCharTotal(10);
			GiveItem2Character(pchar, npchar.quest.amulet);
			Log_Info("You have received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Grazie, figliolo. Il tuo denaro sarà ben speso. Prendi il tuo amuleto e che il Signore ti benedica!";
			link.l1 = "Ti sono grato, fratello Giuliano.";
			link.l1.go = "exit";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto, forestiero.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui, fratello Giuliano?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Quanta gente conta la tua parrocchia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Chi commercia qui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "C’è qualche rischio che l’Isola venga distrutta? Tempeste, magari?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Mi dispiace...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Come tanti altri abitanti, figliolo. La mia nave fu inghiottita da una tempesta mentre viaggiavo da L’Avana verso la Nuova Spagna. Per grazia divina, sono sopravvissuto, e ora Lo servo qui, aiutando le anime perdute a ritrovare la loro rotta.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Meno di quanto desidero. La maggior parte dei Narvali preferisce la violenza alla clemenza, e i Rivados sono poveri diavoli smarriti. Seguono ciecamente i loro riti pagani, mettendo a repentaglio le loro anime immortali. Tra loro si nasconde un mago pericoloso: la Santa Inquisizione dovrà purificarlo.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Sancho Carpentero possiede la taverna sul Fleron, lì trovi da mangiare, da bere e un letto caldo. Axel Yost commercia ogni sorta di mercanzia sull' 'Esmeralda'. Chiedi in giro, figliolo, molti qua trovano cose curiose sul cerchio esterno.";
			link.l1 = "Grazie!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tutto è nelle mani del Signore, figliolo. In Lui crediamo, a Lui ci affidiamo. I guai grossi hanno sempre evitato la nostra Isola – le tempeste imperversano altrove, ma qui regna sempre la quiete.";
			link.l1 = "Grazie. Mi hai rincuorato.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che ci fai là, eh? Ladro!","Ma guarda un po’! Appena m’ero perso nei miei pensieri, tu hai pensato bene di ficcare il naso nei miei forzieri!","Hai deciso di ficcare il naso nei miei forzieri? Non penserai mica di farla franca!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai pensato di frugare nei miei forzieri? Non la passerai liscia, furfante!";
			link.l1 = "Stolta ragazza!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sai, qui non si corre in giro con la lama sguainata. Riponila, per cortesia.","Ascolta, non fare il cavaliere errante che corre con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Bene.","D'accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di rinfoderare la lama.","Ascolta, sono un cittadino di questa città e ti chiederei di rinfoderare la lama.");
				link.l1 = LinkRandPhrase("Bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre armato. Potrei innervosirmi...","Non mi piace quando la gente mi passa davanti con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Me lo sto portando via.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string SelectLSCChurchAmulet();
{
	string sAmulet;
	switch (hrand(3))
	{
		case 0: sAmulet = "amulet_2"; break;
		case 1: sAmulet = "amulet_3"; break;
		case 2: sAmulet = "amulet_6"; break;
		case 3: sAmulet = "amulet_7"; break;
	}
	return sAmulet;
}
