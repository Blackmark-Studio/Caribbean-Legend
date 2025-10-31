#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... nur der Teufel und ich kennen den Ort, und der Letzte, der noch steht, bekommt alles!\n",
"... und Maynard sagte: „Ich erwarte keine Gnade, also solltest du das auch nicht tun“.\n",
"... er war der Betrunkene, der vorschlug, die ganz besondere Hölle genau dort zu arrangieren, nur um zu sehen, wer von uns es länger aushält.\n",
"... lustige Geschichte von meinem alten Freund aus Porto Belo...\n",
"... Nein, meine Herren, das sind beschissene Anekdoten. Ich habe ein paar gute Geschichten, um Ihre Ohren zu füllen.\n",
"... Ich kann nicht viel über den „Fliegenden Holländer“ sagen. Ich habe sie nie gesehen. Ich bin einmal an Bord einer seltsamen Brigantine gegangen, leer, keine einzige Seele an Bord. Raten Sie mal, was? 1700 Fässer Wein im Laderaum... Das nenne ich Glück!\n",
"... Ich neige dazu zu glauben, dass dieser „Fliegende Holländer“ Mist eine Fälschung ist.\n",
"... Hast Du schon einmal davon gehört, dass ich in Key West einen Granatenschock erlitten habe? Obwohl es keine sichtbaren Schäden gab, lag ich zwei Monate lang. Und dann überredete mich meine Leidenschaft, zu beichten. Man sagt, mit Gottes Hilfe wird die Sache gut ausgehen ... Nun, ich ging hin, und der Priester fragte: 'Hast du viele Menschen getötet, mein Sohn?' 'Und wie viele Schiffe sind gesunken?' - 'Viele' - antworte ich. Und er lässt nicht locker: 'Hast du viele Frauen verführt?' Da sage ich: 'Padre, ich bin nicht hierher gekommen, um zu prahlen'. Ha-ha-ha-ha\n",
"... Aber in Santa Cruz gab es einen Fall beim Anlegen. Mit einem Schrei 'Vorsicht!' Mein Matrose wirft eine Peitsche und trifft den einheimischen Schaulustigen direkt an der Stirn! Der schreit und fällt gefühllos um. Der Segler war erschrocken, wartete nicht auf die Rampe, sondern sprang auf den Steg und gab dem armen Kerl Wasser. Schließlich wachte er auf und sagte dem Matrosen: „Du musst ‚Achtung‘ rufen, wenn Gefahr droht, nicht ‚Vorsicht‘, du Idiot! Ha, ha, ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Ich steckte einmal in Florida fest...",
"... Ich kann nicht viel über den „Fliegenden Holländer“ sagen. Ich habe sie nie gesehen. Ich bin einmal an Bord einer seltsamen Brigantine gegangen, leer, keine einzige Seele an Bord. Raten Sie mal, was? 1700 Fässer Wein im Laderaum... Das nenne ich Glück!...",
"... Sie hat den armen Kerl mitten in der Taverne umgebracht, nachdem er vorgeschlagen hatte, ihre „Offiziersfähigkeiten“ im Obergeschoss zu testen..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Anständige Kapitäne sind in diesen Gewässern eine seltene Rasse.",
"Adel ist heutzutage aus der Mode.",
"Oh, das ist ein anständiger Kapitän, ganz anders als ihr, ihr Halsabschneider! He-he!",
"Meine Herren, wir haben einen anständigen Kapitän an unserem Tisch, der schon unzählige Male durch Feuer und Wasser gegangen ist. Also, was können Sie uns sagen, verehrter Herr?",
"Jetzt gibt es einen weiteren glorreichen Korsaren, der nicht gewohnt ist, nach königlichen Straßen zu suchen.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Jetzt gibt es noch einen Piraten!",
"Meine Herren, wir haben einen Glücksritter an unserem Tisch, nehme ich an?",
"Ich rieche Schießpulver und Blut! Ein Filibuster an Bord!",
"Oh, meine Herren, das ist ein erfahrener Korsar, der in netter Gesellschaft bei einem Becher Rum sicher etwas zu erzählen hat... Wollt Ihr Euch uns anschließen?",
"Oh, ich rieche Schießpulver... Meine Herren, wir haben hier einen weiteren glorreichen Korsaren, der bei seiner Beichte sicher viel zu erzählen haben wird... Ha, ha, ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Sie sehen einen Fehler... melden Sie ihn AT, für die Marine.";
//	link.l1 = "Sicherlich!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hey, verschwinde! Wenn du meinen Handel ruinierst, reiße ich dir das Herz raus!";
			link.l1 = RandPhraseSimple("Du wagst es, mich zu bedrohen, du Tölpel?!","Ich werde dich an deinen Worten ersticken lassen, Schurke!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, ich verstehe. Geschäft ist Geschäft. Viel Glück.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "Guten Tag, mein Name ist "+GetFullName(NPChar)+", und deiner?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "Mein Name ist "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Alkohol für alle! Ich bin Kapitän "+GetFullName(pchar)+".","Ich bin Kapitän von der '"+PChar.Ship.Name+" und ein paar hundert echte Teufel! He-he! Mein Name ist "+GetFullName(pchar)+"."),RandPhraseSimple("Erlauben Sie mir, mich vorzustellen, meine Herren. Ich bin Kapitän "+GetFullName(pchar)+".","Wir wurden noch nicht vorgestellt. Ich bin der Kapitän von der '"+PChar.Ship.Name+" unter der Flagge von "+NationNameGenitive(sti(PChar.nation))+". Mein Name ist "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Nun, hier kennt mich jeder! Ich bin "+GetFullName(NPChar)+". Schön dich zu treffen! Was kann ich für dich tun?";
		link.l1 = RandPhraseSimple("Ich habe Geschäfte mit dir!","Ich möchte mit dir sprechen...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Nun, hier kennt mich jeder! Ich bin "+GetFullName(NPChar)+", Kapitän "+xiStr(sld.BaseName+"Konto")+" "+NPChar.Ship.Name+".";
			link.l2 = "Wie wäre es, wenn du dich mir anschließt? Zwei Schiffe sind besser als eins. Wir können zusammen ein ordentliches Geschäft machen.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Möchtest du als Offizier auf meinem Schiff dienen?","Ich denke, du würdest als Offizier auf meinem Schiff gut zurechtkommen. Was sagst du dazu?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-Test) Quests.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-Test) Duelle.";
			link.l8.go = "outraged";
		}
		link.l9 = "Nichts.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "He, verzieh dich, ja! Wenn du mein Geschäft verdirbst, reiße ich dir das Herz heraus!";
			link.l1 = RandPhraseSimple("Du wagst es, mich zu bedrohen, du Tölpel?!","Ich werde dich an deinen Worten ersticken lassen, Schurke!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, ich verstehe. Geschäft ist Geschäft. Viel Glück.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Ich habe dir heute schon alles erzählt!";
			link.l1 = "Oh, ja...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("Was brauchst du "+GetFullName(pchar)+"?","Wer ist da? Ach, du... Verschwinde, ich bin nicht in Stimmung...");
		link.l1 = RandPhraseSimple("Wie wäre es mit einem Geschäft?","Ich wollte mit dir reden...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Oh, schau mal wer da ist! Es ist "+GetFullName(pchar)+". Irgendwelche Neuigkeiten?","Wie geht es Ihnen? Was kann ich für Sie tun?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase("Was sind die Neuigkeiten?","Was gibt's Neues im Archipel?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+"Was gibt's Neues?",PGG_Meet_BadRep[iAns]+"Was sind die Neuigkeiten im Archipel?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Wie wäre es, wenn du dich mir anschließt? Zwei Schiffe sind besser als eins. Wir können ordentliche Geschäfte zusammen machen.","Sie sehen aus wie ein erfahrener Kapitän. Möchten Sie unter meiner Flagge segeln?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Oh, wehe mir... Mein Schiff sank!","Schau mal wer da ist?! Was hat dich hierher gebracht? Übrigens habe ich mein Schiff verloren...");
				link.l3 = RandPhraseSimple("Schade. Vielleicht hast du das nächste Mal mehr Glück.","Du sagst es... Nun, es ist Zeit für mich zu gehen. Auf Wiedersehen.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Möchten Sie als Offizier auf meinem Schiff dienen?","Ich denke, du würdest dich gut als Offizier auf meinem Schiff machen. Was sagst du dazu?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Welche Neuigkeiten gibt es?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Was für eine hässliche Visage. Es bettelt geradezu um eine Tracht Prügel.","Oh, unser 'Freund'. Möchtest du ein paar neue Löcher in der Brust?");
			link.l8.go = "outraged";
		}
		link.l9 = "Nichts.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Ich habe dir bereits gesagt, dass ich nicht interessiert bin.","Ich dachte, wir hätten bereits alles besprochen.");
			link.l1 = RandPhraseSimple("Wie könnte ich vergessen?","Gut genug. Tschüss.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... vielleicht nicht. Nicht ein zweites Mal.","Und du dachtest, ich würde zweimal auf diesen Köder reinfallen?!");
			link.l1 = RandPhraseSimple("Nun, wie du willst...","Also gut. Bis dann.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nein, ich denke nicht.","Nein, ich bin ein Kapitän und ich will nicht als Offizier dienen.");
			link.l1 = RandPhraseSimple("Nun, wie du willst...","In Ordnung. Dann sehen wir uns.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Du hast bereits ein vollständiges Set.","Ich glaube nicht, dass du bereit bist, mir Befehle zu geben.");
			link.l1 = RandPhraseSimple("Schade...","Nun, das Schicksal hat anders entschieden.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Das ist genau das, was ich brauchte! Unsere Klingen werden das Blut unserer Feinde kosten! Aber es gibt ein Problem - ich brauche noch "+NPChar.Quest.Officer.Price+" Pesos, um meine Schulden zu begleichen.","Du siehst aus wie ein echter alter Seebär. Und wenn du bereit bist "+NPChar.Quest.Officer.Price+" Pesos zu zahlen, könnten wir gut zusammenarbeiten."),LinkRandPhrase("Ihr Angebot schmeichelt mir sehr. Ich werde für Sie für ein ziemlich bescheidenes Honorar arbeiten, "+NPChar.Quest.Officer.Price+" Pesos.","Hmm... Du siehst aus wie ein erfahrener Seemann. Vielleicht sollte ich dein Angebot annehmen, wenn du bereit bist, mich mit "+NPChar.Quest.Officer.Price+" Pesos zu bezahlen.","Ich denke, wir werden gut zusammenarbeiten, Kapitän. Nur "+NPChar.Quest.Officer.Price+" Pesos, und wir haben einen Deal."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("Das passt mir gut. Ich hoffe nur, dass Sie mir nicht täglich etwas in Rechnung stellen werden.", "Das ist sehr teuer, aber ich hoffe, Sie sind es wert."), 
				LinkRandPhrase("Ich stimme zu. Betrachten Sie sich als Teil der Crew.", "Hm... Ich denke, ich kann es mir leisten.", "Sieht aus, als wären Sie es wert. Nimm die Münzen!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("Du bist nicht so viel wert. Wir sehen uns...", "Zu verdammt teuer für mich."), 
				LinkRandPhrase("Ja... Gier ist keine Sünde...", "Lachst du über mich? Für so viel Geld kann ich ein Dutzend wie dich kaufen.", "Das ist eine Abzocke. Woher soll ich so viel Geld nehmen?")), "exit");
		link.l3 = "Hmm... und wie qualifiziert sind Sie eigentlich?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Ich denke, Sie haben Geldprobleme, Kapitän.";
			link.l1 = "Oh... in der Tat.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Ausgezeichnet!","Ich habe Sie nie bezweifelt, Kapitän.");
		link.l1 = "Sei nicht spät zur Abfahrt.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Ein Fehler, informiere die Entwickler";
		link.l1 = "Werde ich!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Ich habe dir schon gesagt, dass ich nicht interessiert bin.","Ich dachte, wir hätten bereits alles besprochen.");
			link.l1 = RandPhraseSimple("Wie könnte ich vergessen?","Gut genug. Tschüss.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Mit dir segeln?! Werd' erstmal ein bisschen älter!","Ich glaube nicht, dass ich daran interessiert bin!");
			link.l1 = RandPhraseSimple("Nun, wie du willst...","In Ordnung. Bis dann.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Nein, ich denke nicht.","Nein, danke. Ich diene niemandem gern.");
			link.l1 = RandPhraseSimple("Nun, wie du willst...","Also gut. Tschüss dann.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Ich mag dich! Du hast einen Deal! Ich kann schon das Klimpern der Pesos in unseren Taschen hören!","Du bist schlau "+GetSexPhrase("Kumpel","Fräulein")+"... Wir sollten gut zusammenarbeiten!"),LinkRandPhrase("Ich mag dein Angebot. Ich stimme zu.","Das ist interessant. Weißt du, ich glaube, dass wir zusammen mehr erreichen können!","Das sollte Spaß machen. Sie haben einen Deal!"));
			link.l1 = RandPhraseSimple("Großartig! Ich werde auf dich am Meer warten!","Abgemacht! Wir werden eine großartige Crew sein.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Ich denke, du hast schon genug Gefährten.","Du hast schon genug Schiffe - warum brauchst du mehr?");
			link.l1 = "Ja... Vielleicht hast du recht.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Ich habe genug von dir!!! Ich verlasse deine Staffel!","Meine Geduld ist am Ende! Ich gehe jetzt."),RandPhraseSimple("Ich habe genug von deinen Eskapaden, 'Admiral'... Erlaube mir, meinen Abschied zu nehmen.","Ich habe genug von deinem Kommando und verlasse dein Geschwader."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Gut, dann verschwinde.","In Ordnung, geh wohin du willst."),RandPhraseSimple("Gut. Ich werde dich nicht festhalten.","Das ist deine Wahl. Ich wünsche dir günstigen Wind."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... wie wäre es mit einer kleinen Prämie?","Verdammt! Oh, zur Hölle, vielleicht würdest du doch bleiben? Ich kann sogar deinen Matrosen etwas extra zahlen!"),RandPhraseSimple("Ich würde es hassen, mich von dir zu trennen ... Vielleicht kann eine kleine Entschädigung unsere Streitigkeiten beilegen?","Wie wäre es mit einer Gehaltserhöhung?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Eines Mal war genug für mich. Ich werde deinen Versprechen nicht mehr vertrauen!","Sie werden mich mit keinem Geld ködern! Meine Entscheidung ist endgültig!");
			link.l1 = RandPhraseSimple("Also, viel Glück für dich.","Dann verschwinde und sorge dafür, dass ich dich nie wieder sehe!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Eine Prämie? Gut! Eine Summe von "+NPChar.Quest.Companion.Price+" Pesos werden mir gut passen.","Nun, vielleicht, wenn Sie bereit sind, meiner Crew "+NPChar.Quest.Companion.Price+" Pesos zu bezahlen, könnte ich sie vielleicht überreden zu bleiben."),RandPhraseSimple("Also gut! Ich kann für eine kleine Prämie von "+NPChar.Quest.Companion.Price+" pesos bleiben!",NPChar.Quest.Companion.Price+" wird mich und meine Mannschaft für einige Zeit zufriedenstellen."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Lachst du über mich oder was?! Verschwinde, jetzt!","Ha! Ich würde dieses Geld viel lieber für etwas Nützlicheres ausgeben!"),RandPhraseSimple("Oh nein. Ich bin nicht so reich!","Auf Wiedersehen. Ich werde nicht so viel bezahlen."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Ausgezeichnet! Hier ist deine Prämie!","Ich habe nie daran gezweifelt, dass es nur um Geld ging!"),RandPhraseSimple("Ausgezeichnet! Schön, dass du bleibst.","Hier ist, was ich versprochen habe."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Wähle die Vorlage!";
		link.l1 = "Quest 1 Vorlage - Meer.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "AUSGEWÄHLT! Quest 1 Vorlage - Land.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Quest 1 Vorlage - Meer.";
		link.l1 = "Oh, ja...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "AUSGEWÄHLT! Quest 1 Vorlage - Land.";
		link.l1 = "Oh, ja...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Ich habe dir bereits alles erzählt!";
			link.l1 = "Oh, ja...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Welches Geschäft?.. Hic! Siehst du nicht - ich und die Kumpels haben eine gute Zeit!.. Hic...","Ehh... Kein Geschäft heute!");
		link.l1 = "Ich sehe...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "Welches Gespräch? Obwohl, du bist genau rechtzeitig. Wenn es ums Geschäft geht, bin ich immer bereit!";
					link.l1 = "Hmm. Wovon sprichst du?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...nur ich und der Teufel kennen diesen Ort, und der Letzte, der am Leben bleibt, bekommt alles!..","...und Meinard antwortete: 'Ich erwarte keine Gnade von dir und werde dir auch keine gewähren'","...und einmal auf offener See, als er schon ein bisschen beschwipst war, schlug er vor: 'Lassen wir uns dort zur Hölle machen und sehen, wer bis zum Schluss steht'.")+PCharRepPhrase(LinkRandPhrase("Jetzt gibt es noch einen Piraten!","Meine Herren, wir haben einen Glückspilz an unserem Tisch, schätze ich?","Ich rieche Schießpulver und Blut! Ein Freibeuter backbord!"),LinkRandPhrase("Anständige Kapitäne sind eine seltene Rasse in diesen Gewässern.","Adel ist heutzutage aus der Mode gekommen.","Oh, jetzt gibt es einen anständigen Kapitän, überhaupt nicht wie du, Halsabschneider! He-he!"));
						link.l1 = "Ich schreie nicht, ich sage dir - es gibt ein profitables Geschäft!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Vorsichtig, vorsichtig! Oh! Ich kenne dich. Du bist "+GetFullName(PChar)+". Ich habe viel von dir gehört.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Ich bin Kapitän "+GetFullName(pchar)+".","Ich bin Kapitän von der '"+PChar.Ship.Name+" und ein paar hundert echte Teufel! He-he! Mein Name ist "+GetFullName(pchar)+".")+" Aber ich erinnere mich nicht an dich.",RandPhraseSimple("Erlauben Sie mir, mich vorzustellen, Herren. Ich bin Kapitän "+GetFullName(pchar)+".","Wir wurden noch nicht vorgestellt. Ich bin der Kapitän von der '"+PChar.Ship.Name+" unter der Flagge von "+NationNameGenitive(sti(PChar.nation))+". Mein Name ist "+GetFullName(pchar)+".")+"Aber ich erinnere mich nicht an dich.");
