// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Mein Sohn","Meine Tochter")+", leider kann ich dir keinen Unterschlupf geben. Lauf!","Die Stadtwache durchkämmt die Stadt auf der Suche nach dir, "+GetSexPhrase("mein Sohn","meine Tochter")+". Die Türen meiner Kirche stehen immer offen für die Leidenden, aber ich kann dir kein Obdach geben...",""+GetSexPhrase("Mein Sohn","Meine Tochter")+", du musst rennen! Zögere nicht, ich flehe dich an!"),LinkRandPhrase("Was machst du in der Kirche, verlorene Seele? Ich verlange, dass du sofort gehst, bevor die Soldaten dich hier finden und ein Massaker anrichten!","Verlasse diesen Tempel sofort, du Spötter! Ich werde niemals einen Schurken wie dich schützen!","Verlasse den Tempel unseres Herrn auf der Stelle! Wir brauchen hier keine Mörder!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Ach, komm schon, Pater...","Ich brauche sowieso nicht deine Hilfe..."),LinkRandPhrase("Steh mir einfach nicht im Weg, Vater...","Ich gehe schon, mach dir keine Sorgen...","Padre, hör auf zu toben - Ich habe wirklich keine Zeit dafür"));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...sie sollen in der flammenden Hölle für immer brennen! Niemals sollen sie sehen...";
					link.l1 = RandPhraseSimple("Hüstel! Störe ich, Padre?","Das ist die Rede!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+", Ich freue mich, dich wieder zu sehen!";
					link.l1 = "Und es freut mich, Sie in guter Gesundheit zu sehen, Padre "+NPChar.name+"...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+"! Ich freue mich, Sie wieder gesund und munter zu sehen. Der Herr muss uns doch in unserer Angelegenheit geholfen haben, nicht wahr?";
					link.l1 = "Ja, "+RandPhraseSimple("Vater","heiliger Vater")+", obwohl nicht immer der Rückenwind in meinen Segeln blies, obwohl ich etwas mehr Zeit, Kräfte und Geld ausgegeben habe - Ihre Mission ist erledigt.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Willkommen in unserer heiligen Behausung, "+GetSexPhrase("mein Sohn","meine Tochter")+".";
				link.l1 = "Hallo, heiliger Vater.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Grüße, Ellen, mein Kind.";
					link.l1 = "Und zu dir, Vater.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Du bist nicht mein Vater und sprich mich nie wieder so an.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Verlass den Tempel des Herrn, Blasphemiker! Wir haben nichts zu besprechen!";
				Link.l1 = "Ich wollte nicht mal.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Oh, du Blasphemiker! Geh weg! Wage es nicht, den Tempel unseres Herrn mit deiner Anwesenheit zu entweihen!";
			link.l1 = "Ich wollte hier eigentlich gar nicht bleiben.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Es freut mich, dass du trotz deiner... Verfolgungen mit Jan, unseren Herrn und sein Haus nicht vergisst. Wie kann ich dir helfen?";
			}
			else
			{
				dialog.text = "Möge der Herr Sie und Ihre Angelegenheiten segnen... Sind Sie aus einem bestimmten Grund zu mir gekommen?";
			}
    		link.l1 = RandPhraseSimple("Ich möchte eine Spende machen.","Ich möchte für einen guten Zweck spenden.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Ich glaube, es ist Zeit für eine Beichte.","Ich möchte beichten, "+RandPhraseSimple("Vater.","heiliger Vater."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("Ich habe Geschäfte mit dir, "+RandPhraseSimple("Vater.","heiliger Vater."),"Ich bin geschäftlich hier, "+RandPhraseSimple("Vater.","heiliger Vater."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Ich möchte eine Gebetszeremonie für den Seelenfrieden einer Dame in Auftrag geben.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Vater, ich brauche Hilfe. Mir geht es wirklich schlecht. Ein böser heidnischer Fluch hat mich getroffen. Bitte, hilf mir, ich flehe dich an!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Vater, ich brauche Hilfe. Ich bin wirklich krank. Ein übler heidnischer Fluch hat mich getroffen. Bitte, hilf mir, ich flehe dich an!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Vater, ich brauche Hilfe. Mir geht es wirklich schlecht. Ein widerwärtiger heidnischer Fluch ist über mich gekommen. Mir wurde gesagt, dass du derjenige bist, der mir helfen kann. Ich flehe dich an...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Vater, ich brauche Hilfe. Mir geht es wirklich schlecht. Ein böser heidnischer Fluch hat mich getroffen. Ich wurde von... Jessica Rose zu Ihnen geschickt. Sie hat mir gesagt, dass Sie mir helfen könnten.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "Über die Kerzen...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Ich bin bereit zu beten, Vater.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Schreckliche Dinge geschehen, heiliger Vater.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Entschuldigen Sie, aber ich muss gehen.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Mach dir keine Sorgen, mein Sohn. Der Herr wird dein Leiden sehen und Er wird eine helfende Hand ausstrecken. Trage immer ein Kreuz bei dir, um deinen Glauben zu stärken.";
			Link.l1 = "Danke dir, heiliger Vater.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "Ich werde Euren Willen demütig für 1000 Pesos ausführen.";
			Link.l1 = "Hier, Vater - bitte nehmen Sie diese Münzen.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Danke dir, mein Sohn. Wie heißt die Señora, für deren Seele ich beten soll?";
			Link.l1 = "Ihr Name ist Chica Gonzales und sie hat diese Welt vor vielen Jahren verlassen.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "Das ist seltsam... Ist etwas mit Alvarez passiert, und hat er dich deswegen gefragt?";
			Link.l1 = "Und wer ist dieser Alvarez und was ist so seltsam an meiner Anfrage?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Nun, wie! Jeden Monat bestellt Alvarez, der Wächter unseres Leuchtturms seit zwei Jahrzehnten, einen Gottesdienst für den Frieden der Seele dieser Dame. Niemand außer ihm hat sich bisher um Lady Gonzales gekümmert. Und du kommst hierher. Also dachte ich. Allerdings geht es mich nichts an. Sicherlich werde ich gerne bescheiden Ihre Wünsche erfüllen, um der verirrten Seele zu helfen, Ruhe und den Weg ins Paradies zu finden.";
			Link.l1 = "Danke dir, heiliger Vater.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Gibt es noch eine andere Seele, für die Sie ein Requiem bestellen möchten?";
			Link.l1 = "Mmm... Nein, ich glaube nicht. Muss ich für jemand anderen bestellen?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Nun, vielleicht für die Hunderte von unschuldigen Menschen, die durch deine Hand oder die Klingen deiner gottlosen Gefährten fielen, als du diese unglückliche Stadt geplündert hast?.. Allerdings ist es unwahrscheinlich, dass ein bescheidener Priester hofft, das Gewissen eines Mannes zu erreichen, der einfache friedliche Bürger ohne Reue getötet hat...";
			Link.l1 = "Vater, du verstehst nicht... Das gehört alles der Vergangenheit an. Hier und jetzt habe ich nicht vor, jemandem zu schaden.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Kann ich deinem Wort trauen...? Aber in jedem Fall ist dies heiliger Boden, der nicht mit Blut bedeckt sein sollte. Also rufe ich die Wachen nicht. Gehe in Frieden. Vielleicht hast du vor Gottes Urteil Zeit, zumindest einen Teil deiner Sünden zu sühnen.";
			Link.l1 = "Vielleicht. Gottes Wille geschehe.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica? Ich erinnere mich an sie. Arme Sünderin. Aber ist sie nicht gestorben?";
			link.l1 = "Sie ist gestorben, heiliger Vater. Nun ist sie tot, möge der Herr ihre Seele ruhen lassen. Aber sie hat mir versichert, dass Sie mir helfen könnten.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Wer hat diese Zauber auf dich gelegt, mein Sohn? Sag es mir ehrlich.";
			link.l1 = "Sie... sie tat es. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Gott bewahre uns! Das dachte ich mir. Sich in heidnische Riten zu vertiefen, kann selbst die stärksten Seelen in den Abgrund der Dunkelheit stürzen... Aber... ist sie wirklich gestorben? Oder... nicht ganz?";
			link.l1 = "Sie sind äußerst scharfsinnig, Vater. Jetzt ist sie völlig tot.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Dieser arme Sünder hat bei mir schon so einige Male gebeichtet. Der Hass hat sie vollständig von innen zerstört. Ich wusste, was sie vorhatte. Ich versuchte sie zu stoppen, versuchte sie auf den rechten Weg zu führen, aber alle meine Bemühungen waren vergebens. Ich warnte sie vor der schrecklichen Gefahr und den schwerwiegenden Folgen der gottlosen Taten...";
			link.l1 = "Ja, heiliger Vater. Was ich gesehen habe, war in der Tat schrecklich. Aber... wie kann ich geheilt werden?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Durch die Kraft des Gebets, mein Sohn. Durch die Kraft des heiligen reinigenden Gebets in unserem Tempel. Du wirst sehr lange beten müssen, und nicht nur für dich selbst. Du musst auch für sie beten.";
			link.l1 = "Für Jessica?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Ja. Für dich und ihre Seele. Komm hierher um zehn Uhr nachts, damit dich niemand stört. Du musst die ganze Nacht durchbeten. Bring zwanzig dicke Wachskerzen mit, zünde sie an und bete, bis sie alle ausgebrannt sind.";
			link.l1 = "Und dann werde ich geheilt sein?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Alles liegt in den Händen des Herrn. Ich werde dir beibringen, wie man betet und lasse die Heilige Schrift für dich. Die Kraft des heiligen Gebets wird üble Zauber, die dich getroffen haben, zerstören und auch die Seele der armen Jessica reinigen.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Ich habe zwanzig Wachskerzen bei mir. Ich bin bereit, im Tempel zu bleiben und mit dem Beten zu beginnen.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Ich habe noch keine zwanzig Kerzen bei mir. Ich werde sie besorgen!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "In Ordnung, mein Sohn. Ich werde auf dich warten. Verschwende keine Zeit!";
			link.l1 = "Ich werde bald hier sein...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Hast du zwanzig Kerzen gebracht, mein Sohn?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Ja, Vater. Ich habe zwanzig Wachskerzen bei mir. Ich bin bereit, im Tempel zu bleiben und zu beten.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Noch nicht - aber ich werde sie auf jeden Fall bekommen.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Nun, mein Sohn. Gib sie mir und komm morgen nach zehn Uhr abends zurück. Ich werde dir die notwendigen Gebete beibringen und dich für die Nacht in der Kirche lassen.";
			link.l1 = "Danke, heiliger Vater. Bis morgen!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Danke, Vater. Ich habe es verstanden.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Ich komme morgens zurück. Ich werde auch für dich beten...";
			link.l1 = "Danke dir, heiliger Vater.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Welche heidnischen Zauber haben dich getroffen, mein Sohn?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Ich habe von denen gehört... Sie wurden von unheiligen Hexen dieser rotäugigen Heiden in unsere Welt gebracht. Ich würde Ihnen raten, den Oberpriester der Kirche von Bridgetown aufzusuchen - er hat mehrere Jahre damit verbracht, den schädlichen Einfluss von Indianerflüchen auf die Körper und Seelen der Christen zu studieren.";
				link.l1 = "Und er könnte mir helfen?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Ich habe von denen gehört... Sie wurden in unsere Welt gebracht von unheiligen Hexen dieser rotäutigen Heiden. Leider ist der einzige Rat, den ich dir geben kann, mehr Zeit mit Beten zu verbringen, mein Sohn, und deine Hoffnungen auf die Barmherzigkeit unseres Herrn zu setzen.";
				link.l1 = "Aber kann man wirklich nichts dagegen tun, Vater?! Bleibe ich so... bis ans Ende meiner Tage?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Verzweifle nicht, mein Sohn. Der Herr wird dich hören und Er wird dir Hilfe senden. Aber ich würde dir empfehlen, dich auch in anderen heiligen Stätten umzuhören - vielleicht gibt es Priester, die wissen, wie man heidnische Flüche entfernt.";
			link.l1 = "Danke, Vater! Ich werde geheilt werden - auch wenn ich jede Kirche auf dem Archipel besuchen muss!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Geh, mein Sohn, und möge der Herr über dich wachen.";
			link.l1 = "Auf Wiedersehen, Padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Nur der Herr kann dir helfen - und du selbst, mein Sohn. Ein Priester kann dir nur beibringen, was zu tun ist und wie. Komm und besuche ihn.";
			link.l1 = "Danke, Pater! Du hast mich gerettet! Ich werde sofort nach Barbados segeln!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Geh jetzt, und möge der Herr über dich wachen.";
			link.l1 = "Auf Wiedersehen, Vater.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Welche heidnischen Flüche haben dich getroffen, mein Sohn? Lass mich raten: Du kannst nicht rennen, ein Säbel ist dir zu schwer und deine Bewegungen sind langsam und träge?";
			link.l1 = "Wie wussten Sie das, Vater?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Es war nicht schwer zu sehen, wenn man auf deinen Schritt schaute, als du dich mir nähertest, mein Sohn. Möge der Herr unseren sündigen Seelen gnädig sein... Sag mir, mein Sohn, und sei ehrlich - wer hat diese Verzauberungen auf dich gelegt?";
			link.l1 = "Brauchst du einen Namen, Vater?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Wenn du den Namen kennst, dann sprich ihn aus.";
			link.l1 = "Ihr Name war... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Gott rette uns! Sich in heidnische Riten zu vertiefen, kann selbst die stärksten Seelen in den Abgrund der Dunkelheit stürzen... Was ist mit ihr passiert, mit dieser armen Seele?";
			link.l1 = "Sie ist gestorben, Vater.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Aber... ist sie wirklich gestorben? Oder... nicht ganz?";
			link.l1 = "Sie sind äußerst scharfsinnig, heiliger Vater. Nun ist sie völlig tot.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...und des Herrn Barmherzigkeit! Möge die universelle Dunkelheit ihre Seelen für ihre Sünden verschlingen...";
			link.l1 = LinkRandPhrase("Heiliger Vater","Vater","Vater")+", bist du nicht ein bisschen zu eifrig? Weißt du, du könntest einen Schlaganfall bekommen...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Nun... Scheiße. Lebewohl dann.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+", schreckliche Blasphemie, das abscheulichste aller Verbrechen hat gerade stattgefunden! Aus der Kirche stehlen!!! Es ist, als würde man seine Hand in die Tasche des Herrn selbst stecken!";
			link.l1 = "Ach, ich verstehe... Wie ist es passiert?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("Es ist sehr traurig und alles, aber ich muss wirklich gehen...","Mein Beileid, Padre, aber ich muss gehen...","Du musst dich zu sehr auf den Allmächtigen verlassen haben. Du hättest sicherere Schlösser verwenden sollen. Nun, ich muss gehen...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Unter dem Schleier der Nacht haben einige Schurken alles ergriffen, was die Gemeinde gesammelt hat! Diese Gotteslästerer haben sogar den Opferkelch genommen!";
			link.l1 = "O tempora, o mores... Aber, ich hoffe, du hast etwas auf einer heißen Spur unternommen?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Aber natürlich! Ich habe diese blasphemischen Räuber exkommuniziert und jetzt spreche ich ein Anathema gegen sie aus!";
			link.l1 = "Ich habe keinen Zweifel, dass dies eine äußerst wirksame Maßnahme ist. Aber ich meinte etwas praktischeres. Zum Beispiel eine Verfolgung zu organisieren.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ach, was kann ein einfacher Priester, gebunden durch das Gelübde der Nicht-Widerstand gegen das Böse, tun? Diese Schurken sind sicherlich schon weit von hier, trinken in Tavernen, die durch Raub angesammelt wurden, oder geben sich der Ausschweifung und Verschwendung in der Gesellschaft von gefallenen Frauen hin! Ich hoffe wirklich, sie werden dort ihr Ende finden!";
			link.l1 = RandPhraseSimple("Ich bin sicher, dass ein solches Ende viel attraktiver ist, als gehängt zu werden. Aber ich werde Sie nicht länger ablenken. Alles Gute.","Nun, früher oder später werden wir alle zu den Vorfahren gehen, aber ich würde ihnen kein schnelleres Ende absprechen. Ich muss jedoch gehen. Viel Glück.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Heiliger Vater","Vater","Vater")+", aber ich bin nicht durch Gelübde gebunden und bereitwillig werde ich dem Herrn helfen, die Zeit der Vergeltung herbeizuführen.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Ich werde für dich beten, mein Sohn! Geh jetzt und gib diesen Betrügern, was sie verdienen!";
			link.l1 = "Hab keine Zweifel, Padre";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Nun, vielleicht sendet der allgütige Schöpfer seinen törichten Kindern Pest und Hunger, um sie für ihre Sünden zu bestrafen...";
				link.l1 = "Aus Stolz, zum Beispiel, oder Gier... Warum sind Sie blass geworden, Padre?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jesus, mein Herr, erbarme dich deines sündigen Dieners... Hast du... hast du die Räuber gefunden? Hast du sie getötet?";
					link.l1 = "Lass uns die zehn Gebote in Erinnerung rufen, die jedem guten Christen von der Wiege an bekannt sind: Du sollst nicht töten, du sollst nicht stehlen, du sollst kein falsches Zeugnis ablegen. Kann eine gottesfürchtige Person sie verletzen - und erst recht ein geistlicher Priester...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Es liegt eine solch dicke Luft hier... Also, hast du die Räuber gefunden? Hast du sie getötet?";
					link.l1 = "Lass uns die zehn Gebote in Erinnerung rufen, die jedem guten Christen von der Wiege an bekannt sind: Du sollst nicht töten, du sollst nicht stehlen, du sollst kein falsches Zeugnis ablegen. Kann ein gottesfürchtiger Mensch sie verletzen - und erst recht ein geistlicher Priester?!..";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+"... Gott vergib mir... solches Geld, solche Versuchung... der Mensch ist schwach, wahrhaftig schwach! Ich konnte es nicht ertragen... ich war außer mir... ich betete Tag und Nacht, tat Buße, ich fastete rigoros, ich geißelte mein Fleisch... Unwürdig, ich flehte den Himmel nur an, diese armen Männer zu verschonen, die ich durch meine eigene Gier versucht hatte...";
			link.l1 = LinkRandPhrase("Vater","Vater","Vater")+", beruhige dich. Sie haben nichts darüber gesagt... und das werden sie sicher nicht tun. Übrigens, sie haben mir freiwillig den Kommunionkelch zurückgegeben, den ich dir zurückgebracht habe.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Mein Herr, ich danke Ihnen! Mein Gott, Du hast die Gebete Deines unwürdigen Dieners gehört, eines gestolperten Sünders, der in Schmutz und Lastern feststeckt...";
			link.l1 = "Jeder hätte stolpern können... Aber da deine Reue aufrichtig zu sein scheint, würde ich sagen: du bist ein anständiger Mann und ein guter Priester. Wenn du vor Gericht stehst, wird nichts Gutes dabei herauskommen. Und es liegt an dir zu entscheiden, ob du im Dienst des Herrn bleiben willst oder nicht - nur Er kann dir das sagen und dich leiten...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+"... Mit Tränen der Reue und Dankbarkeit nehme ich diesen Kelch von dir an. Die Reinheit und Noblesse deiner Seele haben mich wahrhaftig erschüttert. Ich segne dich von ganzem Herzen und bitte dich demütig, diese kleine Belohnung anzunehmen. "+FindRussianMoneyString(iMoneyToCharacter)+"... Ich hoffe, es reicht aus, um deine Ausgaben zu decken?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "Das ist unnötig, heiliger Vater "+NPChar.name+". Ich bin nicht gerade die ärmste Person, also solltest du dieses Geld besser für das Wohl deiner Gemeinde verwenden.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Danke, "+LinkRandPhrase("Vater","Vater","heiliger Vater")+", das ist mehr als genug.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+"... Mit den Tränen der Reue und Dankbarkeit werde ich diesen Kelch von dir als Zeichen der Gnade und Vergebung des Herrn annehmen. Die Reinheit und Adel deiner Seele haben mich wahrlich erschüttert. Ich segne dich von ganzem Herzen!";
				link.l1 = "Danke für den Segen, "+LinkRandPhrase("Vater.","Vater.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "Der Segen ist sicherlich notwendig, aber es wäre nicht verkehrt, ihn mit etwas Materiellem zu unterstützen, wenn man bedenkt, welche erheblichen Kosten ich hatte...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, Kind, es tut mir wirklich leid... Ich hoffe, dieser kleine Beitrag von "+FindRussianMoneyString(iMoneyToCharacter)+" wird genug sein, um deine Ausgaben zu decken?";
			link.l1 = "Ja, "+LinkRandPhrase("Vater.","Vater.")+", das reicht, danke.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Ich verstehe Ihre Anspielungen nicht ganz, "+GetSexPhrase("mein Sohn","meine Tochter")+", wovon redest du?!";
			link.l1 = "Ich spreche von schrecklichen Dingen, die Gier einem Mann antun kann und die ich von Lumpen bekommen habe, die angeblich deine Kirche ausgeraubt haben... Wolltest du etwas sagen?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Ich würde dir sagen, Kind, dass du mit einem Geistlichen sprichst und du solltest ein bisschen mehr Respekt zeigen, oder du könntest es bereuen. Was diesen Kelch betrifft - Ich habe ihn noch nie gesehen, aber wenn du bereit bist, ihn der Pfarrei zu spenden, dann...";
			link.l1 = "Halte deine Pferde, Padre. Du wirst es nicht bekommen, bis du dich erklärst.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Was gibt es da zu erklären?! Jetzt schau mal - du bist ein "+GetSexPhrase("kluger Mann","schlaues Mädchen")+", und sicherlich müssen Sie verstehen, dass alles, was diese Gauner Ihnen vielleicht erzählt haben - dass ich sie angeblich eingestellt hätte - eine offensichtliche Lüge ist! Der Herr wird diese Blasphemiker nicht nur für Sakrileg, sondern auch für falsche Beweise bestrafen!";
				link.l1 = "Lasst den Herrn in Ruhe! Wie könnt ihr wissen, was diese armen Dinger mir erzählt haben - diejenigen, gegen die ihr mich aufgehetzt habt? Vielleicht habe ich sie getötet, bevor sie Zeit hatten, mir etwas Schlechtes über euch zu erzählen?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Nun... Ich sehe, dass du so tief in die Sünde verstrickt bist, dass du das Urteil der Menschen nicht mehr fürchtest. Aber es gibt noch göttliche Gerechtigkeit, und jeder von uns wird früher oder später dafür Verantwortung übernehmen müssen. Nimm deine 'Kirchenutensilien' und denke nach, ob du es wert bist, sie zu berühren, Vater "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Bitte verzeih mir meine Zweifel, Vater, denn ein sterbliches Herz ist schwach und die Seele ist verwirrt. Bitte nimm den Kelch und gib mir deinen Segen.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Mein Sohn... Herr... Sir...","Meine Tochter... Fräulein... Dame...")+" "+PChar.name+"... Ich bin bereit, mich vor dir zu beugen... und unsere Meinungsverschiedenheiten, sozusagen... und deine Ausgaben mit dieser bescheidenen Summe zu kompensieren "+FindRussianMoneyString(iMoneyToCharacter)+"... natürlich, wenn Sie nicht vorhaben, andere in diese Angelegenheit einzubeziehen...";
			// При этом варианте репу плюсуем
			link.l1 = "Ich werde niemanden mit hineinziehen. Nehmen Sie den Kelch! Und denken Sie nicht einmal daran, dass ich das Gold akzeptieren würde, das Sie heimlich aus den Taschen Ihrer Pfarrkinder gekniffen haben!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Ich werde niemanden einbeziehen. Nimm den Kelch! Dieses Gold nehme ich nur, weil ich viel Zeit und Geld in dich investiert habe.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Schlimme Nachrichten, "+LinkRandPhrase("Vater","Vater","Vater")+": die Räuber waren zu hinterlistig und einfallsreich, und so gelang es mir nicht, das Kirchengold zurückzuholen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Schreckliche Nachrichten, "+LinkRandPhrase("Vater","Vater","Vater")+": Ich habe es geschafft, die Räuber einzuholen, aber meine einzige Trophäe war dieser Kelch.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Ich bin sicher, dass Euch die Neuigkeiten gefallen werden - Ich habe die Räuber beinahe bestraft und ihnen das Kirchengeld abgenommen, sowie diesen Kelch.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Vater","Vater","Vater")+", Ich bringe schlechte Nachrichten... Ich musste viel Zeit, Kraft und Ressourcen aufwenden, um die Schurken zu jagen, aber als ich sie fand, stellte ich fest, dass sie die Zeit hatten, alles weg zu trinken und auszugeben, außer diesem Kelch...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+", was könnte mir wohl passiert sein? Es ist dein Weg, der voller Gefahren und Ängste ist, und meine friedliche Zelle, das Reich der Besinnung und des Gebets, ist eine ruhige Insel in einem tobenden Ozean menschlicher Leidenschaften...";
					link.l1 = "Und nichts kann die Ruhe Ihrer glückseligen Einsamkeit stören?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Ich bin sicher, dass diese Nachricht dir Freude bereiten wird - Ich habe die Räuber bestraft und das Geld der Gemeinde zurückgebracht.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Vater","Vater","Vater")+"... Ich muss dich enttäuschen. Ich habe Räuber im gesamten Archipel verfolgt, eine große Anzahl von Gefahren und Hindernissen überwunden, mich fast ruiniert, und schließlich habe ich sie eingeholt, aber ach... sie hatten bereits Zeit, das Kirchengeld zu verschwenden.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+". Ihre Worte stürzten mich in tiefe Trauer - aber nicht in Verzweiflung, denn Verzweiflung ist eine Todsünde! Der Herr hat uns mit einer weiteren Prüfung konfrontiert, um unseren Glauben zu stärken.";
						link.l1 = "Amen, Vater...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+", lüge nicht deinem geistlichen Hirten.";
						link.l1 = "Es tut mir wirklich leid, Vater, aber ich schwöre, dass ich die Wahrheit sage.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+". Ihre Worte stürzten mich in tiefe Trauer - aber nicht in Verzweiflung, denn Verzweiflung ist eine Todsünde! Der Herr stellte uns eine weitere Prüfung, um unseren Glauben zu stärken. Aber Ihre Bemühungen und Ausgaben sollten trotzdem entschädigt werden. Bitte, nehmen Sie diese bescheidene Summe - "+FindRussianMoneyString(iMoneyToCharacter)+" - und folge deinem rechtschaffenen Weg weiter!";
					link.l1 = "Hmm!... Danke, Pater, ich werde dieses Geld für eine tugendhafte Sache verwenden.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Vater","Vater","Vater")+"... Ich kann keine Belohnung für eine Arbeit annehmen, die ich nicht getan habe. Sie sollten dieses Geld besser verwenden, um den Altar zu erneuern.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "In Ordnung, ich glaube dir, "+GetSexPhrase("mein Sohn","meine Tochter")+". Der Herr hat uns mit einer weiteren Prüfung besucht, um unseren Glauben zu stärken.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Abscheulich, dachtest du wirklich, unseren Herrn täuschen zu können?! Fluch auf dich"+GetSexPhrase(", Schurke",", Dirne")+"! Raus mit dir und vergiss nicht, dass dieses Geld dir keinen Nutzen bringen wird!";
				link.l1 = "Wie ist das möglich?! Padre!..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+". Deine Worte stürzten mich in tiefe Trauer - aber nicht in Verzweiflung, denn Verzweiflung ist eine Todsünde! Der Herr stellte uns eine weitere Prüfung, um unseren Glauben zu stärken.";
				link.l1 = "Amen, Vater...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Ja, das ist genau der Kelch, der mit dem Geld gestohlen wurde... Aber... Wenn du ihn hast, warum hast du das Geld nicht zurückgebracht? Es war eine ordentliche Summe, und sicherlich hätten diese Schurken es nicht so schnell ausgeben können... "+GetSexPhrase("Mein Sohn","Meine Tochter")+", erinnere dich daran, dass es keine größere Sünde gibt als deinem geistlichen Hirten zu lügen und in der Gegenwart Gottes im Tempel falsche Beweise vorzulegen!";
				link.l1 = "Heiliger Vater "+NPChar.name+", Ich habe fast mein Leben verloren, um diese Vase zu bekommen, dachte, dich glücklich zu machen. Ich werde nichts darüber sagen, wie viel Geld ich dafür ausgegeben habe!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Verzieh dich und danke dem Allmächtigen, der mir ein sanftes Herz gegeben hat. Es ist der einzige Grund, dass du noch nicht als Dieb und Schurke gebrandmarkt bist!";
			link.l1 = "Wie ist das?! "+LinkRandPhrase("Heiliger Vater","Vater","Vater")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+". Ihre Worte stürzten mich in tiefe Trauer - aber nicht in Verzweiflung, denn Verzweiflung ist eine Todsünde! Der Herr stellte uns vor eine weitere Prüfung, um unseren Glauben zu stärken.";
			link.l1 = "Amen, Vater...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Herr, ich danke Dir! Tatsächlich, du warst Sein Werkzeug, mein Kind! Ich wusste, dass unser Himmlischer Vater dir den Weg zeigen und alle Hilfe bieten würde, die du benötigst. Ich habe ohne Unterbrechung gebetet, und...";
			link.l1 = "Sie wissen, Padre, in Angelegenheiten wie dieser sind Waffen sicherlich nützlicher als Gebete. Aber anscheinend wurden Ihre Gebete tatsächlich gehört.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+", Ich möchte dich ordentlich belohnen, du"+GetSexPhrase(", wie ein wahrer Ritter der Mutterkirche,","")+" tat alles in seiner Macht stehende überca...";
			link.l1 = "Vater, Sie übertreiben wirklich meine bescheidenen Leistungen. Ich werde Sie jetzt unserem Herrn preisen lassen...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Natürlich, "+GetSexPhrase("mein Sohn","meine Tochter")+". Wie viel möchten Sie der Heiligen Kirche spenden?";
			Link.l1 = "Es tut mir leid, heiliger Vater, aber ich habe meine Meinung geändert.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Meine Spende wird eine bescheidene sein - nur 100 Pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 Pesos. Ich denke, das sollte genug sein.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Ich habe Glück mit Geld, also werde ich 5000 Pesos spenden.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Vater, ich möchte eine Spende nicht in meinem Namen machen. Ich tue es auf Anfrage.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... Nun, das ist deine Entscheidung, und du bist frei, deine Meinung zu ändern. Und vergiss nicht, dass dies am Tag des Jüngsten Gerichts berücksichtigt wird.";
			Link.l1 = "So werden es auch viele andere Dinge tun. Lassen wir das Thema wechseln.";
			Link.l1.go = "node_3";
			Link.l2 = "Es tut mir leid, Vater, aber es ist Zeit für mich zu gehen.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "Im Namen der Heiligen Kirche danke ich Ihnen, "+GetSexPhrase("mein Sohn","meine Tochter")+", für dein Geschenk.";
			Link.l1 = "Ich muss mit Ihnen sprechen, Vater.";
			Link.l1.go = "node_3";
			Link.l2 = "Es tut mir leid, Vater, aber es ist Zeit für mich zu gehen.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "Im Namen der Heiligen Kirche danke ich Ihnen.";
            Link.l1 = "Ich muss mit Ihnen sprechen, Vater.";
			Link.l1.go = "node_3";
			Link.l2 = "Es tut mir leid, Vater, aber es ist Zeit für mich zu gehen.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "Im Namen der Heiligen Kirche danke ich Ihnen für Ihr Geschenk.";
            Link.l1 = "Ich muss mit dir sprechen, Vater.";
			Link.l1.go = "node_3";
			Link.l2 = "Es tut mir leid, Vater, aber es ist Zeit für mich zu gehen.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Natürlich, "+GetSexPhrase("mein Sohn","meine Tochter")+", ich höre Ihnen zu.";
			link.l1 = "Ich habe meine Meinung geändert. Vielleicht nächstes Mal.";
			link.l1.go = "exit";
			link.l2 = "Ich bin so voller Sünden, Vater. Ein Tag wird nicht ausreichen, um all meine Vergehen aufzulisten...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Wir sind alle Sünder, mein Kind...";
			link.l1 = "Ja, aber auf meinem Gewissen liegt die Last von Tausenden von Todesfällen schwer. Ich habe Schiffe ausgeraubt und versenkt...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Ich hoffe, es waren keine unter denen, die unter der Flagge von "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Nein, natürlich nicht, Vater.";
			link.l1.go = "ispoved_3";
			link.l2 = "Alle Arten von ihnen, Vater...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Dann wird unser Herr dich von diesen Sünden freisprechen. Denn dies ist ein grausames Zeitalter, und indem du die Feinde deines Herrschers vernichtest, rettest du das Leben seiner treuen Untertanen.";
			link.l1 = "Danke, Vater, das war ein großer Trost... Ich gehe jetzt.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Der Herr wird dir eine solche Sünde nicht vergeben! Betet und bereut, bereut und betet! Es gibt nur einen Weg für dich jetzt - ins Kloster!";
			link.l1 = "Das Kloster muss warten. Nicht in diesem Leben, zumindest. Leb wohl...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Es tut mir leid, "+GetSexPhrase("mein Sohn","meine Tochter")+", aber alle Beichtstühle sind im Moment besetzt. Ich werde in der Lage sein, Ihre Beichte frühestens in einer halben Stunde anzuhören.";
				link.l1 = "Entschuldigung, "+RandPhraseSimple("Vater","Vater")+", das ist eine andere Sache. Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+", von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", gab dir einst unbezahlbare Schätze aus der theologischen Bibliothek. Er bat mich, sie zurückzugeben.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Welches Geschäft hat Sie hierher gebracht, "+GetSexPhrase("mein Sohn","meine Tochter")+"?";
			link.l1 = "Ich möchte Ihnen eine Frage stellen, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Ich wollte über die Arbeit zum Wohl der Kirche von "+NationNameGenitive(sti(NPChar.nation))+".","Wie läuft es in der Gemeinde? Brauchen Sie Hilfe?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Vater","Vater")+", Ich möchte mit Ihnen über finanzielle Angelegenheiten sprechen."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Ich brauche Heilung.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Vater","Heiliger Vater")+", ich bin hier auf Anfrage eines Mannes. Sein Name ist Gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Vater, ich habe Ihnen Papiere von einem Mönch in der Stadt "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Vater, ich komme aus der Kolonie "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+". Die örtliche Kirche benötigt mehr Gebetbücher, und der örtliche Mönch hat vorgeschlagen, diesbezüglich mit Ihnen zu sprechen.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Vater, ich habe die Gebetbücher für Ihre Gemeinde gebracht.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Ich habe es mir anders überlegt, ich habe viel zu tun.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "Das ist großartig. Und doch, in diesen düsteren Zeiten, "+GetSexPhrase("mein Sohn","meine Tochter")+", nicht jeder Besucher des Tempels kann unserer Mutterkirche nützlich sein.";
				link.l1 = LinkRandPhrase("Vater","Vater","Vater")+", ich bin ein wahrer Christ, und meine Absichten, unserer Mutterkirche zu dienen, sind die aufrichtigsten."+GetSexPhrase("Wer wird Sie unterstützen, wenn nicht ihr treuer Ritter, wie ich?","")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "Bisher ist alles ruhig in der Pfarrei, "+GetSexPhrase("mein Sohn","meine Tochter")+". Danke für das Angebot.";
    		link.l2 = "Nun, wenn alles in Ordnung ist, denke ich, werde ich meinen Geschäften nachgehen.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Nun, ich habe eine heikle Mission, die nicht nur reine Absichten erfordert, sondern auch großen Mut und erhebliche Diskretion...";
			link.l1 = LinkRandPhrase("Vater","Vater","Vater")+", Ich werde Ihnen gerne jede Dienstleistung erbringen, auch wenn ich dafür direkt in die Hölle gehen muss! Gott möge mir für meine unheiligen Worte vergeben.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Gut... Aber nochmal, das ist ein sehr heikles Geschäft... Vor einiger Zeit hat der Vater Oberer "+PChar.GenQuest.ChurchQuest_1.ToName+" von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" an "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"hat für mich für eine Weile ein paar theologische Werke und alte Handschriften aus einer Kirchenbibliothek ausgeliehen. Da die Anfrage durch die Beharrlichkeit des Erzbischofs unterstützt wurde, die Verbreitung des lieblichen Lichts des Wissens nicht zu verhindern, konnte ich nicht ablehnen, obwohl ich vermutete, dass die Schwierigkeiten der Seereisen es ihm nicht erlauben würden, die Manuskripte rechtzeitig zurückzugeben... Könnten Sie mir bei der Lösung dieses Problems helfen?";
			link.l1 = "Ich fürchte, "+LinkRandPhrase("Vater","Vater","heiliger Vater")+", Ich kann das nicht für dich tun. Das ist ein sehr heikles Geschäft, und nur ein echter Diplomat würde es schaffen, es zu regeln.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vater","Vater","Vater")+", deine Mission scheint mir nicht allzu kompliziert zu sein. Ich mache mich sofort auf den Weg.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Oh! Ja... Tatsächlich, jetzt erinnere ich mich... Aber, "+GetSexPhrase("mein Sohn","meine Tochter")+", diese Schätze sind eher von spiritueller als materieller Natur! Sie haben meinen Gemeindemitgliedern bereits immens geholfen und könnten dies auch in Zukunft tun!";
				link.l1 = "Aber, "+LinkRandPhrase("Vater","Vater","Vater")+", die Gemeindemitglieder von Vater "+PChar.GenQuest.ChurchQuest_1.PriestName+" brauchen auch Erlösung, und ohne diese Werke wird ihm die Unterstützung der Pfeiler der Theologie fehlen, und seine Predigten werden an Inspiration mangeln.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Oh, ja!.. In der Tat... "+GetSexPhrase("Mein Sohn","Meine Tochter")+", diese Schätze sind eher von spiritueller als materieller Natur! Sie haben meinen Pfarrkindern bereits immens geholfen, also, zu meiner Schande, habe ich 'vergessen', sie ihrem rechtmäßigen Eigentümer zurückzugeben...";
				link.l1 = "Tatsächlich, "+RandPhraseSimple("Vater","Vater","Vater")+", in der Tat. Deshalb Vater "+PChar.GenQuest.ChurchQuest_1.PriestName+" bat mich, ihm diese Bücher persönlich zu überbringen.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Ich verstehe, mein Kind, aber beten wir nicht täglich zu unserem Herrn: 'und vergib uns unsere Schuld, wie auch wir vergeben unseren Schuldigern'? Und die Kirche von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" reicher als meine bescheidene Gemeinde.";
			link.l1 = "Sie haben sicherlich recht, Vater, aber ich habe gerade an andere Stellen in der Heiligen Schrift gedacht: 'Suche nicht nach einem einfachen Weg, denn dort lauert der Teufel auf uns, und seine Stimme ist umso subtiler und die Versuchung umso stärker, je einfacher der Weg!' Und Padre "+PChar.GenQuest.ChurchQuest_1.PriestName+"Er wollte bereits eine Nachricht wegen deiner Vergesslichkeit an den Erzbischof schicken - ich habe ihn gerade noch davon abgebracht.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "Z-Z-Zum Erzbischof?! Wegen einer solchen Kleinigkeit!.. Warum? Wirklich? Ich wollte diese Werke sowieso meinem geliebten Bruder in Christus schicken - es gab einfach keine gute Gelegenheit, sie ihm zu überbringen. Aber in dir, "+GetSexPhrase("mein Sohn","meine Tochter")+", ich sehe einen wahrhaft verdienstvollen Diener unseres Herrn. Hier - nimm diese Bücher und Manuskripte und bitte liefere sie an Pater "+PChar.GenQuest.ChurchQuest_1.PriestName+" sicher und gesund. Und fügen Sie dazu meine aufrichtigste Dankbarkeit hinzu.";
			link.l1 = "Natürlich, "+LinkRandPhrase("Vater","Vater","Vater")+". Natürlich...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Aber, "+GetSexPhrase("mein Sohn","meine Tochter")+"... Sie sehen, das Ding ist, dass ich letzte Woche einen Kapitän des Schiffes ' traf"+sld.Ship.Name+"', wo ich gerufen wurde, um einem sterbenden Seemann die Kommunion zu spenden. Zu meiner großen Freude, Kapitän "+GetFullName(sld)+" hat mir gesagt, dass er vorhat zu "+XI_ConvertString("Colony"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". Und obwohl er keine Bedingungen verdiente, stimmte er dennoch zu, zu helfen und versicherte mir, dass der Hafen von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+"er wird sicherlich besuchen. Also nutzte ich diese Gelegenheit, schickte Bücher mit diesem freundlichen Mann weg und übergab ihr weiteres Schicksal dem Herrn.";
				link.l1 = "Hmm, bist du sicher, dass diesem Kapitän vertraut werden kann? Hat er den Wert der ihm anvertrauten Werke und die Wichtigkeit dieser Mission erkannt?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+GetSexPhrase("mein Sohn","meine Tochter")+"! Du bist nur ein paar Stunden zu spät! Ich habe bereits die Bücher des Vaters verschickt "+PChar.GenQuest.ChurchQuest_1.PriestName+" mit Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+". Heute Morgen kam dieser fromme Mann zur Beichte und erwähnte, dass sein Schiff heute segeln würde nach "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". Und obwohl Herr Kapitän keine Bedingungen gewährte, stimmte er dennoch zu, zu helfen, und versicherte mir, dass der Hafen von "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" er wird sicherlich besuchen.";
				link.l1 = LinkRandPhrase("Vater","Vater","Vater")+"... bist du sicher, dass diesem Kapitän vertraut werden kann? Und ich möchte auch wissen, wie sein Schiff heißt.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Ich vertraue Leuten, "+GetSexPhrase("mein Sohn","meine Tochter")+", jeder einzelne von uns ist nach dem Bilde unseres Herrn geschaffen, und Sein heiliges Feuer brennt in jeder Seele!";
			link.l1 = "Ugh. Das ist ein gewichtiges Argument, sicherlich. Nun... Dann segne mich, Vater, und wünsche mir Glück bei meiner Suche nach diesem Kapitän.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Du solltest den Leuten vertrauen, "+GetSexPhrase("mein Sohn","meine Tochter")+". Was sein Schiff betrifft - ich habe nichts zu sagen.";
			link.l1 = "Und du hast wertvolle Manuskripte an irgendeinen Kapitän gegeben, ohne dich sogar um den Namen seines Schiffes zu kümmern?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Sie sehen, "+GetSexPhrase("mein Sohn","meine Tochter")+", Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+" ist sehr gottesfürchtig...";
			link.l1 = "Nun, das habe ich schon gehört.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Geduld, "+GetSexPhrase("junger Mann","junge Dame")+"! Kapitän "+PChar.GenQuest.ChurchQuest_1.CapFullName+" ist eine sehr gottesfürchtige Person und bis zu diesem Tag trug sein Schiff einen Namen, den ein Geistlicher niemals auch nur im Gedanken, geschweige denn laut aussprechen sollte! Und heute während seiner Beichte habe ich ihn darauf hingewiesen. Denn wie die Bibel sagt, müssen wir Sünder die Reinheit der Seele mehr bewahren als die Reinheit des Körpers, denn unser Herr verwehrt Sein Reich den Fäkalmäulern...";
			link.l1 = "Ich verstehe, "+LinkRandPhrase("Vater","Vater","Vater")+", Ich verstehe! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", ein berüchtigter Spieler und Trunkenbold, bekannt in der gesamten Karibik, hat beschlossen, seine alte Kiste auf Ihren Vorschlag hin umzubenennen?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Du bist sehr scharfsinnig, "+GetSexPhrase("mein Sohn","meine Tochter")+". Ich kenne den neuen Namen dieses Schiffes nicht, aber es ist sicherlich etwas Erhabenes.";
			link.l1 = "Ach, "+RandPhraseSimple("Vater","Vater","Vater")+"... Danke für alles. Und bete für meine sündige Seele...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, mein Kind! Ich habe eifrig gebetet, und alles scheint sich auf bestmögliche Weise gelöst zu haben! Für deine Hilfe und deinen Glauben, "+GetSexPhrase("mein Sohn","meine Tochter")+", Paradies und engelhafter Gesang werden sicherlich auf dich warten...";
			link.l1 = RandPhraseSimple("Vater.","Vater.")+", Ich werde so bald nicht den heiligen Petrus treffen, Gott bewahre. Was die Lebenden betrifft - sie benötigen viele materielle Dinge neben Versprechen des himmlischen Glücks...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Ja, ja, "+GetSexPhrase("mein Sohn","meine Tochter")+", natürlich. Ich werde dich verdient belohnen. Hier, nimm das und denke daran, dass unser Herr jene törichten Seelen bestraft, die zu sehr nach irdischen Segnungen verlangen und den gelben Teufel anbeten!";
			link.l1 = "Danke, "+LinkRandPhrase("Vater","Vater","heiliger Vater")+". Bitte nehmen Sie Ihre lang erwarteten Bücher und Manuskripte und beten Sie für meine sündige Seele... Auf Wiedersehen!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Deine Gesundheit ist "+GetHealthNameMaxSmall(pchar)+", und die Wunden werden von selbst heilen. Sie müssen nur Blutvergießen vermeiden und auf Ihre Gesundheit achten.";
    			link.l1 = "Danke, das ist sicherlich eine Erleichterung. Ich werde versuchen, mich eine Weile von Kämpfen fernzuhalten.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Deine Gesundheit ist "+GetHealthNameMaxSmall(pchar)+", und obwohl die Wunden von selbst heilen, solltest du dich darum kümmern.";
    			link.l1 = "Was wird dafür benötigt?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "Und warum verschlechtert sich meine Gesundheit?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Das ist sehr einfach, "+GetSexPhrase("mein Sohn","meine Tochter")+". Sie nehmen Schaden jedes Mal, wenn Sie verwundet werden. Das geht nicht spurlos vorüber. Ihre Gesundheit verschlechtert sich mit jeder Wunde und Sie werden dadurch schwächer. Ihre Crew verliert den Respekt vor Ihnen, wenn sie einen schwachen Kapitän sieht. Sie werden jedoch vorsichtiger und Ihre Fähigkeit, sich zu verteidigen, erhöht sich vorübergehend. Ruhe und das Minimieren von Wunden helfen Ihnen, voller Kraft zu bleiben.";
			link.l1 = "Danke für die Aufklärung.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Gebete und Enthaltung von Gewalt, "+GetSexPhrase("mein Sohn","meine Tochter")+". Dann wird der Herr dir zurückgeben, was du verloren hast.";
			link.l1 = "Aber könnten Sie für mich beten?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Also gibt es keinen Weg? Hmm... Du hast mich wirklich beruhigt, danke.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Ich? Das ist wahrscheinlich möglich. Aber du wirst eine Spende für unsere Gemeinde machen müssen.";
    			link.l1 = pcharrepphrase("Wie viel?","Gern! Wie viel?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Ich denke, ich werde mich selbst zurechtfinden...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("Mein Sohn","Meine Tochter")+", Ich bete bereits für dein Wohlergehen. Diese Gebete werden meine ganze Zeit bis zum Ende des Monats in Anspruch nehmen.";
    			link.l1 = "Danke, "+RandPhraseSimple("Vater.","Heiliger Vater.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Einhunderttausend Pesos werden eine ausreichende Zahlung für das Wunder der Heilung sein.";
			link.l1 = pcharrepphrase("Was?!! Bist du völlig verrückt? Ich würde eine solche Summe zahlen, nachdem ich ein paar Kirchen ausgeraubt habe!","Das ist zu viel für mich. Sie sagen die Wahrheit - Gesundheit kann man nicht für Geld kaufen.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Ich stimme zu!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Gut. Deine Gesundheit wird sich ein wenig verbessern. Aber du musst immer noch Gefechte vermeiden und gut auf dich aufpassen, sonst verliert dieser Effekt seine Wirkung. Ich muss einen ganzen Monat in Gebeten für deinen vergänglichen Körper verbringen.";
			link.l1 = "Danke. Wenn etwas passiert, komme ich in einem Monat wieder, um dich zu sehen.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "Und wer ist diese freundliche Seele, die das Geld spendet?";
			link.l1 = "Hmm... Das ist die Madame des örtlichen Bordells.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Ich würde die Namen lieber geheim halten. Es kann eine anonyme Spende geben, nicht wahr?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Du bist ein Sünder, und doch fragst du einen Sünder? Du solltest zuerst an deine Seele denken, tatsächlich werden wir alle vor dem Herrn erscheinen!";
					link.l1 = "Das ist wahr. Ich hoffe, dass unser Herr mir gnädig sein wird... Also, wie steht's mit der Spende?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Hinter mich, Satan!!! Nimm dein unheiliges Geld und hau ab!";
					link.l1 = "Wie bitte, Vater?! Wir sind mit offenem Herzen zu Ihnen gekommen, und Sie...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Ich bin froh, dass du den Sündern hilfst, ihren Weg zu unserem Herrn zu finden. Dafür wirst du im Himmel deinen Lohn erhalten!";
					link.l1 = "Das wäre großartig! Also, wie steht es mit der Spende?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Ich kann kein Geld annehmen, das in Sünde erworben wurde. Gib es dieser gefallenen Frau zurück, "+GetSexPhrase("mein Sohn","meine Tochter")+". Niemand kann einen Weg zu Gott durch Geld finden.";
					link.l1 = "Es ist schade, dass du sie ablehnst. Wirklich schade.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Dieses Geld nehmen, ohne auch nur zu wissen, woher es kommt...";
				link.l1 = "Ja, Padre, genau. Bitte, akzeptieren Sie diesen Beitrag, der vom Herzen kommt!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Dieses Geld nehmen, ohne auch nur zu wissen, woher es kommt? Bist du verrückt?! Und was ist, wenn dieses Geld mit Blut befleckt ist!";
				link.l1 = "Vater, alles Geld ist mit Blut befleckt...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Ich akzeptiere es, "+GetSexPhrase("mein Sohn","meine Tochter")+". Gehe und sag das deiner gefallenen Frau.";
			link.l1 = "In Ordnung, Padre. Danke.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Ich akzeptiere es, "+GetSexPhrase("mein Sohn","meine Tochter")+". Erzähl es deinem Spender.";
			link.l1 = "In Ordnung, Pater. Danke.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Verschwinde, Brut der Hölle, und wage es nicht, dein Gesicht hier wieder zu zeigen!";
			link.l1 = "Heh, wie du willst.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "Das ist meine Entscheidung. Geh in Frieden, "+GetSexPhrase("mein Sohn","meine Tochter")+".";
			link.l1 = "Auf Wiedersehen, Padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "Das denkst du, du Gotteslästerer?! Verlasse diesen Tempel sofort und wage es nicht, hier wieder dein Gesicht zu zeigen!";
			link.l1 = "Oh, wirklich? Macht nichts, ich gehe...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Ich hatte fast die Hoffnung verloren, diese Papiere wieder zu sehen. Warum hat es so lange gedauert, mein Sohn?";
				link.l1 = "Es waren... unvorhergesehene Entwicklungen, Vater.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Ich habe auf diese Papiere gewartet, Sohn. Danke für die schnelle Lieferung. Bitte nimm diese Münzen und geh mit meinem Segen.";
				link.l1 = "Danke, Vater. Es war mir eine Freude, der Heiligen Kirche zu helfen!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Wir sind alle in Gottes Händen, mein Sohn... Der Mensch denkt, Gott lenkt. Gib mir diese Papiere und geh in Frieden.";
			link.l1 = "Hier, Vater. Alles Gute für Sie!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Gottes Segen, mein Sohn. Möge der Allmächtige dich auf deinen Reisen beschützen!";
			link.l1 = "Auf Wiedersehen, Vater.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Du wurdest geschickt, um Gebetbücher von uns zu nehmen - für die Kirche von "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Nun. Ich habe ein Paket mit dreißig Gebetbüchern. Nimm es, mein Sohn.";
			link.l1 = "Danke, Padre. Auf Wiedersehen!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Möge der Herr dich auf deinen Reisen begleiten! Geh in Frieden...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Danke für deine Hilfe, mein Sohn, obwohl sie etwas verspätet ankam.";
				link.l1 = "Ich wurde durch unvorhergesehene Ereignisse aufgehalten, Vater.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Danke für deine Hilfe, mein Sohn. Du hast diese Bücher gerade rechtzeitig gebracht. Bitte, nimm dieses geweihte Amulett als Belohnung - es wird dich in der dunkelsten Stunde vor Gefahr bewahren.";
				link.l1 = "Danke, Vater. Es war mir eine Freude, der Heiligen Kirche zu helfen!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "Alles liegt in Gottes Händen, mein Sohn. Geh in Frieden!";
			link.l1 = "Auf Wiedersehen, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Gottes Segen, mein Sohn. Möge der Allmächtige dich auf deinen Wegen vor Unheil bewahren!";
			link.l1 = "Auf Wiedersehen, Vater.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
