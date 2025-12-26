void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Wollten Sie etwas?";
			link.l1 = "Nein, nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Was für eine Überraschung! Du selbst "+GetTitle(NPChar,true)+" "+pchar.lastname+" höchstpersönlich!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Dich hätte ich hier nun wirklich nicht erwartet... Ehrlich gesagt – ich dachte, du wärst längst tot!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Ich traue meinen Augen nicht... Ein Schönling? Aber... wie?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha-ha! Das hättest du dir sparen können. Wie du siehst – ich lebe und bin wohlauf. Schau, ich habe mir ein feines, sauberes Schiff zugelegt. Und du... erzähl mal: wie bist du denn zu so einem Leben gekommen, mein Freund?";
			  }
			  else 
			  {
				dialog.text = "Ha-ha! Das war wohl ein Fehler von dir. Wie du siehst – ich lebe und bin bester Dinge. Schau, ich habe mir ein feines, sauberes Schiff zugelegt. Und du... erzähl mal: Was verschlägt dich hierher, mein Freund?";
			  }
			link.l1 = "Nicht hier. Gehen wir in die Taverne – die Angelegenheiten können warten.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Pssst... Schrei doch nicht so. Der Schönling ist Vergangenheit, genauso wie der Prinz, nehme ich an. Oder?";
			link.l1 = "Aber ich habe es doch mit eigenen Augen gesehen...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Wie sie mich umgebracht haben? Wär’s doch nur so gewesen, mein Freund. Glaub mir.";
			link.l1 = "Komm, gehen wir in die Taverne. Dort erzählst du mir alles.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Also sind Sie der neue Besitzer des Pinasschiffs '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Ich. "+GetFullName(npchar)+", wenn Sie schon so neugierig sind. Und wer sind Sie?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", und ich möchte dieses Schiff von Ihnen abkaufen.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Natürlich, natürlich, ich habe schon von Ihnen gehört. Ich dachte schon, ich hätte endlich alle Bewerber um dieses Schiff abgeschüttelt. Leider muss ich Sie enttäuschen, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' gehört jetzt mir, und schon sehr bald segle ich damit nach Bordeaux. Ich bin doch nicht ins Handelsgeschäft eingestiegen, um gleich beim ersten Geschäft alles zu verlieren. Das bringt Unglück, wissen Sie.";
			link.l1 = "Bordeaux, sagen Sie? Interessant... Vielleicht habe ich ein lukratives Angebot für Sie. Wollen wir das bei einem Becher Rum besprechen?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Es liegt nicht in meinen Prinzipien, weder Rum noch ein gutes Angebot auszuschlagen. Gehen wir.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Also, auf dich, "+GetTitle(npchar,false)+" "+pchar.lastname+". Ich wusste, dass so ein Kerl wie du nicht lange für Tirax die Drecksarbeit machen würde. Aber dass du so eine große Nummer wirst... du verstehst es wirklich, einen zu überraschen, verdammt nochmal.";
				link.l1 = "Ha-ha. Wer hätte das gedacht. Also hast du dich entschlossen, Händler zu werden?";
			  }
			  else 
			  {
				dialog.text = "Auf unser Wiedersehen! Ich hatte so ein Gefühl im Nacken, dass wir uns noch einmal begegnen.";
				link.l1 = "Ha-ha. Auf sie! Also hast du dich entschlossen, Händler zu werden?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "Man kann ja nicht ewig für ein paar Dublonen den Hals riskieren. Den Richtigen geschmiert, den Falschen zum Schweigen gebracht – und schon bin ich kein Dieb und Pirat mehr, sondern ein angesehener Kaufmann.";
			link.l1 = "Das ist ja eine Überraschung. Jetzt weiß ich gar nicht mehr, wie ich dir das anbieten soll, was ich eigentlich dem frischgebackenen Kapitän der Pinasse vorschlagen wollte. "+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Ach komm, erzähl schon, wie es wirklich war. Wir kennen uns doch schon ewig.";
			link.l1 = "Siehst du... ich bin hierher in die Karibik gekommen auf der Pinasse, die du ausgelöst hast. Als ich erfahren habe, dass sie versteigert wird, wollte ich sie zurückkaufen – und damit nach Hause, nach Frankreich, segeln.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha-ha-ha-ha! Warte... ah-ha-ha-ha-ha!..";
			link.l1 = "Na, und was ist so lustig daran?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "Kaum hatte ich die Auktion gewonnen, da kam schon ein Geck auf mich zu – jung, gepflegt: Er meinte, ich solle ihn samt seinem Hab und Gut nach Bordeaux bringen, gegen bare Münze. Und was für eine Münze – gleich ein ganzer verdammter Sack voll.";
			link.l1 = "Ach ja? Ha-ha. Das ist wirklich amüsant. Und was hast du gemacht? Zugestimmt?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", also ich wäre doch schön blöd, einen Haufen Gold für eine ganz normale Überfahrt über den Atlantik abzulehnen. Ja, ich muss wohl ein paar Monate an Zwieback und Pökelfleisch knabbern. Aber weißt du, ich habe schon für weniger Geld meinen Hals riskiert. Also, natürlich bin ich dabei.";
			link.l1 = "In diesem Fall kann ich dir dasselbe anbieten. Bring mich nach Bordeaux – und du bekommst genauso einen Haufen Münzen.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Bist du bereit, als Passagier mitzufahren? Du kennst doch unsere Regeln – an Bord gibt es nur einen Kapitän. Und auf meinem Schiff bin das ich.";
			link.l1 = "Warum nicht? Ich atme mal durch und denke über das Leben nach. Vielleicht sollte ich mich wirklich irgendwo niederlassen und sesshaft werden. Im Moment kann ich mir das kaum vorstellen, aber vielleicht hat das ja seinen Sinn. Sogar du hast schließlich beschlossen, dich von den Kämpfen fernzuhalten.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ach, hätte ich so eine schöne Frau wie du, hätte ich vielleicht selbst das Meer verlassen, mich irgendwo in der Einöde niedergelassen: ein Haus gebaut und mit Wein gehandelt. Zum Glück habe ich genug zum Leben – seit du mich aus den Klauen der Spanier gerettet hast, habe ich meine Zeit nicht vergeudet.";
			}
			else
			{
				dialog.text = "Ach, hätte ich so eine schöne Frau wie du, dann hätte ich vielleicht auch das Meer verlassen und mich irgendwo in der Einöde niedergelassen: ein Haus gebaut und mit Wein gehandelt. Zum Glück gäbe es genug zum Leben – das Erbe der Plantagenwitwe war beachtlich.";
			}
			link.l1 = "Meine Frau! Teufel, "+npchar.name+", ich habe ja noch nicht mit ihr darüber gesprochen.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Dafür hast du noch mehr als genug Zeit. Ich muss mein Kahn erst mal richtig ausrüsten. Wenn du mit allem fertig bist, schlepp deinen Hintern hierher. Dann feiern wir noch ordentlich, bevor wir in See stechen.";
			link.l1 = "Das ist ganz nach meinem Geschmack! Keine Sorge, lange wirst du nicht warten müssen.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ach, hätte ich eine Frau, würde ich vielleicht selbst das Meer verlassen und mich irgendwo in der Einöde niederlassen: ein Haus bauen und ein wenig mit Wein handeln. Aber solange... ist das Meer mein Zuhause.";
			link.l1 = "Mit Wein von meinen Plantagen, ha-ha! In Bordeaux, "+npchar.name+", solche Mädchen sind wirklich eine Augenweide! Vielleicht findest du dort ja auch jemanden für dich – in Liebesdingen sind sie gar nicht übel. Weißt du, was ich mir gedacht habe? In den nächsten Monaten werden wir wohl nur die Fratzen deiner Matrosen zu sehen bekommen. Wir sollten vor der Abreise unbedingt noch ein ordentliches Fest im hiesigen Bordell feiern.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "Und Sie, Monsieur, wissen schon, was Sie vorschlagen wollen. Wenn Sie mit all Ihren Angelegenheiten fertig sind – bewegen Sie Ihren Hintern hierher. Und dann gehen wir auch noch ins Bordell, darauf können Sie sich verlassen.";
			link.l1 = "Nun gut, dann verliere ich keine Zeit. An die Arbeit!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Für die Freiheit!";
			link.l1 = "Und auf dich, Jean! Auf deine Rückkehr ins Leben! Ich kann es immer noch kaum glauben. Wie ist das möglich?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Man hat mich halbtot, von Kopf bis Fuß blutüberströmt, vom Schlachtfeld geschleift. Dann warf man mich in eine Baracke und ließ mich dort wie Aas verrecken. Unter den Sklaven war ein ziemlich gewitzter Kerl – Moko. Er hat mir das Leben gerettet: Er hat meine Wunde mit einem Stück meines eigenen Hemdes verbunden und mir Wasser gegeben.";
			link.l1 = "Willst du sagen, die Spanier haben dich nach alldem am Leben gelassen?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Wie du siehst. Aber nicht aus reiner Herzensgüte. Sie wollten Vergeltung – ein Verhör mit Nachdruck, Folter. Sie haben gebrannt, geschlagen, geschnitten. Sie drohten, mir die Augen auszubrennen – natürlich nur aus großer Liebe zu mir. Aber dann hat jemand das Gerücht gestreut, dass die Piraten Rache für mich nehmen wollen und schon die Messer wetzen. Dem Plantagenbesitzer zuckte gleich das Auge. Er wollte den Besuch unserer Brüder nicht abwarten und ist eilig in seine Besitzungen nach Campeche geflohen. Uns, Moko und die anderen, hat er mitgenommen, damit keine Zeugen übrigbleiben. Den anderen hat er erzählt, ich sei gestorben – und damit war die Sache erledigt.";
			link.l1 = "Und was ist dann passiert? Wie bist du freigekommen? Und wie zum Teufel bist du hier gelandet?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Glück, mein Freund. Blindes, dreckiges Glück. Man brachte mich auf die Plantage – und die Folter ging weiter. Dieser Bastard beschloss, jede Sekunde meines Leidens auszukosten, aber mit jedem Tag wurde er schwächer... bis er schließlich am Fieber krepiert ist. Danach hat sich niemand mehr um mich geschert. Sie haben mich aufs Feld gejagt wie ein Vieh, und die Peitsche gab’s dazu reichlich.";
			link.l1 = "Ich verstehe immer noch nicht, wie du da rausgekommen bist?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Hast du von Christopher Myngs gehört?";
			link.l1 = "Alonso hat da mal was erwähnt... Der Überfall auf Campeche! Die haben damals die Spanier ganz schön fertiggemacht. Waren das also die, die dich befreit haben?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Nicht ganz. Wir haben uns selbst befreit. Während die Wachen gegen eine englisch-bukanierische Truppe kämpften, haben Moko und ich ein Schlupfloch im Dach der Baracke gefunden und einen Aufstand angezettelt. Wir haben das Arsenal und die Kasse der Frau des verstorbenen Dreckskerls von Plantagenbesitzer erbeutet.";
			link.l1 = "Die Staatskasse?! Das ist ja eine Überraschung.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Wir haben nicht lange überlegt – mit Waffen und Habseligkeiten sind wir in den Dschungel gezogen. Zwei Tage lang haben wir uns durch das Dickicht geschlagen, bis wir auf ein Dorf der Can Pech-Indianer gestoßen sind. Ihr Schamane tat nur so, als würde er den Spaniern gehorchen, aber besonders viel Sympathie hatte er für sie nicht. Moco hat sich schnell mit ihm verstanden – sie haben uns aufgenommen, im Tausch gegen die Hälfte unseres Arsenals und unsere Hilfe im Krieg, gegen wen auch immer. So habe ich dort anderthalb Jahre gelebt.";
			link.l1 = "Du, Jean, bist nicht mehr der, der du früher warst. Von nun an bist du der Glückspilz.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha-ha. Dagegen habe ich nichts einzuwenden. Und dann hat es einen französischen Prediger in unser Bataillon verschlagen. Uns war sofort klar: Das ist unsere Chance, hier rauszukommen, ohne in Ketten zu landen. Wir haben seine Eskorte bestochen – und kurz darauf segelten wir schon nach Tortuga.\nUnd dann, wie du dir sicher schon denken kannst, habe ich beschlossen, dem Tod nicht länger hinterherzulaufen. Ich habe mit dem alten Handwerk Schluss gemacht... und mir bei Gelegenheit etwas zugelegt."+GetShipName("Ulysse")+"'.\n"+"Und du? Wie bist du zu so einem Leben gekommen? Ich wusste ja, dass so ein Draufgänger wie du nicht lange für Tirax die Drecksarbeit machen würde. Aber dass du mal so ein hohes Tier wirst... du verstehst es wirklich, einen zu überraschen, verdammt nochmal.";
			link.l1 = "Ha-ha. Wer hätte das gedacht. Also hast du dich entschlossen, Händler zu werden?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "Auf die, die auf See sind!";
			link.l1 = "Und auf das Glück, Madame!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Also, kommen wir zur Sache. Was wollten Sie mir vorschlagen?";
			link.l1 = "Ihr reist nach Bordeaux... Seht ihr, ich bin ebenfalls auf dem Weg dorthin.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Wollen Sie, dass ich Sie an Bord nehme? Soweit ich weiß, sollten Sie doch Ihr eigenes Schiff haben. Vielleicht sogar eine ganze Flotte. Und trotzdem haben Sie sich entschieden, auf einem fremden Schiff zu reisen. Habe ich das richtig verstanden?";
			link.l1 = "Genau so ist es. Die letzten Ereignisse haben mich nachdenklich gemacht: Vielleicht ist es an der Zeit, vor Anker zu gehen, sesshaft zu werden... Ich denke, die Rolle eines einfachen Passagiers auf eurem Schiff wird mir helfen zu erkennen, ob ich mich auf einen neuen Lebensrhythmus einlassen kann.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hm... Also, Sie haben genug davon, Ihren Hals ohne Grund zu riskieren? Das kenne ich. Ich selbst... Ach, egal. Ein Platz auf dem Schiff findet sich für Sie, auch für Ihre ganze Gefolgschaft. Die Überfahrt ist bereits von einem jungen Franzosen bezahlt – und er zahlt auch für die Eile, also werde ich die Laderäume nicht vollpacken. Was die Bezahlung angeht...";
			link.l1 = "Machen Sie sich keine Sorgen, Kapitän. Ich stehe Ihrem Auftraggeber in Großzügigkeit in nichts nach und bin bereit, denselben Betrag zu zahlen.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Hervorragend! Dann sind wir uns einig?";
			link.l1 = "Abgemacht! Darauf sollten wir trinken!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Ja, der Rum ist wirklich gut... Ich brauche zwei Wochen, um das Schiff in Schuss zu bringen und alles Nötige zu besorgen. Danach können wir in See stechen.";
			link.l1 = "Dann treffen wir uns in zwei Wochen wieder hier. Also, bis bald, Kapitän.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Na, mein Freund, hast du deine Angelegenheiten geregelt? Zeigen wir diesem Hühnerhaufen, wie man richtig feiert?";
				link.l1 = "Noch nicht die Zeit, "+npchar.name+", ich habe noch ein paar Dinge zu erledigen.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Kapitän, sind Sie bereit, an Bord zu gehen?";
				link.l1 = "Leider, Kollege, ich habe noch zu tun.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "He, Wirt! Für alle eine Runde auf meine Kosten! Und nicht irgendein Fusel, sondern das Beste, was du hast!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Auf uns, mein Freund. Auf den salzigen Wind, auf das endlose Meer und auf den Horizont – ewig lockend, ewig unerreichbar...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", Liebling, ich möchte mit dir über meinen Vater sprechen.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Was ist passiert, mein Lieber? Ich hoffe, es geht ihm gut, ja?";
			link.l1 = "Nun, nicht so gut, wie man es sich wünschen würde. Es gibt Gründe zu glauben, dass er nicht mehr lange durchhält, und ihn beunruhigt sehr der Gedanke, mich vielleicht nicht mehr zu sehen, bevor er seine letzte Reise antritt.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Ich weiß, meine Liebe, ich weiß... Aber so ist das Leben. Ich hätte mir gewünscht, dass ihr euch kennenlernt. Damit er sieht, was für eine wunderbare Frau ich habe, und uns seinen Segen gibt.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "Und was, wenn ich ihm nicht gefalle, ja? Ich bin schließlich kein Adelskind...";
			link.l1 = "Unsinn, "+npchar.name+", wie könntest du ihm nicht gefallen? Du bist doch ein Wunder! Wenn du schon mein Herz erobert hast – wirst du auch seines gewinnen.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Denkst du das wirklich, Liebling? Dann sollten wir so schnell wie möglich zu ihm aufbrechen.";
			link.l1 = "Genau das habe ich auch vor. Ich habe sogar schon ein Schiff für uns gefunden. In zwei Wochen stechen wir in See.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "Ein Schiff? Wir fahren nicht mit unserem eigenen?";
			link.l1 = "Nein, meine Liebe. Wir fahren mit der Pinasse '"+GetShipName("Ulysse")+"'. Mit ihm bin ich in die Karibik gekommen – mit ihm werde ich sie auch wieder verlassen.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "Und du wirst kein Kapitän sein?";
			link.l1 = "Früher oder später hätte ich diese Rolle sowieso ablegen müssen. Ich hoffe, es ist nur vorübergehend. Aber so oder so schadet es nicht, ein Gefühl dafür zu bekommen, was mich in Zukunft erwartet.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "Und was ist mit unseren Offizieren? Wir können sie doch nicht alle mitnehmen. Und hier auf dich warten werden sie wohl auch kaum.";
			link.l1 = "Ähm... Ja, du hast recht. Ich werde wohl mit jedem von ihnen sprechen müssen, und mich wahrscheinlich für immer verabschieden. Auch wenn das alles andere als leicht wird – nach allem, was wir gemeinsam durchgemacht haben.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Vielleicht sollten wir zum Abschied ein kleines Fest in der Taverne veranstalten?";
			link.l1 = "Ich habe auch darüber nachgedacht, meine Liebe. Weißt du... vielleicht hast du recht. Das ist wirklich eine gute Idee.";
			link.l1.go = "exit";
			link.l2 = "Ich glaube nicht, dass das eine gute Idee ist. Wir kommen auch ohne großes Abschiednehmen aus... So ist es wohl für alle besser. Vielleicht laden wir nur unsere engsten Freunde ein...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Meine Liebe, ich möchte mit dir über meinen Vater sprechen.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Natürlich, "+pchar.name+". Hoffentlich geht es ihm gut?";
			link.l1 = "Nicht ganz. Er ist schon lange krank, und ich fürchte, die Krankheit wird bald siegen... Vater erträgt das alles mit großer Tapferkeit. Das Einzige, was ihn wirklich beunruhigt – er könnte mich nie wiedersehen. Ich möchte ihn besuchen... und dich ihm vorstellen. Seinen Segen für unsere Ehe erhalten.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Ich freue mich darauf, ihn kennenzulernen, mein Liebster. Wann brechen wir auf?";
			link.l1 = "In zwei Wochen. Aber das ist noch nicht alles. Wir werden nicht mit unserem eigenen Schiff reisen. In die Alte Welt bringt uns die Pinasse '"+GetShipName("Ulysse")+"– derjenige, der mich einst hierher gebracht hat.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", aber das Schiff vor einer langen Reise zu wechseln, bringt Unglück.";
			link.l1 = "Wir werden das Schiff nicht wechseln, Liebes. Wir werden Passagiere sein.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Aber... Liebling, ich verstehe nicht...";
			link.l1 = "So muss es sein, "+npchar.name+". Früher oder später werde ich das Kommando abgeben müssen. Und ich möchte vorher wissen, mit welchen Gefühlen ich dann konfrontiert sein werde.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Wenn du dich so entschieden hast... Aber was ist mit unseren Offizieren? Wir können sie doch nicht alle mitnehmen. Und hier auf dich warten werden sie wohl auch nicht.";
			link.l1 = "Ähm... Ja, du hast recht. Ich werde wohl mit jedem von ihnen sprechen müssen, und mich vermutlich für immer verabschieden. Auch wenn das alles andere als leicht wird – nach allem, was wir gemeinsam durchgemacht haben.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Vielleicht sollten wir zum Abschied ein kleines Fest in der Taverne veranstalten?";
			link.l1 = "Ich habe auch darüber nachgedacht, meine Liebe. Weißt du... ich denke, das machen wir so. Das ist wirklich eine gute Idee.";
			link.l1.go = "exit";
			link.l2 = "Ich glaube nicht, dass das eine gute Idee ist. Wir kommen auch ohne großes Abschiednehmen aus... So ist es wahrscheinlich für alle besser. Vielleicht laden wir nur unsere engsten Freunde ein...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Käpt’n... Ich habe schon mit dem Wirt gesprochen – er hat das beste Gebräu vorbereitet, das er hat. Wann legen wir los?";
				link.l1 = "Jetzt gleich! Hey, Wirt! Für alle eine Runde auf meine Kosten!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Käpt’n, Sie wollten mir doch erzählen, wie Sie vom 'Ulysses' erfahren haben.";
				link.l1 = "Ich erinnere mich, ich erinnere mich. Hey, Wirt! Den besten Rum an diesen Tisch.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Zu früh, "+npchar.name+". Ich habe noch dringende Angelegenheiten zu erledigen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Na los, mein Freund, ruf die anderen – wir zeigen Saint-Pierre, wie echte Seewölfe feiern!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha-ha! Käpt’n, Sie werden es nicht glauben – ich habe sie schon gerufen!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Auf uns, "+npchar.name+".   Auf das Glück und auf den Wind, der unsere Segel füllt!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Was für ein Chaos wir angerichtet haben, Käpt’n. Ha-ha. Ich glaube, die Taverne wurde nur durch die mageren Rumvorräte des Wirts vor dem völligen Ruin bewahrt.";
			link.l1 = "Erinnere mich bloß nicht daran, "+npchar.name+",   jetzt geht es mir erst ein wenig besser.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Wie Sie wünschen, mein Herr "+pchar.lastname+". Haha. Aber immerhin haben wir uns königlich von Martinique verabschiedet. Man wird sich dort noch lange an eure Abreise erinnern.";
			link.l1 = "Ich glaube, wir haben ein bisschen übertrieben, als wir den Wirt ins Beiboot gesetzt und nach Le François geschickt haben, um Nachschub zu holen.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha-ha-ha. Machen Sie sich um ihn keine Sorgen. In den letzten Tagen hat er so viel Gold verdient, dass er sich eine Plantage kaufen kann – und dazu noch einen Adelstitel.";
				}
			else
				{
					dialog.text = "Ha-ha-ha. Machen Sie sich um ihn keine Sorgen. In den letzten Tagen hat er so viel Gold verdient, dass er sich eine Plantage kaufen und dazu noch einen Adelstitel leisten könnte. Schade nur, dass Sie mit keinem der Offiziere gesprochen haben. Wir werden sie vermissen.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Es scheint, "+sld.name+" ist immer noch wütend auf Sie, weil Sie die halbe Nacht verschwunden waren.";
			}
			else
			{
				dialog.text = "Und mit diesem Händler… da, mein Kapitän, sind Sie wirklich zu weit gegangen.";
			}
			link.l1 = "Verdammt, ausgerechnet wir mussten mit Jean in diesen Laden gehen…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "Und wie haben sie euch bloß nicht erwischt? Das wäre ein Spaß gewesen – "+GetTitle(PChar,true)+"   beim Versuch erwischt, ein paar Flaschen Wein zu stehlen.";
			link.l1 = "Du findest das lustig, "+npchar.name+", und ich erinnere mich nicht mal an die Hälfte davon. Das letzte Mal, dass ich so betrunken war... ungefähr... ungefähr nie.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Na dann, auf einen guten Anfang, Käpt’n. Ha-ha. Mir hat’s gefallen. Ich würde es wieder tun. Wann sagst du, kehren wir zurück?";
			link.l1 = "Geh lieber und schau nach unserem Gepäck. Haben wir auch wirklich alles mitgenommen? Ich komme später runter – die stickige Luft im Laderaum würde mir jetzt bestimmt nicht guttun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Sieh dir das nur an... das Schiff hat es ganz schön durchgeschüttelt.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Hier ist doch ein verdammter Haufen Gold, Käpt’n!";
			link.l1 = "Ich sehe, "+npchar.name+".   Das muss alles schnell in die Truhen, bevor die Mannschaft es sieht.   Solche Versuchungen brauchen sie nicht.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Nein, ich kann nicht widerstehen...";
			link.l1 = "Was?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "He, was ist denn mit dir?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Na los, steh auf. Hast dir auch 'ne Zeit ausgesucht...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Schließen Sie sich uns an, Käpt’n.";
			link.l1 = "Steh auf, hör auf, dich wie ein Narr zu benehmen.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Entspannen Sie sich doch. Sie müssen das einfach fühlen.";
			link.l1 = "Na gut, zum Teufel mit dir. Na los, rück mal zur Seite.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Ich habe immer davon geträumt, das einmal zu tun…";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Ein großartiges Gefühl, nicht wahr, Käpt’n?";
			link.l1 = "Ha-ha-ha. So habe ich also die Karibik besucht – nur um herauszufinden, wie es meinem Bruder geht. Vater hat mit so einer Wendung bestimmt nicht gerechnet. Ha-ha!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Mein Herr "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha-ha! Erinnern Sie sich, wie Sie auf dem Archipel angekommen sind?";
			link.l1 = "Und ob ich mich erinnere. Ha-ha. Kaum zu glauben, dass ich einmal genauso ein Geck war wie der, der jetzt über das Deck stolziert. So viel habe ich in diesen verfluchten Karibikinseln erlebt… Intrigen, Untote, Bruder Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Sie haben verdammt viel Glück, Käpt’n. So ein Vermögen zu machen und dabei noch mit dem Leben davonzukommen… das schafft nicht jeder.";
			link.l1 = "Na gut. Genug gefaulenzt. Es wäre noch schöner, wenn uns wirklich jemand erwischt.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Hör mal, mein Freund, mir gefällt der Spill-Sicherungsmechanismus auf diesem Schiff nicht. Der ist viel zu unsicher. Nicht, dass den jemand aus Versehen löst.";
			}
			else
			{
				link.l1 = "Hören Sie, Kapitän, mir gefällt die Winsch-Sicherung auf diesem Schiff nicht. Die ist viel zu unsicher. Nicht, dass sie jemand aus Versehen löst.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ach, komm, "+pchar.name+",   auf dem Schiff weiß jeder, dass…";
			}
			else
			{
				dialog.text = "Ach, kommen Sie schon, Kapitän. Wer würde denn nur auf so etwas kommen...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "He, du Holzkopf... Was zum Teufel treibst du da? Hat man dir nie beigebracht, deine krummen Stelzen aus fremden Angelegenheiten rauszuhalten?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Immer mit der Ruhe, vergiss dich nicht! Ich bin ein Edelmann und dulde das nicht…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "Auf meinem Schiff bist du niemand. Meine Matrosen haben hier mehr Rechte als du. Also entweder hältst du dich ruhig und störst niemanden, oder ich werfe dich höchstpersönlich über Bord.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha-ha-ha. Es ist, als hätte ich mich selbst von außen betrachtet.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Wovon redest du?";
				link.l1 = "Ja, ist doch egal, "+npchar.name+". Sei nicht so streng mit unserem Passagier. Für ihn ist das alles noch neu. Schließlich sind auch wir nicht über Nacht zu Seebären geworden.";
			}
			else
			{
				dialog.text = "Wovon sprechen Sie?";
				link.l1 = "Beachten Sie das nicht, "+npchar.name+". Und seien Sie nicht zu streng mit Ihrem Passagier. Für ihn ist das alles neu. Schließlich sind auch wir nicht als Seebären geboren worden.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Mit seinem Talent wird er sich eher um die Ankerwinde wickeln, als ein Seemann zu werden. Auf so was muss man erst mal kommen…";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Wer weiß, wer weiß. Ich kam auf das Archipel als genauso sorgloser, neugieriger und überheblicher Jüngling.";
			}
			else
			{
				link.l1 = "Wer weiß. Als ich auf dem Archipel ankam, war ich genauso ein sorgloser, neugieriger und eingebildeter Jüngling.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Na toll, was für ein Vergleich.\n"+"Warte mal\n"+"Siehst du dich etwa in ihm? Ha-ha-ha. Dann nimm ihn doch unter deine Fittiche. Ich werde mich jedenfalls nicht mit ihm abgeben.";
				link.l1 = "Ich werde ein Auge auf ihn haben. Solange du ihm nicht das Fell über die Ohren ziehst. Aber für den Anker soll er voll zahlen.";
			}
			else
			{
				dialog.text = "Haben Sie sich etwa in ihm wiedererkannt? Ha-ha. Na gut, Kapitän, dann nehmen Sie ihn eben unter Ihre Fittiche. Ich werde mich jedenfalls nicht mit ihm abgeben.";
				link.l1 = "Ich behalte ihn im Auge. Solange ihr ihm nicht das Fell über die Ohren zieht. Aber für den Anker soll er gefälligst bezahlen, wie es sich gehört.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Anker werfen. Auf den Wind warten. Kurs halten.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Anker lichten. Wir nehmen den Wind auf. Kurs Nordost.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Anker lichten! Klüver runter – wir fangen den Wind. An die Arbeit...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Was machst du?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Was machst du?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Nein, was tust du?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... Was machst du da? Der Obermaat wiederholt die Befehle des Kapitäns.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "So wiederholt der Obermaat ihre Worte.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Lass das, Alonso. Wir sind hier nur Passagiere. Hast du das vergessen?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Ähm... Verzeihung, Käpt’n. Konnte mich nicht zurückhalten\nAber es hat sich gelohnt. Es war, als wäre ich für einen Moment in der Vergangenheit gewesen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"...   Was wünschen Sie?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Na, mein Freund, wie fühlst du dich?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Gib es zu, "+npchar.name+", du hast doch schon damals beschlossen, Händler zu werden, als du dich von Tirax abgewandt hast?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Gib es zu, "+npchar.name+", du hast doch schon damals auf der Plantage davon geträumt, Händler zu werden, oder?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Ich erinnere mich genau, dass irgendein Bote versucht hat, mit mir zu sprechen. Aber beim besten Willen – ich kann mich nicht erinnern, worum es ging. Weißt du vielleicht etwas darüber?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Waren Sie schon einmal in Bordeaux, Kapitän?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Kapitän, um ehrlich zu sein, erinnere ich mich kaum daran, wie wir Martinique verlassen haben. Ich sollte wichtige Post von einer bestimmten Person erhalten, aber anscheinend ist sie nie bei mir angekommen. Hat sich deswegen vielleicht jemand an Sie gewandt?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Es scheint, als käme eine leichte Brise auf. Zeit, die Segel zu setzen. (In See stechen)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Noch nichts. Ich gehe dann.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha-ha... Wie noch nie zuvor! Voller Kraft und Gesundheit.";
			link.l1 = "Wirklich? Du siehst aus, als hätte dich ein Hai durchgekaut.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Wer sagt das denn? Du selbst siehst doch aus wie ein geprügelter Hund.";
			link.l1 = "Und ich fühle mich genauso. Haha. Verdammt, ich weiß nicht mal mehr, wie und wann wir eigentlich abgelegt haben.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ach, das war ein rauschendes Fest. Nur leider verdammt teuer. Meine Trottel hätten beinahe das Bordell abgefackelt – ich musste einen Sack voll Münzen springen lassen, um den Skandal zu vertuschen. Jetzt stehen mir diese Dummköpfe bis ans Lebensende in der Schuld.\nUnd, wie gefällt dir die Rolle des Passagiers? Heulst du schon vor Langeweile?";
			link.l1 = "Ich habe das Gefühl, als hätte ich mein Schicksal nicht mehr selbst in der Hand. Aber gleichzeitig spüre ich eine seltsame Erleichterung. Als hätte ich eine Kiste voller Kanonenkugeln von meinen Schultern geworfen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha-ha. Also gut, wenn dich die Sehnsucht packt – ich bin bereit, dich als Offizier bei mir aufzunehmen.";
			link.l1 = "Sehr großzügig von dir, aber ich muss ablehnen. In der ganzen Karibik gibt es nicht genug Rum, um unsere Gelage zu versorgen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Nicht ganz, mein Freund. Der Gedanke kam mir zwar hin und wieder, aber ich habe ihm nie viel Beachtung geschenkt. Dann kam er zum zweiten Mal zurück, als ich hörte, dass die ganze Bande von Tyracs treuen Hunden spurlos verschwunden ist. Jeder einzelne – der Hackmesser, der Glatzkopf und sogar dieses alte stinkende Luder Leprechaun.\nUnd als ich dann hörte, was für Erfolge du erzielt hast, habe ich endgültig beschlossen, dass es mir reicht. Man kann nicht ewig für ein paar Münzen seinen Kopf riskieren.\nGold habe ich genug, um mich nie wieder vor irgendeinem Bastard mit Perücke zu bücken. Aber das Meer hinter mir zu lassen... darauf war ich nicht vorbereitet. Also habe ich beschlossen, mir eine neue Beschäftigung zu suchen.";
			} 
			else 
			{
				dialog.text = "Nicht ganz, mein Freund. Der Gedanke kam mir hin und wieder, aber ich habe ihm nie wirklich Beachtung geschenkt. Zum zweiten Mal ließ er mich nicht los, als ich hörte, dass die ganze Bande von Tirax’ treuen Hunden spurlos verschwunden ist. Jeder einzelne – der Beil, der Glatzkopf und sogar dieser alte stinkende Lump Leprikon.\nUnd als mir dann im Gefecht feindliche Kugeln gleich zweimal fast das Hirn rausgepustet hätten, habe ich endgültig beschlossen: Es reicht. Man kann nicht ewig für ein paar Münzen seinen Kopf riskieren.\nGold habe ich genug, um mich nie wieder vor irgendeinem Bastard mit Perücke zu bücken. Aber das Meer hinter mir zu lassen... darauf war ich nicht vorbereitet. Also habe ich beschlossen, mir ein anderes Leben zu suchen.";
			}
			link.l1 = "Tesak, der Glatzkopf, der Leprechaun... Weißt du, wohin sie verschwunden sind?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Nein, ich weiß es nicht. Und ehrlich gesagt – es ist mir völlig egal, wohin diese Biester verschwunden sind. Von mir aus könnten sie zum Teufel gehen.";
			link.l1 = "Genau dorthin habe ich sie auch geschickt.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Also warst du es, der ihre ganze Bande ausgelöscht hat? Nicht schlecht! Und Markus hat dir das verziehen?";
			link.l1 = "Er weiß nichts davon. Und höchstwahrscheinlich wird er es auch nie erfahren.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Also, verdammt noch mal, da habe ich sie ja gerade rechtzeitig verlassen, haha. Du hättest am Ende wohl auch meinen Kopf nicht verschont\nNur eines verstehe ich nicht – warum zum Teufel hast du das überhaupt gemacht?";
			link.l1 = "Du hattest recht – für ein bisschen Gold würden diese Halunken alles tun: verraten, töten, sich gegenseitig an die Kehle gehen. Man hat uns mit einer Geschichte über unermessliche Schätze in eines der Verliese auf dem Süd-Main gelockt. Es war eine sorgfältig geplante Falle, und diese verdammten Holzköpfe haben den Köder ohne zu zögern geschluckt. Anstatt die Beute gerecht zu teilen, dachten sie, es wäre einfacher, mich umzubringen und alles für sich zu behalten.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "Und zum Teufel, das hat bei denen überhaupt nicht geklappt, haha! Warte mal, wer hat diese Falle überhaupt gestellt?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Ein gewisser Zorro, ein spanischer Volksrächer – als Vergeltung für Cartagena. Wer dieses Gemetzel überlebt hätte, wäre für immer im Kerker geblieben – alle Ausgänge waren verschlossen. Doch der Bastard hatte Pech – mein Offizier hat ihn überlistet.";
			}
			else
			{
				link.l1 = "Ein gewisser Zorro, ein spanischer Volksrächer – als Vergeltung für Cartagena. Wer dieses höllische Gemetzel überlebt hätte, sollte für immer im Kerker bleiben – alle Ausgänge waren fest verschlossen. Mir ist die Flucht gelungen. Aber zu einem sehr hohen Preis.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Wenigstens hast du überlebt. Und ich nehme an, du hast auch das ganze Gold eingesackt, für das du beinahe mit deinem eigenen Hals bezahlt hättest?";
			link.l1 = "Es gab dort kein Gold. Es war nur vergoldetes Blei...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Nach all dem habe ich beschlossen, Tirax zu verlassen. Du bist der Erste, dem ich das erzähle. Abgesehen von meinen Offizieren.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Ich sage nur ungern 'Ich hab's ja gesagt', aber... ich hab's ja gesagt.";
			link.l1 = "Rechtzeitig aufzuhören ist nicht gerade meine Stärke. Also musst du mir wohl ein paar Lektionen erteilen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Du kennst mich doch – für ein paar Krüge guten Rums erzähle ich dir sogar von meinem Goldversteck, hehe.";
			link.l1 = "Von mir brauchst du so viel Großzügigkeit nicht zu erwarten, ha-ha-ha. Deine Vorräte reichen dir völlig aus.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Schon klar. Er hat versucht, dir irgendwelche Briefe anzudrehen – entweder von einem Ben oder von einem Benedikt. Aber du hast ihn angefahren, dass du keinen Ben kennst, und ihm gedroht, ihn aus der Taverne zu werfen, falls er uns weiter die Stimmung verdirbt.";
			link.l1 = "Verdammt... Das waren wohl Briefe von Abt Benoît. Wichtige Briefe.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Na, dann ist es ja gut, dass ich sie mitgenommen habe. Hehe.  Ich hatte so ein Gefühl, dass der Bengel den richtigen erwischt hat. Hier, nimm.";
			link.l1 = "Du hast mir wirklich aus der Klemme geholfen, "+npchar.name+", danke.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Ein einfaches 'Danke' reicht nicht, Freundchen. Du schuldest mir einen Drink – und zwar den besten, den es in Bordeaux gibt.";
			link.l1 = "Du bekommst schon deinen Drink, du Bettler. Unser Rum ist natürlich nicht mit dem karibischen zu vergleichen, aber der Wein... So einen hast du bestimmt noch nie getrunken.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Kam nie dazu...";
			link.l1 = "Ich beneide Sie. Ich würde Bordeaux gern noch einmal so sehen wie beim ersten Mal. Sie bevorzugen vermutlich Rum, aber ich empfehle Ihnen trotzdem, die Weinausstellung beim Rathaus zu besuchen. Für unseren Claret sind Kenner in der Karibik bereit, ein Vermögen zu zahlen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Ich danke Ihnen für den Rat. Darf ich eine Frage stellen?";
			link.l1 = "Natürlich.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Wie fühlt es sich an, nach all den Jahren am Steuer plötzlich nur noch Passagier zu sein? Haben Sie sich schon an diese neue Rolle gewöhnt?";
			link.l1 = "Hm... Ich werde das Gefühl nicht los, als hätte ich mein Schicksal nicht mehr selbst in der Hand. Und doch spüre ich eine seltsame Erleichterung. Als hätte ich eine Kiste Kanonenkugeln von meinen Schultern geworfen. Ich denke, es ist noch zu früh, um Schlüsse zu ziehen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Angesichts der verdammten Flaute, in die wir so schön geraten sind, habt ihr mehr als genug Zeit.";
			link.l1 = "In guter Gesellschaft ist selbst Flaute nicht schlimm. Und was die Gesellschaft angeht, Kapitän, muss ich zugeben, da habe ich wirklich Glück gehabt.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Hat er. Ein Bote von irgendeinem Abt. Ich vergesse immer, Ihnen diese Briefe zu geben. Hier, bitte.";
			link.l1 = "Hervorragend. Sie haben mir wirklich sehr geholfen, Kapitän. Ich danke Ihnen.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Du hast recht.";}
			else {dialog.text = "Ihr habt recht.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Wind von Steuerbord! Setz alles, von der Fock bis zum Besan! Volle Fahrt voraus!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Ein ausgezeichnetes Schwert, "+GetTitle(NPChar,true)+". Darf ich mal sehen?";
			link.l1 = "Vielleicht ein andermal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Wann schlagen endlich diese Sanduhren? Mir läuft schon das Wasser im Mund zusammen.";
			link.l1 = "Nur Geduld, Matrose.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Hast du gesehen, was für eine Ratte da vorbeigelaufen ist? Ich schwöre, so riesige habe ich noch nie gesehen!";
			link.l1 = "Tja...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Was soll ich jetzt nur tun, Monsieur? Ich habe so viel getrunken, dass ich mich gar nicht mehr erinnere, wie ich auf dieses Schiff gekommen bin. Ich bin doch kein Seemann... Und zu Hause warten meine Frau und zwei Kinder.";
			link.l1 = "Du hättest weniger trinken sollen. Aber jetzt ist es zu spät – jetzt musst du wohl Seemann werden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Es ist uns eine Ehre, Sie an Bord unseres Schiffes zu begrüßen.";
			link.l1 = "Ihr seid sehr höflich, Monsieur Obermaat. Höflichkeit ist keine allzu verbreitete Eigenschaft unter erfahrenen Seewölfen. Aber wir wollen die Mannschaft nicht in Verlegenheit bringen – wir sind schließlich nicht am Hofe Seiner Majestät. Nenn mich einfach: Kapitän.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Nun, Seemann bin ich erst seit Kurzem. Früher war ich Schreiber bei Monsieur Levasseur. Und als er dann… ähm… aus dem Weg geräumt wurde, kam ein neuer Gouverneur. In bestimmten Kreisen sprach es sich schnell herum, was für ein Schurke dieser Seigneur de René de Boisdufflé de Lettre ist. Da wurde mir klar: Einen anständigen Job finde ich hier nicht mehr. Die Leute werden denken, ich hätte alles gewusst – und geschwiegen.";
			link.l1 = "War das etwa nicht so?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Natürlich nicht. Ich habe mir nie angewöhnt, mich in fremde Angelegenheiten einzumischen. Außerdem hat Levasseur Neugier immer streng bestraft.";
			link.l1 = "Das glaube ich gern.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Also, nachdem ihr ihn aus dem Weg geräumt habt, heuerte ich als Matrose auf dem erstbesten Piratenschiff an. Und, seltsamerweise, gewöhnte ich mich ziemlich schnell ein und veränderte mich. Sogar unter den wildesten Halunken konnte ich mir Respekt verschaffen. Aber das, womit sie sich beschäftigten... das war nicht meine Welt. So bin ich schließlich hier gelandet.";
			link.l1 = "Also wusstest du von meiner Beteiligung am Schicksal von Levasseur?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Natürlich, Kapitän. Und ich bin froh, dass Sie die Welt von diesem Ungeheuer befreit haben. Gleichzeitig haben Sie mich aus meinem muffigen Kämmerchen geholt. Sie haben mich dazu gebracht, mein Leben mit neuen Augen zu sehen.";
			link.l1 = "Erstaunlich, wie klein die Welt doch ist...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "So widersprüchlich es auch klingen mag, die Welt ist ebenso klein wie sie groß ist.";
			link.l1 = "Lustig. Darüber habe ich noch nie nachgedacht.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Kapitän "+pchar.lastname+"... Was für ein wunderbarer Abend heute, nicht wahr?";
			link.l1 = "Vielleicht. Noch besser wäre nur ein sanfter Nordwestwind gewesen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Kapitän "+pchar.lastname+"...";
				link.l1 = "Eigentlich… Ach, egal. Ich erinnere mich an dich! Du heißt Moko. Du warst doch derjenige, der ein ganzes Fass Rum auf einmal geleert hat, oder?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Was wollen Sie… Monsieur?";
				link.l1 = "So einen Hüne trifft man nicht alle Tage. Wie heißt du?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Ich... Und ich bin erst nach zwei Tagen wieder aufgewacht.";
			link.l1 = "Ein anderer an deiner Stelle hätte keine zwei Stunden überlebt. Wenn du so kämpfst, wie du trinkst – dann hat Jean verdammt viel Glück mit seinem Bootsmann.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Auch ich hatte Glück mit meinem Kapitän. Durch ihn habe ich meine Freiheit gefunden. Und durch euch. Ich würde heute noch auf den Plantagen verrotten, hättet ihr Jean nicht geholfen.";
			link.l1 = "Das war ein interessantes Abenteuer. Und ich bin froh, dass es besser ausgegangen ist, als es hätte können.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Ich bin der Bootsmann auf diesem Schiff.";
			link.l1 = "Ha-ha, ich würde zu gern denjenigen sehen, der es wagt, dir zu widersprechen. Dienst du schon lange beim Kapitän?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Einige Jahre. Ich verdanke ihm viel. Wäre er nicht gewesen, wäre ich längst verrottet auf...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Wolltest du sagen – auf der Plantage?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Lass gut sein, "+npchar.name+", du musst mir natürlich nichts erzählen, aber falls dir das noch nicht aufgefallen ist – ich gehöre nicht zu diesen Saubermännern mit Perücken. Hat der Kapitän dich freigekauft?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Wir sind gemeinsam geflohen. Von der Plantage in Maracaibo. Ohne Jean hätten wir es nie geschafft. Seitdem bin ich in seiner Mannschaft. Erst als Matrose, und jetzt – bin ich der Bootsmann.";
			link.l1 = "Der Kapitän war in der Sklaverei? Das hätte ich nie gedacht. Aber auch in meinem Schrank gibt es ein paar Leichen. Ich freue mich, dass Sie dem spanischen Stiefel entkommen sind, "+npchar.name+". Na, und wie ist es, Seemann zu sein?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Als hätte ich vorher gar nicht gelebt. Das Meer ist jetzt mein Zuhause.";
			link.l1 = "Da verstehe ich dich, mein Freund. Wie kein anderer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Kapitän "+pchar.lastname+"... Womit kann ich helfen?";
			link.l1 = "Ich danke Ihnen, "+npchar.name+", im Moment brauche ich nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Wie froh bin ich, auf diesem Schiff wenigstens ein vernünftiges Gesicht zu sehen. Diese... Matrosen... das sind Barbaren.";
			link.l1 = "An Ihrer Stelle würde ich mich auf einem fremden Schiff nicht so ausdrücken. Ich weiß nicht, wie Sie in die Karibik gekommen sind, aber hier, wissen Sie, gelten andere Regeln. Sie sollten der Mannschaft gegenüber Respekt zeigen.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Respekt? Vor denen? Das sind doch Wilde! Ich bin ein Edelmann, "+GetTitle(NPChar,true)+", ich bin Ordnung gewohnt, Service, und... Zivilisation! Sollen sie es nur wagen, mir zu widersprechen – mein Vater wird sie...";
			link.l1 = "Ihr Vater wird erfahren, dass Sie unterwegs an Fieber gestorben sind. Und er wird kaum das Gegenteil beweisen können.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Verdammt soll dieser Colonel Fox sein! Alles ist seine Schuld! Für seine Tochter habe ich den Ozean überquert, auf meinen Komfort verzichtet, diese schiefen Blicke ertragen, dieses furchtbare Essen, dieses... Schwanken! Und jetzt segle ich auch noch auf irgendeinem fremden Schiff!";
			link.l1 = "Oberst Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Sie kennen ihn, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Ähm... Ich habe von ihm gehört.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Nun, dann haben Sie nicht viel verpasst. Dieser Mann ist die Verkörperung blinden soldatischen Starrsinns und Vorurteile.";
			link.l1 = "Er ist Soldat...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Genau! Und damit ist alles gesagt. Als ich kam, um um ein Treffen mit seiner Tochter zu bitten, wissen Sie, was er getan hat? Wissen Sie? Er hat mich einfach vor die Tür gesetzt! Ohne ein einziges Wort!";
			link.l1 = "Aber Sie haben offenbar nicht aufgegeben?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Natürlich! Ich habe eine ganze Woche lang versucht, vorgelassen zu werden! Ich habe mich erniedrigt! Ich habe sogar... dem Wachmann ein Bestechungsgeld angeboten! Am Ende ist es mir gelungen, mich ohne Einladung zu ihm durchzuschleichen. Ich wollte einfach nur mit ihm reden!";
			link.l1 = "Ich glaube nicht, dass er sich darüber gefreut hat.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Hast du dich gefreut? Ach was, er hat einen richtigen Aufstand gemacht! Ich wurde rausgeworfen, durfte mich der Residenz nicht mehr nähern, das Schiff meines Vaters wurde beschlagnahmt, und schließlich wurde allen englischen Kapitänen verboten, mich an Bord zu nehmen! Da blieb mir nichts anderes übrig, als auf Martinique ein französisches Schiff zu suchen... Es war ein Albtraum.";
			link.l1 = "Es sieht so aus, als hätten Sie ihn ziemlich wütend gemacht.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Er war immer gegen mich. Sein Lieblingsspruch war: 'Tochter eines Offiziers – Frau eines Offiziers.' Sie, "+GetTitle(NPChar,true)+", hielt er für eine viel passendere Partie.";
			link.l1 = "Vielleicht hatte er diesmal auch noch andere Gründe...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Also sind Sie hierher gekommen, um Ihre Geliebte zu sehen.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Ja. Ich habe keinen einzigen Brief von ihr bekommen, seit sie Europa verlassen hat. Ich bin sicher, ihr Vater fängt einfach ihre Post ab. Sie konnte mich nicht vergessen! Natürlich war sie mir gegenüber zurückhaltend... sogar kühl... Aber ich glaube nicht, dass sie mich aus ihrem Leben gestrichen hat.";
			link.l1 = "Mein Beileid, Monsieur. Seelische Wunden heilen weitaus schwerer als körperliche. Warten Sie... Warum, Sie als Engländer, reisen Sie nach Bordeaux?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Ich habe nicht vor, mit Schande nach Hause zurückzukehren. Ich werde wohl bei meinem Onkel in Bordeaux unterkommen müssen, bis sich alles gelegt hat. Sein Anwesen ist ohnehin viel geräumiger und eleganter als unseres. Und das Personal ist auch besser ausgebildet.";
			link.l1 = "Nun gut, das ist wohl nicht die schlechteste Lösung. Vielleicht finden Sie sogar eine neue Auserwählte. Bordeaux hat wirklich viele junge Schönheiten zu bieten, das können Sie mir glauben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Wann kommen wir endlich an, "+GetTitle(NPChar,true)+"? Ich leide unerträglich inmitten all dieser... Gentlemen. Ich muss dringend ein Bad nehmen.";
			link.l1 = "Ich fürchte, in den nächsten zwei Monaten bleibt Ihnen nichts anderes übrig, als von ihr zu träumen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Verdammte Flaute, soll sie doch der Teufel holen.";
			link.l1 = "Mecker nicht, "+npchar.name+", früher oder später wird der Wind auffrischen.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "Und was sollen wir bis dahin tun, Sir? Ich kann ja nicht mal die Kanonen überprüfen... Wir sind schließlich auf einem fremden Schiff.";
			link.l1 = "Versuch einfach mal, dich auszuruhen. Man muss ja nicht immer nur arbeiten.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Verdammte Flaute...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Ein schönes Schiff, Herr Kapitän. Finden Sie das auch?";
			link.l1 = "Sogar besser als Meifeng?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Für "+npchar.name+" Es gibt kein besseres Schiff als die Meifeng. Kein anderes Schiff kann so hart am Wind segeln wie sie.";
			link.l1 = "Nur ruhig, "+npchar.name+", ich habe doch nur Spaß gemacht. Natürlich ist Meifeng konkurrenzlos. Aber auch die Ulysses ist ein gutes Schiff. Solide.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" ans Steuer treten wollen. Spüren, wie das Schiff auf die Hand hört...";
			link.l1 = "Leider, mein Freund, das ist nicht unser Schiff. Biete doch lieber diesem Kerl dort drüben ein Fechtduell an. Das wird euch beiden guttun.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "Mit welcher Geschwindigkeit könnten wir fahren, wenn der Wind günstig ist?";
			link.l1 = "Das kann ich dir wirklich nicht genau sagen, "+npchar.name+". Frag lieber ihren Steuermann.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Hast du gesehen, was für ein Riese hier als Bootsmann arbeitet? Man sagt, er kann mit einer Hand eine Kokosnuss zerdrücken.";
			link.l1 = "Ha-ha. Und du hast wohl ein bisschen Angst vor ihm, was?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Warum denn das? Die Größe ist nicht das Wichtigste. Ich habe schon mit ganz anderen fertig geworden.";
			link.l1 = "Vielleicht schlägst du ihm dann einen Faustkampf vor? Eins gegen eins – ganz fair.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Du bist ja ganz blass geworden. Ha-ha. Na gut – wenn du nicht willst, dann eben nicht. Schonen wir deine Knochen, die ja auch nicht mehr die jüngsten sind.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "In diesen Gewässern gibt es so viele Fische, dass man sie mit dem Boot schöpfen könnte, aber diese Faulpelze haben es nicht einmal geschafft, ein Netz auszuwerfen.";
			link.l1 = "Sprich mit ihrem Bootsmann. Ich denke, er wird deine Bemerkung zu schätzen wissen, hehe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "Das Gold ist in Sicherheit, Kapitän "+pchar.name+". Tichingitu soll ihn zuverlässig bewachen.";
			link.l1 = "Danke, mein Freund. Alonso wird dich bald ablösen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Beim Klabautermann, Sir, auf diesem Kahn gibt es mehr Ratten, als ich in meinem ganzen Leben je gesehen habe.";
			link.l1 = "Das Schiff lag lange im Hafen, ohne richtige Aufsicht. Die neue Mannschaft wird sie bald loswerden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway hört das Klirren der Kette. Hat der Kapitän den Anker geworfen?";
			link.l1 = "Unser Passagier hat die Sicherung durchbrennen lassen. Der Wind ist im Moment noch ganz schwach, aber ich hoffe, das bleibt nicht lange so.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Ja, verdammt noch mal... Jetzt hätte ich nichts gegen einen kräftigen Becher Rum.";
			link.l1 = "Bald gibt es Abendessen, halt noch durch. Alonso wird dich ablösen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", meine Liebe, wie fühlst du dich?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Lass gut sein, Liebling, bist du mir wirklich böse, nur weil ich kurz in den Laden gegangen bin, um Wein zu holen?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "In den Laden, um Wein zu holen? Du hättest mich wenigstens warnen können! Woher soll ich wissen, dass du nicht im Bordell warst – mit irgendeiner… oder gleich mit allen auf einmal?!";
			link.l1 = "Liebling, glaubst du wirklich, ich würde so ein Risiko eingehen? Ich habe doch die schönste, klügste und wahnsinnig eifersüchtige Frau auf dem ganzen Archipel. Warum sollte ich mich da mit irgendwelchen billigen Hafenmädchen abgeben?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Du hättest mir wenigstens ein Wort sagen können, ja, gell! Ich saß da und…";
			link.l1 = "Ich verspreche dir, das nächste Mal sage ich dir nicht nur Bescheid – ich nehme dich einfach mit. Aber jetzt… frage ich mich plötzlich, ob in der Kapitänskajüte mit den Möbeln alles in Ordnung ist. Besonders mit dem Bett. Wollen wir nachsehen?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"...   Und wenn jemand reinkommt?\nHm… jetzt reizt mich das nur noch mehr.";
			link.l1 = "Dann verlieren wir keine Sekunde.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", meine Liebe, wie fühlst du dich?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Ach komm, Liebling, bist du wirklich sauer auf mich, nur weil ich losgezogen bin, um Wein zu kaufen?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Hättest mich ruhig mitnehmen können. Oder glaubst du etwa, ich hätte mich schlechter geschlagen als deine Komplizinnen?";
			link.l1 = "Ich glaube, du würdest sie mühelos in den Schatten stellen. Aber dann hätte ich wohl gar nicht mehr an den Wein gedacht.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "Worum denn?";
			link.l1 = "Daran zu denken, mit dir gleich dort allein zu sein… Dieser Gedanke lässt mich gerade einfach nicht los.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Ach ja? Und wo willst du dich denn vor neugierigen Blicken verstecken?";
			link.l1 = "In der Kapitänskajüte. Ich denke, wir sollten sein Bett auf Stabilität prüfen.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha-ha.   Und was, wenn der Kapitän uns erwischt?\nObwohl… allein dieser Gedanke lässt mein Herz schneller schlagen.";
			link.l1 = "Dann verlieren wir keine Zeit!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "Das war wunderschön, mein Kapitän...\nIch habe eine Neuigkeit für dich.";
			link.l1 = "Neuigkeiten? Ich bin ganz Ohr.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Wir bekommen ein Kind. Ich bin schwanger, ja, gell.";
			link.l1 = "Meine Liebste... Ist das wahr?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Du wirst Vater, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... Das ist unglaublich!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Bist du glücklich, mein Liebster?";
			link.l1 = "Froh? Machst du Witze? Verdammt, ich bin der glücklichste Mensch auf der Welt! Aber... warum hast du es mir nicht früher erzählt?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Um die Abreise zu verhindern? Ich möchte deinen Vater wirklich kennenlernen, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Ich liebe dich!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Du warst wie immer großartig, Liebling. Ich habe Neuigkeiten für dich.";
			link.l1 = "Neuigkeiten? Ich bin ganz Ohr.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", Chevalier de Monpe – du wirst Vater.";
			link.l1 = "Ist das... ist das wahr?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "So wahr, wie dass ich so heiße, wie ich heiße "+npchar.name+". Nicht später als in einem halben Jahr werden wir ein Kind bekommen – einen kleinen Monsieur de Mor... oder vielleicht eine Mademoiselle.";
			link.l1 = " Hélène... Das ist unglaublich!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Deshalb hast du also nicht mit uns auf die Abfahrt angestoßen! Aber… warum hast du mir das nicht früher gesagt?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Ich hatte Angst, dass du dich entscheidest, kein Risiko einzugehen und auf dem Archipel bleibst. Ich wollte, dass du die Bitte deines Vaters erfüllst. Und... ich möchte ihn wirklich gerne selbst kennenlernen.";
			link.l1 = ""+npchar.name+"… Ich liebe dich!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Na, na… Und was machen wir denn hier? Kleine Gascogner?";
				link.l1 = "Ha-ha-ha! Ich werde einen Sohn haben, "+npchar.name+"! Ich werde Vater!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Finden Sie nicht, dass es selbst für jemanden Ihres Ranges zu weit geht, die Kapitänskajüte ohne Wissen des Kapitäns zu benutzen?";
				link.l1 = "Verzeihung, Kapitän. Aber ich habe einen guten Grund! Ich werde Vater!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Oder eine Tochter!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "Und das hast du vor mir verheimlicht, du Schuft? Dabei habe ich dich doch für meinen Freund gehalten!";
			link.l1 = "Ich habe es selbst gerade erst erfahren! Stell dir das vor! Ich! Werde! Vater!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha-ha-ha! Du bist ja wirklich glücklich, mein Freund! So habe ich dich noch nie gesehen.\nNa, ihr zwei plaudert mal schön weiter, ich mache inzwischen die Kanonen für den Festschuss bereit. Sag Bescheid, wenn du bereit bist, den Befehl zu geben.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha… Glauben Sie mir, ich hatte schon eine Ahnung, warum Sie hierher gekommen sind.";
			link.l1 = "Nein, doch nicht! "+sld.name+" Ich bin schwanger! Ich werde einen Sohn bekommen!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Oder Tochter!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Ähm... Nun, ich gratuliere Ihnen von ganzem Herzen!\nIch werde veranlassen, dass wir zu Ehren des Anlasses eine Salve aus allen Kanonen abfeuern. Geben Sie Bescheid, sobald Sie bereit sind, den Befehl zu erteilen.\nBis dahin... steht Ihnen die Kajüte zur Verfügung.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Hust, hust... Nun, Vater... Ich sehe schon, du willst gleich noch einen Erben machen, was?";
				link.l1 = "Ha-ha! Wenn es nach mir ginge, würde ich gleich ein ganzes Dutzend auf einmal machen! Na, mein Freund, wollen wir eine Salve aus allen Kanonen abfeuern?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Fürchte, mein Freund, so läuft das nicht. Aber wir haben es versucht.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "Na, Kapitän, lassen wir alle Kanonen sprechen?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Nicht jetzt.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "Die Mannschaft wartet nur darauf! Geben Sie den Befehl, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "Die Mannschaft ist bereit. Geben Sie den Befehl.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Kanoniere! Alle Geschütze, Feuer!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Wie sehr freue ich mich, dich zu sehen, mein Sohn!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Vater... Kaum zu glauben, dass ich wieder zu Hause bin... Ich hatte schon vergessen, wie Schnee aussieht. Es scheint, als hätte sich hier überhaupt nichts verändert...";
			}
			else
			{
				link.l1 = "Vater... Kaum zu glauben, dass ich wieder zu Hause bin... Es scheint, als hätte sogar der Schnee beschlossen, dieses Ereignis zu feiern. "+month+". Hier hat sich überhaupt nichts verändert...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "Das kann man von dir aber nicht behaupten! Deine Haltung, dein Gang, die Narben\n"+"Nein, vor mir steht nicht mehr der verwöhnte Junge, den ich einst in die Ferne verabschiedet habe.";
			link.l1 = "In der Karibik wird man schnell erwachsen, Vater. Aber darüber können wir später noch sprechen. Erzählen Sie lieber, wie es um Ihre Gesundheit steht. Ich hoffe, die Krankheit ist zurückgegangen, wenn Sie jetzt in voller Montur vor mir stehen?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Leider, "+pchar.name+", sie klammerte sich nur noch fester an meinen Hals. Aber konnte ich meinen geliebten Sohn etwa in alltäglicher Kleidung empfangen? Für mich ist das ein großer Tag, "+pchar.name+"\n"+"Es sieht so aus, als müsstest du mich jemandem vorstellen.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Leider, "+pchar.name+",   ihr Griff wird mit den Jahren nur stärker. Aber konnte ich meinen geliebten Sohn etwa in gewöhnlicher Kleidung empfangen? Für mich ist das ein großer Tag, "+pchar.name+"\n"+"Ich sehe, du bist nicht allein gekommen\n"+"Ihr müsst von der Reise hungrig sein? Suzanne hat Gänseleber nach deinem Lieblingsrezept zubereitet!\n"+"Bitte zu Tisch – unterwegs kannst du uns ja vorstellen!";
				link.l1 = "Ich gebe zu, ich habe diesen Duft schon gerochen, als ich mich dem Anwesen näherte!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Vater, darf ich Ihnen meine Frau vorstellen – "+sld.name+" "+pchar.lastname+". "+sld.name+", das ist mein Vater – der Chevalier "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", ich bin entzückt! Deine Auserwählte erinnert kein bisschen an die verwöhnten Damen der Gesellschaft, wie wir sie hier gewohnt sind. Ich wage zu behaupten, sie führt ein Schiff ebenso sicher wie das Herz meines Sohnes.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Es ist mir eine große Freude, Sie kennenzulernen, gnädige Frau. Ich versichere Ihnen, mein Sohn hat einen ausgezeichneten Geschmack!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Ich fühle mich geehrt, Chevalier! Sie haben recht, ich kann tatsächlich auch im schlimmsten Sturm das Steuer halten. Aber was das Herz Ihres Sohnes betrifft – es braucht keine Führung. Wir sind in unseren Zielen und Bestrebungen vereint.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "Abt Benoît hat Sie als kluge und mutige junge Frau beschrieben – und offenbar hat er nicht übertrieben. Es freut mich, dass "+pchar.name+"   ich in dir nicht nur eine Ehefrau, sondern auch eine ebenbürtige Gefährtin gefunden habe\n"+"Ihr müsst hungrig von der Reise sein? Suzanne hat Gänseleber nach deinem Lieblingsrezept zubereitet!\n"+"Nun denn, ich lade euch alle zu Tisch! Und auf dem Weg dorthin hoffe ich, dass wir uns alle ein wenig besser kennenlernen.";
			link.l1 = "Ich gebe zu, ich habe diesen Duft schon gerochen, als ich mich dem Anwesen näherte!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Es freut mich, Sie kennenzulernen, Chevalier! "+pchar.name+" viel von Ihnen erzählt, und ich habe Sie mir genau so vorgestellt, ja, gell!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", ich bin entzückt! Deine Auserwählte erinnert kein bisschen an die gepuderten Damen der feinen Gesellschaft – und gerade darin liegt ihr wahrer Wert\n"+"Ich glaube, du hast eine wunderschöne Rose gewählt, statt verwöhnter, launischer Lilien.";
			link.l1 = "Die Wilde Rose, Vater… "+sld.name+"  - ein wahrer Schatz. Ich bin sicher, Sie werden mir zustimmen, wenn Sie sie näher kennenlernen.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Dann wollen wir diesen Moment nicht länger hinauszögern! Ihr seid bestimmt hungrig von der Reise? Suzanne hat Gänseleber nach deinem Lieblingsrezept zubereitet!\n"+"Ich bitte alle zu Tisch! Und auf dem Weg hoffe ich, "+sStr+"";
			link.l1 = "Ich muss gestehen, ich habe diesen Duft schon gerochen, als ich mich dem Anwesen näherte!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Meine Liebe, das musst du unbedingt probieren – nichts kann mit Gänseleber konkurrieren, die nach unserem Familienrezept zubereitet wird! Das Rezept stammt von unserem Großvater – und er bekam es einst als Geschenk aus einem Mittelmeerland.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Ich möchte das Festmahl nicht mit Traurigkeit beginnen, aber als Familie sind wir verpflichtet, derer zu gedenken, die vor uns gegangen sind. Ich bitte euch, die Gläser zu erheben auf Michel. Möge der Herr seiner Seele Frieden schenken.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Ich habe so vieles, was ich dich fragen möchte, "+pchar.name+"... Doch zuvor lass mich deine Gemahlin anhören und "+sStr+". Bitte erzählen Sie, wie Sie Charles kennengelernt haben.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Ich habe so viele Fragen an dich, "+pchar.name+"... Doch zuvor lass mich anhören "+sStr+". Bitte erzählen Sie, wie Sie Charles kennengelernt haben.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Ich bin genauso gespannt wie Sie, das zu hören!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Ich war in tödlicher Gefahr... "+pchar.name+", wie ein wahrer Gentleman, hat er nicht zugelassen, dass mir etwas zustößt! Er hat mich verteidigt und mit den Halunken abgerechnet, ja, gell?";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" hat mich aus den Händen eines englischen Schurken gerettet, der es gewagt hatte... mich zu entführen. Wäre er auch nur eine Stunde später gekommen – wir hätten uns nie kennengelernt.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Ich habe nie daran gezweifelt, dass er so handeln würde, wie es einem wahren Edelmann gebührt. Ehre ist für unsere Familie mehr als nur ein Wort. Ich bin stolz auf dich, mein Sohn.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" in das Haus des Bleichgesichts schleichen, um Essen zu finden. Bleichgesicht überrascht werden "+sld.name+" - und ins Gefängnis stecken. Kapitän "+pchar.name+" kommen, befreien "+sld.name+" aus dem Gefängnis. Seitdem "+sld.name+" dem Kapitän dienen "+pchar.name+" und dir bis zum letzten Atemzug treu sein.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Es ist erfreulich zu wissen, dass mein Sohn nicht nur ein ehrenhafter Edelmann, sondern auch ein Mensch mit gutem Herzen ist. Es freut mich, dass er so treue Freunde wie Sie an seiner Seite hat, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Eines Tages kam der Kapitän zu mir nach Hause – auf der Suche nach Arbeit. Ich gab ihm einen Auftrag, und er erledigte ihn wie es sich gehört. Dem Chef gefiel er, und so zog er den Kapitän immer mehr in seine Angelegenheiten hinein, während er mich zu ihm aufs Schiff schickte – um ein Auge auf ihn zu haben... Und dann hat dieser... Mister sich heimlich vom Anker gelöst, Kanonenkugel noch mal, und den Archipel verlassen, ohne dem Kapitän ein Wort zu sagen. Hat ihn einfach in dem Schlamassel sitzen lassen, den er selbst angerührt hatte. Ich bot dem Kapitän meine Hilfe an, und obwohl Richard sich wirklich mies verhalten hat, Kanonenkugel noch mal, hat der Kapitän mich nicht fortgejagt.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longway und der Herr Kapitän arbeiteten für denselben Mann. Doch dieser Mann hat Longway verraten. Da beschloss Longway: Diesem Mann dient er nie wieder. Der Herr Kapitän nahm mich als Offizier auf sein Schiff, und hat sehr viel für Longway getan.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Zum ersten Mal sind wir uns in der Taverne von Bridgetown begegnet: "+pchar.name+"   Er war auf der Suche nach einer Aufgabe, und ich – nach einem zuverlässigen Helfer. Dieses Kennenlernen war nur der Anfang – darauf folgten Ereignisse, die unsere Wege untrennbar verbanden. Ich wurde sein Offizier, und heute kann ich ihn ohne Zögern meinen Freund nennen – einen Menschen, für den ich mein Leben riskieren würde.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Den Menschen hinter den Umständen zu erkennen, ist eine seltene Gabe. Das spricht wohl dafür, dass mein Sohn nicht ohne Verstand ist.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Ich bin froh, dass mein Sohn kein gefühlloser Soldat ist, sondern ein wahrer Anführer, der sich um seine Gefährten kümmern kann.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "So etwas hört man nicht alle Tage. Das ist wohl der beste Beweis dafür, dass mein Sohn nicht nur ein geschickter Seemann, sondern auch ein guter Freund ist.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Wir haben uns in Bordeaux kennengelernt. Der Käpt'n ist als Passagier auf unser Schiff gekommen, und wir haben ihn nach Martinique gebracht. Seitdem – und bis zu unserer Abreise hierher – war ich die Stimme seiner Mannschaft und habe beobachtet, wie "+GetFullName(pchar)+" Schritt für Schritt wurde er zu dem, der er heute ist.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Sie kennen Charles also noch als den unausstehlichen Jungen, der auf mein Drängen hin das Elternhaus verlassen hat? Ich denke, Monsieur, wir werden einiges zu besprechen haben.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Mein Lieber "+pchar.name+", du hast einen langen und ehrenvollen Weg hinter dir... Du bist nur wegen eines Kaninchenfells in die wilde Savanne gezogen, doch hast dich mit einem Löwen gemessen und bist siegreich zurückgekehrt, seine Haut auf deinen Schultern. Jetzt bin ich so ruhig um das Schicksal unseres Anwesens und all unserer Ländereien wie nie zuvor.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Ich kann es kaum erwarten, dir so bald wie möglich die Zügel aller Angelegenheiten unserer Familie zu übergeben. Es wird viel Arbeit auf dich zukommen, aber ich glaube fest daran – der Herr selbst blickt mit Wohlwollen auf dich, und du wirst nicht nur das dir anvertraute Erbe bewahren, sondern auch die Ehre und den Wohlstand der Familie de Monpe mehren.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Es ist mir eine große Ehre, Ihr Sohn und Erbe zu sein. Mit Freude übernehme ich alle Sorgen um unsere Familie. Ich bin sicher, dass meine Ehefrau mir dabei eine treue Stütze sein wird. Ich verspreche, alles in meiner Macht Stehende zu tun, um unseren Namen noch mehr zu ehren... Und der erste Beitrag zu seinem Wohlstand wird die Geburt eines Kindes sein!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "Es ist mir eine große Ehre, Ihr Sohn und Erbe zu sein. Mit Freude übernehme ich alle Sorgen um unsere Familie und verspreche, alles in meiner Macht Stehende zu tun, um unseren Namen noch mehr zu ehren.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Vater, die Jahre in der Neuen Welt haben mich verändert. Ich fürchte, ich kann mich nicht mehr mit dem ruhigen Lebensrhythmus hier in Europa abfinden.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", wirklich...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Ja, Vater. "+sld.name+" Ich bin schwanger.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "Das sind wahrlich großartige Neuigkeiten, mein lieber Sohn! Der Herr hat meine Gebete erhört! Mögen alle Anwesenden hier Zeugen sein: Zu Ehren des Neugeborenen werde ich den prächtigsten Ball ausrichten, den unser Anwesen je gesehen hat! Lasst uns die Gläser erheben – auf den Erben!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Oder eine Erbin!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "Auf ein neues Kapitel in der Geschichte unserer Familie!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "Auf den zukünftigen Krieger oder die gute Tochter!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Auf das Wohl des Neugeborenen!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Auf das Schicksal, das euch zusammengeführt hat!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Auf eine strahlende Zukunft für eure Familie!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Auf den zukünftigen Alonso de Mor oder die kleine Alonsita de Mor!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-hah-hah!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha-ha-ha!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Es ist mir eine große Ehre, Ihr Sohn und Erbe zu sein. Mit Freude werde ich alle Sorgen unserer Familie auf mich nehmen und verspreche, alles in meiner Macht Stehende zu tun, um unseren Namen noch weiter zu ehren.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Sag mal, "+pchar.name+", hast du über meinen Vorschlag nachgedacht, dich mit Yvonne in den Stand der Ehe zu begeben?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Ich gebe es zu, Vater... Yvonne war meinem Herzen nie wirklich nah. Aber in der Neuen Welt gibt es viele wundervolle Frauen. Ich verspreche Ihnen – wenn ich einer würdigen begegne, werde ich nicht zögern.";
			}
			else
			{
				link.l1 = "Ich gebe es zu, Vater... Yvonne war meinem Herzen nie wirklich nah. Aber in Frankreich gibt es viele wunderbare junge Frauen. Ich verspreche Ihnen – wenn ich einer würdigen begegne, werde ich nicht zögern.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Deine Einstellung gefällt mir, mein lieber Sohn. Lasst uns die Gläser erheben – auf dich, auf deine Taten und auf deine ehrenvolle Heimkehr!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Auf treue Freunde, ohne die man in der Neuen Welt nicht überleben kann!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Auf das große Herz von Kapitän Charles!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Auf den eisernen Willen des Kapitäns!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Auf die Weisheit unseres Kapitäns!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Für die Treue zur Sache!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "Auf die Fähigkeit, immer mit heiler Haut davonzukommen!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Ich habe gehört, Sie haben sehr beharrlich um eine Audienz gebeten. Also, was führt Sie zum Gouverneur von Martinique?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Ich möchte über die Arbeit zum Wohle der französischen Krone sprechen.";
			link.l1 = "Ja, ich habe einen Auftrag für Sie, bei dem Sie sowohl Schnelligkeit als auch Geschick im Seekampf brauchen werden. Sind Sie bereit, sich zu beweisen?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Eure Hoheit, könntet Ihr bitte etwas genauer erklären, worum es bei dem bevorstehenden Auftrag geht?";
			link.l1 = "Natürlich. Sie müssen das spanische Kurierschiff namens 'Santa Esperanza' aufspüren, entern und mir die Papiere bringen, die Sie in der Kapitänskajüte finden. Das von mir genannte Schiff wird in etwa zwölf Tagen an Trinidad vorbeikommen.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "In Ordnung, ich übernehme diesen Auftrag. Und nach welchen Papieren soll ich suchen?";
			link.l1 = "Die Postsendung. Darin befinden sich unter anderem sehr wichtige Dokumente für mich. Sie müssen die Unterlagen nicht durchsehen, bringen Sie mir einfach das gesamte Paket unversehrt. Für diesen Dienst zahle ich Ihnen fünfzehntausend Pesos... Also, ich erwarte Sie mit dem Ergebnis Ihrer Arbeit in meiner Residenz.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Ich nehme an, ich werde Euch nicht lange warten lassen, Eure Hoheit.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Eure Hoheit... Erlauben Sie mir, Bericht zu erstatten?";
			link.l1 = "Berichten Sie, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Ähm-ähm...";
			link.l1 = "Sprechen Sie ruhig. Ich habe keine Geheimnisse vor meiner Frau.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "Die Aufklärung meldet: Eine Eskadre ist aus Willemstad ausgelaufen. Angeführt wird sie vom Linienschiff zweiten Ranges ‚Gouden Leeuw‘, einem wahren Ungeheuer der Meere. Die gesamte Feuerkraft der Eskadre umfasst über zweihundertfünfzig Kanonen und mehr als anderthalbtausend Soldaten. Ihr Ziel ist Saint-Pierre.";
			link.l1 = "Hm... Das heißt, wir haben so gut wie keine Zeit zur Vorbereitung.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Wie sollen wir vorgehen, Herr Gouverneur?";
			link.l1 = "Vor Anker liegen bei uns mehrere Schiffe, die dem Feind in den Rücken fallen könnten...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Wollen Sie sie von zwei Seiten angreifen?";
			link.l1 = "Genau. Die Festung wird das Feuer auf sich ziehen. Und wenn die Nacht hereinbricht, wird das Geschwader unter meinem Kommando vom Meer aus angreifen. Wir werden ihre Aufmerksamkeit zerstreuen, und dann werden von Hafen aus Brander voller Pech und Bretter losgeschickt. Von ihrer Flotte bleibt dann nicht einmal ein Splitter übrig.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Ausgezeichneter Plan, Eure Hoheit! Darf ich den Befehl zur Vorbereitung geben?";
			link.l1 = "Legt los. Und der Herr sei mit uns.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Wache, holt Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Herr Gouverneur...";
				link.l1 = ""+npchar.name+", eine holländische Staffel wird in den nächsten Tagen hier eintreffen und mit der Belagerung beginnen. Hör zu: Nimm Philipp und "+sld.name+", und bring sie sofort zum Abt. Er soll alle Frauen, Kinder und Alten versammeln und für ihre Sicherheit sorgen.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Herr Gouverneur...";
			link.l1 = ""+npchar.name+", eine holländische Staffel wird in den nächsten Tagen hier eintreffen und die Stadt belagern. Richte dem Abt aus, er soll alle Frauen, Kinder und Alten versammeln und für ihre Sicherheit sorgen. Was dich betrifft, so habe ich vor, dir das Kommando über einen Brander zu übertragen. Näheres später. Zuerst müssen wir die Zivilbevölkerung schützen.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Ich glaube nicht, dass "+sld.name+" wird sich den anderen Frauen anschließen. Sie langweilt sich zu Tode.";
			link.l1 = "Hm... Dann richte ihr aus: Sie soll sich auf einen Kampf vorbereiten. Auch du wirst nicht untätig bleiben – du wirst das Brander-Kommando übernehmen. Näheres später. Jetzt kümmere dich um meinen Sohn.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Es wäre mir eine Ehre! Darf ich mich an die Arbeit machen?";
			link.l1 = "Ich erlaube es. Tu, was du musst. Jede Sekunde zählt für uns.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Nun... Ich gebe zu, ich habe erwartet, dass du das sagen würdest – und doch hatte ich auf eine andere Antwort gehofft. Aber ich respektiere deine Entscheidung und werde dich nicht weiter bedrängen.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Ich verstehe, dass ich Sie enttäuscht habe. Aber ich habe eine Nachricht für Sie, die – so hoffe ich – alles bisher Gesagte in den Schatten stellt.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Ich höre dir ganz zu.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Ich habe vor, mindestens ein Jahr hierzubleiben. "+sld.name+" in ihrem Zustand ist Seegang absolut nicht zu empfehlen.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", wirklich...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Nun... Ich gebe zu, ich habe erwartet, dass du das sagen würdest – und doch hatte ich auf eine andere Antwort gehofft. Aber ich respektiere deine Entscheidung und werde dich nicht weiter bedrängen. Doch sag mir, "+pchar.name+", hast du über meinen Vorschlag nachgedacht, dich mit Yvonne zu vermählen?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Konnte nicht widerstehen, was?";
			link.l1 = "Du?! Ist das ein Traum?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "Die Gier nach schnellem Gewinn, Macht, die Illusion der Unverwundbarkeit… Was davon hat dich zugrunde gerichtet, Bruder? Was hat deinen Verstand getrübt, so wie es die Köpfe aller Bleichgesichter vernebelt?";
			link.l1 = "Verschwinde! Du bist nur ein Geist! Du bist gar nicht hier!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Hast du es immer noch nicht begriffen? Spectra sunt memoria peccatorum. Du bist der Geist... Die Legende der Karibik erzählt von einem Mann, den Gier und blinder Hochmut verschlungen haben. Wie viele hast du für Gold getötet, "+pchar.name+"?";
			link.l1 = "Nun gut, mein lieber Bruder, ich habe nichts dagegen, dich ein zweites Mal umzubringen! Du hast es ja selbst herausgefordert!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}