//			link.l1 = "Hmm... und wer bist du? Ich erinnere mich nicht an dich.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Hallo, "+GetFullName(NPChar)+". Wie ist das Leben?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Ich bin "+GetFullName(NPChar)+", Kapitän "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". Der berüchtigtste Freibeuter auf der ganzen spanischen Hauptstadt.",". Nur ein Seemann.");
		link.l1 = "Ja, jetzt werde ich mich an dich erinnern.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Ich habe Geschäfte mit dir, "+GetSexPhrase("Kumpel","lass")+". Ich weiß, dass ich dir vertrauen kann, aber ich kann das einfach nicht in der Taverne besprechen - zu viele falsche Ohren. Ich werde auf meinem Schiff auf dich warten. Der Name meiner alten Kiste ist '"+NPChar.Ship.Name+"'.";
//			link.l1 = "Spuck es jetzt aus, ich habe keine Zeit für Besuche.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Ich habe eine interessante Angelegenheit für dich und deine Halsabschneider.","Wenn wir uns zusammentun, könnten wir tatsächlich einen wirklich großen Preis gewinnen! Natürlich müssen wir dabei jemanden umbringen. He-he."),RandPhraseSimple("Ich habe ein Geschäftsangebot für Sie, Kapitän.","Kapitän, Ihr Ruf ist unübertroffen, und daher biete ich Ihnen an, an einer verführerischen Affäre teilzunehmen."))+RandPhraseSimple("Nur zwischen uns beiden. Lassen Sie uns es in der Offizierskabine von '."+NPChar.Ship.Name+" besprechen, über dem Krug mit dem köstlichsten Bier. Heute.","Wir sollten es dort nicht besprechen, lassen Sie uns die Details auf der '"+NPChar.Ship.Name+" in Ruhe und Frieden verhandeln. Und bitte nehmen Sie sich nicht zu viel Zeit.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Zum Teufel mit diesen Verzögerungen! Wenn es gut ist, will ich es sofort wissen, und erst recht, wenn es schlecht ist!","Es hat keinen Sinn in solchen kurzen Drähten! Es gibt einen passenden Raum in der Taverne - lass uns dorthin gehen!"),RandPhraseSimple("Und warum können wir Ihr Angebot nicht gleich hier, im Wirtshauszimmer, besprechen?","Ich fürchte, ich habe wenig Lust, Ihr Schiff zu besuchen. Wenn Sie etwas brauchen, spucken Sie es hier und jetzt aus!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... Wir sollten nicht über Geschäfte in der Taverne diskutieren - zu viele falsche Ohren. Ich warte auf dich auf meinem Schiff '"+NPChar.Ship.Name+". Wir werden dort reden.";
			link.l1 = "Ich habe keine Zeit und ich mag es nicht zu besuchen.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ich komme. Aber wenn du nur meine Zeit verschwendest, reiße ich dir die Zunge heraus!",RandSwear()+"In Ordnung, warte auf mich. Ich hoffe, dein Angebot lohnt sich. Und denk nicht einmal daran, mir einen Streich zu spielen!"),RandPhraseSimple("Ich nehme Ihre Einladung gerne an, Kapitän.","Du hast meine Neugier geweckt. Natürlich komme ich."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Oh, dir ist seekrank, nicht wahr? Lauf und versteck dich unter dem Rock deiner Mutter!","Zu ängstlich?! Verschwinde!"),RandPhraseSimple("Geht nicht. Wenn dir Gold egal ist, ist es deine Entscheidung.","Es ist auf diese Weise und nicht anders. Wenn du es nicht willst - gut, es gibt viele andere."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! Du bist mutig, nicht wahr? Also gut, ich komme!","Ich sehe, du kannst zu deinen Kanonen stehen, Kapitän. Also gut, warte auf mich."),RandPhraseSimple("Gut, ich stimme zu.","Du redest viel was? Gut ich bin bereit, Geschäfte auf deinem Schiff zu besprechen."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! Du dachtest, du könntest mich auf dein Schiff locken und mich dort töten? Das wird nicht funktionieren!","Deine Worte sind keinen Pfennig wert! Ich werde keine Geschäfte mit dir machen!"),"Zweifelhaftes Angebot. Ich muss ablehnen.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Rum für mich! Und du verschwindest aus meinen Augen!","Haben wir nicht schon alles besprochen?"),RandPhraseSimple("Geh deinen eigenen Weg. Ich habe Dinge zu erledigen.","Ich glaube nicht, dass wir etwas zu besprechen haben."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Ich habe dir gesagt, dass ich auf meinem Schiff auf dich warten würde!";
		link.l1 = "Oh... sicher...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Oh, nein, das wird nicht funktionieren... Sind das nicht zu viele Schiffe für dich, "+GetSexPhrase("Kamerad","Fräulein")+"?","Ha! In so einer großen Gesellschaft kann man nichts geheim halten. Verschwinde.");
			link.l1 = RandPhraseSimple("Wie du willst!","In Ordnung. Nicht dass es mir etwas ausmachen würde.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Großartig. Jetzt bin ich sicher, dass keine falschen Ohren in der Nähe sind, und meine Matrosen sind bereits informiert. Also mein Angebot ist, etwas herrenloses Zeug zu erwerben.";
//			link.l1 = "Und was ist daran so schwer? Warum würdest du mich dafür überhaupt brauchen?";
			Dialog.Text = RandPhraseSimple("Willkommen an Bord, Kapitän!","Großartig. Jetzt bin ich sicher, dass keine falschen Ohren in der Nähe sind, und meine Matrosen sind bereits informiert. Also mein Angebot ist, etwas herrenloses Zeug zu erwerben.")+" Also mein Angebot ist, einige herrenlose Sachen zu erwerben.";
			link.l1 = RandPhraseSimple("Und was ist daran so schwer? Warum würdest du mich dafür überhaupt brauchen?","Eigentumslos?! Du musst wohl einen Scherz machen!");
		}
		else
		{
			Dialog.Text = "Jetzt bin ich sicher, dass keine falschen Ohren in der Nähe sind - heraus damit!";
			link.l1 = "Also mein Angebot ist, etwas herrenloses Zeug zu erwerben.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Nun, es gibt Leute, die es als ihr Eigenes betrachten und sie müssen vom Gegenteil überzeugt werden.","Natürlich muss jemand getötet werden - aber das wird doch sicherlich kein Problem sein?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Zur Sache!","Das riecht nach einem Massaker! Und wo sind sie?"),RandPhraseSimple("Ich würde gerne mehr Details über Ihr Angebot erfahren.","Was genau bieten Sie mir an?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Du ziehst mir die Wolle über die Augen. Ich werde daran nicht teilnehmen!","Das scheint einfach zu sein, aber ich vertraue dir nicht! Du willst, dass ich für dich die Kastanien aus dem Feuer hole? Nun, ich bin dagegen!"),RandPhraseSimple("Klingt vielversprechend, aber ich werde passen.","Nein, ich stehle nicht, ich mag es, wenn sie mir stattdessen Geschenke geben."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "Und was ist daran so schwer? Warum braucht ihr mich dafür überhaupt?";
			link.l1 = "Nun, es gibt Leute, die es als ihr Eigenes betrachten und sie müssen vom Gegenteil überzeugt werden.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " to resupply.";
		}
		else
		{
			sTmp += ", wurde vom Sturm erwischt, nicht weit von " + sLoc + " und ist gesunken. Es gelang ihnen jedoch, einen Teil der Ladung zu sichern in der Bucht von " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + 
				" Jetzt warten sie auf die Ankunft ihrer Staffel.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Zögere nicht, spuck es aus!","Ich hatte recht mit dir, was weißt du noch?"),RandPhraseSimple("Das ist sehr interessant, bitte fahren Sie fort!","Ich bin "+GetSexPhrase("ganz","ganz")+" Ohr!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Das klingt nach einer verlockenden Angelegenheit, aber ich lehne trotzdem ab. Ich brauche keinen Streit mit "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Eine Karawane? Herrenlos?! Es sollte tausend Soldaten geben, die sie bewachen! Nein, das geht nicht. Ich verschwinde."),RandPhraseSimple("Nein, ich bin nicht im Krieg mit "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", also bin ich nicht interessiert.","Meine Antwort ist nein! Ich werde meine Beziehungen nicht ruinieren mit "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Das riecht nach einem Massaker! Was ist mit den Details?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Wir haben nur "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+", um sie abzufangen.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" Tage wird die Karawan zu weit weg sein, und wir werden es nicht einholen können.","Wir haben genau "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" Tage, um sie alle zu töten und die Beute zu holen!"),RandPhraseSimple("Wir haben nur "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" Tage für die gesamte Operation zu unserer Verfügung.","Wir sollten uns beeilen, "+PChar.Name+". Wir haben nur "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" Tage."));
			link.l1 = RandPhraseSimple("Wir werden es rechtzeitig schaffen! Lassen Sie uns heute in See stechen.","Lassen wir keine Zeit verlieren, dann. Befehl, heute Segel zu setzen.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "Das ist sehr interessant, bitte fahren Sie fort.";
			link.l1 = "Wir haben nur "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+", Tage um sie abzufangen.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Lass uns keine Zeit verschwenden! Los geht's!";
		link.l1 = "Legen wir los!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"Du hast mich enttäuscht, Kapitän. Dachtest du, ich lade dich ein "+RandPhraseSimple("zur Sonntagsmesse?!!","zu einen Spiel mit Kinder!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Das ist deine Angelegenheit. Und es liegt an mir zu entscheiden.","Ich werde nicht für ein paar Pesos am Strick hängen."),RandPhraseSimple("Meine Entscheidung ist endgültig, Kapitän.","Wir haben nichts mehr zu besprechen."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Oh, komm schon! Alles wird reibungslos verlaufen, und niemand wird etwas wissen. Wir werden alle umbringen."),RandPhraseSimple("Wohin gehen Sie, Kapitän? Zu den Behörden, vielleicht?","Es ist ziemlich unklug, in eine Tigerhöhle zu gehen und zu denken, dass man leicht wieder herauskommt."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Geh und küss den Seeteufel! Ich bin Kapitän "+GetFullName(PChar)+" und du bist mir egal! Ich gehe!","Ich schwöre beim Teufel, du bringst mich wirklich zur Weißglut!"),RandPhraseSimple("Ihr Vorschlag ist für mich nicht von Interesse und es gibt nichts mehr für uns zu besprechen. Lebewohl.","Ich denke, es gibt nichts mehr zwischen uns zu besprechen. Entschuldigung, ich bin beschäftigt und muss gehen."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Ergreift "+GetSexPhrase("ihn","sie")+"! Bindet "+GetSexPhrase("ihn","sie")+" an der Kanone! Mal sehen, welche Farbe "+GetSexPhrase("seine","ihre")+" Gedärme haben!!!","Hey! Johnny! Henderson! Ergreif "+GetSexPhrase("diesen Schurken","dieses Fräulein")+"! Lass nicht "+GetSexPhrase("ihn","sie")+" zum Rettungsboot kommen!!!"),RandPhraseSimple("Schade, Kapitän! Ich hoffe, dass Ihnen unser Laderaum gefällt. Und dann entscheiden wir, was wir mit Ihnen machen.","Die weißen Sklaven leben nicht lange, Kapitän, also treffe deine Wahl: Entweder schießt Hends dir in den Kopf, oder du verbringst den Rest deines Lebens in einem Steinbruch."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ich werde dich deine verdammten Eingeweide essen lassen, "+GetFullName(NPChar)+"!!!","Aus dem Weg! Ihr Schurken! Ich töte euch, wo ihr steht!"),RandPhraseSimple("Dein Angebot ist unannehmbar... und äußerst unklug!!!","Du bist nicht so gastfreundlich, wie ich sehe... Platz da!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "Also, "+GetFullName(PChar)+", Ich sehe, dass ich einen Fehler gemacht habe, mich mit dir einzulassen. Jetzt gibt es keine Beute für uns. Auf Wiedersehen!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Verdammt! Wir sind spät dran - und alles wegen dieser faulen Tölpel! Jetzt gibt es keine Beute, die wir mit dir teilen könnten, "+GetFullName(PChar)+". Hisst die Stagsegel! Wir verschwinden hier! ","Also, "+GetFullName(PChar)+", Ich sehe, dass ich einen Fehler gemacht habe, indem ich mich mit dir eingemischt habe. Jetzt gibt es keine Beute für uns. Lebewohl!"),RandPhraseSimple("Sie sind verschwunden - und alles wegen Ihrer Verspätung! Jetzt gehen wir verschiedene Wege, "+GetFullName(PChar)+".","Es gibt keine Möglichkeit, dass wir den Karawanen jetzt einholen können. Ich habe einen Fehler gemacht, indem ich mich mit dir eingelassen habe. Auf Wiedersehen!"))link.l1 = PCharRepPhrase(RandPhraseSimple("Zum Teufel mit diesem Karawan! Perlenfischer sind sogar besser, und es gibt kein Risiko!","Das Glück ist mit uns und morgen ist ein neuer Tag! Es gibt genug bemitleidenswerte Kaufleute auf den Meeren, die nur darauf warten, dass wir ihr Geld nehmen!"),RandPhraseSimple("Es ist wirklich schade, dass eine so brillante Operation zu einem totalen Misserfolg geworden ist! Lebewohl!","Der Mensch denkt und Gott lenkt... Lebewohl!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Oh, warum zum Teufel habe ich mich mit dir eingelassen. Du hast alles ruiniert. Also, jetzt musst du mir eine Strafe zahlen von "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Blutrünstig"+GetSexPhrase("er Halunke","es Miststück")+"! Alles ging direkt zum Seeteufel hinunter!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" Pesos auf den Nagel, verschwinde aus meinen Augen!","Haben Sie sich als Admiral Nelson vorgestellt? Sie haben die gesamte Beute versenkt, "+GetSexPhrase("Trottel","dumme Frau")+"! Gib mir jetzt "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" Pesos und verschwinde!"),RandPhraseSimple("Haben Sie beschlossen, hier Krieg zu führen! Das ist völlig inakzeptabel! Aber, ich nehme an, wir können es vergessen, wenn Sie uns "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" Pesos bezahlen.","Deine Methoden sind völlig inakzeptabel! Du hast die ganze Angelegenheit ruiniert! Zahle uns sofort unseren Anteil in Höhe von "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" Pesos und geh, wohin du willst!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Wenn ich nicht wäre, würdest du jetzt schon Krebse füttern, du gieriger Bastard!","Oh ja, ich hätte ihr Flaggschiff dich entern lassen sollen - dann würdest du jetzt nicht die Luft vergiften, während du am Hof schwingst!"),RandPhraseSimple("Deine Forderungen sind unangebracht und deine Anspielungen sind beleidigend!","Wir haben uns nicht auf die Strafe geeinigt, also zahle ich dir nichts!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Ich kann dir jetzt keinen Kampf liefern, und das weißt du! Würge an deinen Pesos!"," Pesos?!! Nun, Lady Luck lächelt mir heute sicherlich nicht zu. Ich stimme zu."),RandPhraseSimple("Deine Forderungen sind unerhört, aber ich denke, ich habe keine Wahl.","Deine Gelüste sind übermäßig, aber ich muss zustimmen!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Oh, warum zum Teufel habe ich mich mit dir eingelassen. Du hast alles ruiniert.";
			link.l1 = "Ach, komm schon! Du hast doch selbst gesehen, dass es keinen anderen Weg gab.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Also, unsere Beute macht "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Lass uns teilen.";
			Dialog.Text = PCharRepPhrase("Das war eine heiße Angelegenheit! Also, unsere Beute beläuft sich auf "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Ausgezeichnete Arbeit, Kapitän! Unsere Beute macht sich aus "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" Mein Anteil ist "," Der Anteil an meinem Schiff - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" Dein Anteil beträgt ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Alles ist korrekt! Die Boote werden bereits beladen!","Ja, alles ist korrekt. Ein Geschäft ist ein Geschäft."),RandPhraseSimple("Deine Berechnungen sind korrekt. Ich stimme zu.","Wenn es ums Teilen geht, bist du untadelig."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Du wagst es, deinen Anteil zu fordern? Du solltest sofort am Hof aufgehängt werden!","Dein Anteil? Hier ist jeder für sich selbst. Wenn nichts für dich übrig war, ist es dein Problem!"),RandPhraseSimple("Ich glaube nicht, dass du irgendeinen Anteil erwarten kannst.","Meine Antwort ist Nein! Ich teile nicht mit Schurken wie euch!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Nun, gut dann, ich werde nicht streiten! Auf Wiedersehen!","Lassen wir kein Blut vergießen und die Dinge noch schlimmer machen! Das nächste Mal haben wir mehr Glück!"),RandPhraseSimple("Nun, Lebewohl, Kapitän, ich bin nicht in der Position, Forderungen zu stellen...","Die Verluste und Schäden an meinem Schiff erlauben mir nicht, auf einer gerechten Entscheidung zu bestehen. Ich überlasse es Ihrem Gewissen, Kapitän!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Günstigen Wind dir!","Sieben Fuß unter dem Kiel!"),RandPhraseSimple("Auf Wiedersehen! Ich hoffe, die frische Seeluft wird Ihnen gut tun!","Ich hoffe, dass unsere Missgeschicke Sie nicht noch unerträglicher machen, Kapitän! Lebewohl!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Hast du es nicht kapiert! Du könntest dein Leben stattdessen kaufen! Schnappt den Bastard!","Oder denkst du, wir spielen hier Spiele mit dir? Nun, sobald wir dich kielholen, solltest du gefügiger werden!"),RandPhraseSimple("Wir werden Ihr Leben verkürzen müssen, Kapitän! Wenn Sie nicht auf freundliche Weise gehen wollen, werden Sie bald den heiligen Martin treffen!","Du lässt mir keine Wahl, "+GetFullName(PChar)+"! Ich werde nehmen, was mir gehört, ob es dir gefällt oder nicht!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Ich schwöre beim Teufel, du wirst dafür bezahlen!!!","Yo-ho! Dann geh und hol mich, Kapitän "+GetFullName(PChar)+"! "),RandPhraseSimple("Der Schnitt wird lang und tief sein!","Möchtest du schnell sterben oder ein wenig leiden?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Ich will nichts mehr mit dir zu tun haben!";
		link.l1 = "Überhaupt kein Problem.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Schön, Geschäfte mit dir zu machen. Viel Glück.";
		link.l1 = "Und das Gleiche für dich.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("Das war ein echtes Massaker! Schade, dass keine Weiber dabei waren! Die Beute macht es jedoch wert  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Nicht schlecht, Kapitän! Die Beute macht es wert "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" Mein Anteil ist ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" Dein Anteil ist ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Vollkommen gerecht, verdammt noch mal!","Alles ist perfekt in Ordnung, verdammt noch mal!"),RandPhraseSimple("Deine Berechnungen sind korrekt. Ich stimme zu.","Wenn es ums Teilen geht, bist du tadellos."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
