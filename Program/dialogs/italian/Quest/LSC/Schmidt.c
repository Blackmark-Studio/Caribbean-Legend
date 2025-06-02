// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Ascolta, signore, perché hai lasciato parlare i pugni, eh? Non hai niente da fare nella mia officina finché non sei nostro nemico. Fuori di qui!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Ho sentito parlare delle tue imprese. È cosa buona che tu sia divenuto amico di Donald e nostro alleato. I Narvali sanno apprezzare l’amicizia, questo te lo posso giurare.";
					link.l1 = "Spero di sì. Posso contare ora sul tuo aiuto?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "E allora? Che cosa vuoi?";
					link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". E io sto solo passeggiando, cercando di conoscere la gente. Ti disturbo forse?";
				link.l1.go = "meeting";
				}
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Ho sentito parlare delle tue imprese. È cosa buona che tu sia divenuto amico di Donald e nostro alleato. I Narvali sanno apprezzare l’amicizia, te lo posso assicurare.";
					link.l1 = "Spero di sì. Posso contare ora sui tuoi servigi?";
					link.l1.go = "friend";
				}
				else
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Vuoi parlare ancora? Mi dispiace deluderti, ma non ho né tempo né voglia per questo.";
					link.l1 = "Va bene, non ti disturberò oltre.";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Esatto! Mi stai dando fastidio, forestiero. Sono Jurgen Schmidt, armaiolo e fabbro del clan Narvalo. Fornisco armi alla mia gente. Ma serve tempo per forgiare una buona lama, una chiave, una serratura o riparare il meccanismo di un moschetto da torre. Ci vogliono ore, pazienza e molta attenzione. Ecco perché non sopporto chi mi disturba.";
			link.l1 = "Fabbrichi armi? Posso commissionarti qualcosa?";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "No. Fabbro armi solo per chi appartiene al clan dei Narvali. Questa è la mia regola e la manterrò. Quindi non ci sperare, messere. Unisciti al nostro clan o almeno diventa nostro alleato, e allora ne riparleremo.";
			link.l1 = "Va bene. Allora ti lascio in pace. Scusa se t’ho disturbato!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "friend":
			dialog.text = "Puoi parlare. Un amico dei Narvali è amico mio, dunque ti presto orecchio.";
			link.l1 = "Vorrei ordinare una lama.";
			link.l1.go = "blade";
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l2 = "Ho sentito che hai forgiato una lama speciale per il compianto Alan Milrow. Ho visto quella spada larga, è un’arma da vero uomo di mare. Posso ordinare qualcosa del genere?";
				link.l2.go = "narval";
			}
			link.l3 = "Non ho ancora idee. Ci penserò su e poi tornerò!";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "Jurgen":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Dunque non sei annegato? Che diavolo, davvero sei vivo?";
				link.l1 = "Non temere, Jurgen. Sono ancora in vita! Non avevo proprio intenzione di annegare...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				NextDiag.TempNode = "Jurgen";
				break;
			}
			dialog.text = "Ah, "+GetFullName(pchar)+"!   Cosa vuoi, forestiero?";
			if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
			{
				if (GetCharacterItem(pchar, "jewelry11") >= 3)
				{
					link.l4 = "Ti ho portato i tuoi tre pezzi di ferro speciale, come mi hai chiesto. Guarda un po', è quello che volevi?";
					link.l4.go = "narval_7";
				}
				if (CheckCharacterItem(pchar, "meteorite"))
				{
					link.l5 = "Dai un'occhiata, Jurgen. Ho trovato un lingotto di ferro curioso sul fondo, ma pesa assai più di quanto volevi. Non meno di cinque libbre.";
					link.l5.go = "narval_7_1";
				}
			}
			if (!CheckAttribute(npchar, "quest.blade_done"))
			{
				link.l1 = "Vorrei ordinare una lama.";
				if (!CheckAttribute(npchar, "quest.blade_rules")) link.l1.go = "blade";
				else link.l1.go = "blade_4";
			}
			if (CheckAttribute(npchar, "quest.blade_payseek"))
			{
				link.l1 = "Ti ho portato altri dobloni come pagamento per la lama.";
				link.l1.go = "blade_3";
			}
			if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
			{
				link.l2 = "Ho sentito dire che hai forgiato una lama speciale per il defunto Alan Milrow. Ho visto quella spada larga, è davvero un'arma notevole. Posso commissionarti qualcosa del genere?";
				link.l2.go = "narval";
			}
			if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
			{
				link.l1 = "Sono qui per il mio ordine. Dovrebbe essere già pronto, o sbaglio?";
				link.l1.go = "blade_done_2";
			}
			link.l3 = "No, non è nulla, volevo solo darti il mio saluto.";
			link.l3.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		// --> заказ клинков
		case "blade":
			dialog.text = "Va bene. Ma ho delle richieste particolari per ogni incarico, quindi ascolta bene prima.";
			link.l1 = "Sono tutto orecchi.";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Puoi ordinare solo una lama da me, e soltanto una volta. Non forgerò un’arma su misura: puoi scegliere solo il tipo – stocco, sciabola o spadone. Rifletti bene prima di decidere, ché le proprietà e la qualità della lama dipenderanno dai materiali che ho a disposizione in questo momento.\nAdesso. Mi serviranno venti giorni per completare il tuo ordine. Accetto solo dobloni. Mille monete. Tutto pagato in anticipo.";
			link.l1 = "Davvero! Roba da ricchi...";
			link.l1.go = "blade_2";
		break;
		
		case "blade_2":
			dialog.text = "È caro, lo ammetto. Ma forgio lame d’eccellenza, quindi il prezzo è ben meritato. Tocca a te decidere, senza fretta né pressioni.";
			link.l1 = "Ho capito, Jurgen. Sì, voglio fare un ordine.";
			link.l1.go = "blade_3";
			link.l2 = "Hm. Devo riflettere prima di chiederti qualcosa. Ne parleremo più tardi!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
			npchar.quest.blade_rules = "true";
			npchar.quest.blade_dublon = 1000;
			AddQuestRecord("LSC", "17");
		break;
		
		case "blade_3":
			dialog.text = "Molto bene. Dammi allora i tuoi dobloni.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.blade_pay = GetCharacterItem(pchar, "gold_dublon");
				link.l1 = "Ecco, prego. Ho "+FindRussianQtyString(sti(npchar.quest.blade_pay))+".";
				link.l1.go = "blade_pay";
			}
			link.l2 = "Hm. Purtroppo ora non ne ho con me. Ma te li porterò di certo, e potremo continuare questa nostra chiacchierata.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Jurgen";
		break;
		
		case "blade_4":
			dialog.text = "Dunque, è questa la tua decisione finale? Ne sei davvero sicuro?";
			link.l1 = "Sì, lo sono.";
			link.l1.go = "blade_3";
		break;
		
		case "blade_pay": // оплата
			if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
			{
				npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.blade_dublon)-sti(npchar.quest.blade_pay);
			npchar.quest.blade_dublon = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.blade_pay));
			Log_Info("You have given "+sti(npchar.quest.blade_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Splendido. Mi hai pagato per il mio lavoro e i materiali, quindi posso cominciare subito.";
				link.l1 = "Posso fare un ordinazione?";
				link.l1.go = "blade_done";
			}
			else
			{
				dialog.text = "Va bene. Accetto i tuoi dobloni. Devi portarmi "+FindRussianQtyString(sti(npchar.quest.blade_dublon))+" ancora.";
				link.l1 = "Te li porterò quando li avrò.";
				link.l1.go = "exit";
				npchar.quest.blade_payseek = "true";
			}
		break;
		
		case "blade_done":
			DeleteAttribute(npchar, "quest.blade_payseek");
			dialog.text = "Certo! Quale tipo ti attira di più? Stocchi, sciabole o spadoni?";
			link.l1 = "Stocchi. Mi piacciono le armi eleganti e leggere.";
			link.l1.go = "rapier";
			link.l2 = "Sciabole. Secondo me, sono la scelta migliore.";
			link.l2.go = "sabre";
			link.l3 = "Spadoni, senza dubbio! Taglia e affetta!";
			link.l3.go = "palash";
		break;
		
		case "rapier":
			npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
			dialog.text = "Come desideri. Torna a ritirare la tua richiesta tra venti giorni, non prima.";
			link.l1 = "Grazie! Ci vediamo tra venti giorni. Addio, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "sabre":
			npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
			dialog.text = "Come desideri. Torna per il tuo ordine tra venti giorni, non prima.";
			link.l1 = "Grazie! Ci vediamo tra venti giorni. Addio, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "palash":
			npchar.quest.blade_done = SelectJurgenBladeDone("palash");
			dialog.text = "Come desideri. Torna per il tuo ordine fra venti giorni, non prima.";
			link.l1 = "Grazie! Ci vediamo tra venti giorni. Addio, Jurgen.";
			link.l1.go = "blade_done_1";
		break;
		
		case "blade_done_1":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "blade_date");
			NextDiag.CurrentNode = "Jurgen";
			AddQuestRecord("LSC", "18");
		break;
		
		case "blade_done_2":
			dialog.text = "Sì. La tua lama è pronta. Prendila pure, usala. Capirai che vale ogni moneta appena la sfiori.";
			link.l1 = "Grazie, Jurgen.";
			link.l1.go = "blade_done_3";
		break;
		
		case "blade_done_3":
			DialogExit();
			NextDiag.CurrentNode = "Jurgen";
			GiveItem2Character(pchar, npchar.quest.blade_done);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "blade_date");
		break;
		
		// заказ палаша Нарвал для Мэри
		case "narval":
			dialog.text = "Ahimè, amico mio, devo rifiutare per due motivi. Primo, forgio una simile spada solo per un membro del clan Narvalo, e solo per qualcuno di davvero speciale. Secondo, mi mancano i materiali necessari.";
			link.l1 = "E quale sarebbe questo ferro speciale che ti serve? Ho sentito dire che l’hanno tirato su dal fondo...";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Esatto. Ci sono frammenti di questo metallo sparsi ovunque sulla nostra secca. Non so come ci siano arrivati. Ma il ferro è unico: non arrugginisce mai e le lame forgiate con esso restano sempre affilate. Se riuscissi a procurarti quel ferro, forse potremmo risolvere la questione. Ma c'è ancora un problema, tu non sei un Narvalo...";
			link.l1 = "Mm. Conta davvero qualcosa?";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Sì. Potrai pensare che sia una mia stravaganza, ma forgerò una spada così solo per un Narvalo.";
			link.l1 = "Ebbene... Va bene, lo accetto. Ma ho un’idea. Posso ordinare questa lama per un membro del clan Narvali?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Hm. Suppongo che tu possa, se mi porterai il ferro. Non andrà contro i miei principi... E per chi vuoi che io forgia la spadona?";
			link.l1 = "Per la Rossa Mary. Viene dal clan dei Narvali e merita di possedere un’arma tanto eccelsa.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Ah! Ci potevo arrivare anch'io, maledetta vecchiaia... Beh, sono d’accordo. Son certo che Mary sarà davvero felice di ricevere un dono così... Portami il ferro e ti forgerò la spada larga. Prendo quel che serve per la lama... bah, lasciamo stare, la farò gratis. Sarà un regalo non solo tuo, ma anche mio.";
			link.l1 = "Grazie!   Quanta ferraglia ti serve?";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Quei pezzi che abbiamo trovato sul fondo erano proprio uguali – un chilo ciascuno. Me ne servono tre così.";
			link.l1 = "D’accordo. Cercherò di trovarli. E ci rivedremo per parlarne.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			DialogExit();
			npchar.quest.narval_blade = "ferrum";
			NextDiag.CurrentNode = "Jurgen";
			// кладем гигантский кусок метеорита на дно
			sld = ItemsFromID("meteorite");
			sld.shown = true;
			sld.startLocation = "underwater";
			sld.startLocator = "item"+(rand(7)+1);
			Log_TestInfo("Meteorite in the locator " + sld.startLocator);
			pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
			pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
			pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
			AddQuestRecord("LSC", "19");
		break;
		
		case "narval_7":
			RemoveItems(pchar, "jewelry11", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Fammi vedere... Sì, proprio così! È stato arduo scovare pezzi così minuti sul fondo?";
			link.l1 = "Ebbene, che posso dire... Mary merita proprio tutti questi guai, non credi?";
			link.l1.go = "narval_8";
			pchar.quest.LSC_narval_ferrum.over = "yes"; //снять прерывание
		break;
		
		case "narval_7_1":
			RemoveItems(pchar, "meteorite", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Vediamo un po'... Per la barba di Nettuno! Sì, è proprio il ferro di fondo, ma pezzi tanto grossi non ne ho mai visti prima. Questo basterà per forgiare la spada larga. È stata dura trovarlo?";
			link.l1 = "Ebbene, che posso dire... Maria vale questi guai, non credi?";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			dialog.text = "Mi piaci sempre di più, "+pchar.name+"... Molto bene allora. Ora tocca a me lavorare per la nostra splendida Amazzone. Ci vorranno due giorni per forgiare la spada larga, metterò da parte gli altri ordini.\nPortami Mary dopodomani. Non dirle nulla, è una sorpresa. Sarà felice come una bambina.";
			link.l1 = "Va bene, Jurgen. Affare fatto! Ci vediamo dopodomani!";
			link.l1.go = "narval_9";
		break;
		
		case "narval_9":
			DialogExit();
			npchar.quest.narval_blade = "work";
			NextDiag.CurrentNode = "narval_10";
			SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
			AddQuestRecord("LSC", "21");
		break;
		
		case "narval_10":
			dialog.text = ""+pchar.name+", non scocciarmi. Vuoi che la spada sia pronta in tempo, vero?";
			link.l1 = "Sì, certo. Me ne vado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_10";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai laggiù, eh? Ladro!","Guarda un po'! Appena mi sono perso nei miei pensieri, tu hai deciso di curiosare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, furfante!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sappi che qui non è tollerato andare in giro con la lama sguainata. Riponila via.","Ascolta, lascia stare il cavaliere errante con la spada sguainata. Mettila via, non fa proprio per te...");
			link.l1 = LinkRandPhrase("Va bene.","Va bene.","Come tu dici...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere la lama nel fodero.","Ascolta, sono cittadino di questa città e ti chiedo di rinfoderare la lama.");
				link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre in giro con l’arma sguainata. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","La porto via.");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
		case "rapier":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_18"; 
			else sBlade = "q_blade_16";
		break;
		
		case "sabre":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_19"; 
			else sBlade = "q_blade_10";
		break;
		
		case "palash":
			if (sti(pchar.rank) > 15) sBlade = "q_blade_21"; 
			else sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
