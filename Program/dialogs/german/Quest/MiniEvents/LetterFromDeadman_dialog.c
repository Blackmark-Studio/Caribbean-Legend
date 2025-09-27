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
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Was willst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "Was willst du, "+GetSexPhrase("Kamerad","lass")+"? Wenn du mir etwas Rum anbietest, sage ich nicht nein. Ich bin schon so viele Runden durch diese gottverlassene Stadt gelaufen, dass sich meine Beine gleich verknoten. Und wie heißt du?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Du bist nicht von der 'Eagle', oder?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Und ich - "+GetFullName(npchar)+". Und ja, ich bin von der 'Eagle'. Gefällt Ihnen unser Schiff, Kapitän?";
			}
			else
			{
				dialog.text = "Kapitän? Nun, nun... Ähem... Ich bin Antonio Velenta. Und ja, ich bin von der 'Eagle'. Hat unser Schiff Euer Interesse geweckt, Kapitän?";
			}
			link.l1 = "Ein Schiff ist ein Schiff. Du solltest dich besser beeilen und an Bord gehen, statt hier in der Stadt herumzulaufen – dein Kapitän schäumt schon vor Wut. Er will noch vor dem Auslaufen der Flut den Hafen verlassen, und irgendetwas sagt mir, Junge, dass er nicht auf dich warten wird.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Verdammt noch mal... Ich weiß, ich weiß... Aber ich habe hier in dieser Stadt noch ein paar offene Rechnungen. Wie wär's, willst du ein paar Dublonen verdienen, Captain?";
			link.l1 = "Dublonen sind immer willkommen. Aber sie zu verdienen ist das eine, sich Ärger einzuhandeln das andere. Was ist der Auftrag? Raus damit.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Siehst du, als ich den Laderaum entlud, bin ich über einen Brief gestolpert. Es sah nicht so aus, als wäre er absichtlich versteckt worden, er lag einfach zwischen ein paar alten Fässern. Unser Fluyt hat schon mehr als eine Enterung erlebt, also kann man nicht sagen, woher er stammt.";
			link.l1 = "Also hast du den Brief gefunden, aber was soll das schon heißen?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Es ist an eine gewisse Marisa Caldera aus Porto Bello adressiert. Mit Wachs versiegelt... Ich spüre es im Bauch – das ist keine belanglose Angelegenheit. Vielleicht ist es von einem Kapitän, vielleicht von einem Kaufmann... aber ganz sicher nicht von einem gewöhnlichen Matrosen wie mir! Nur werde ich keine Zeit haben, die Empfängerin zu finden – unser Kapitän versteht wirklich keinen Spaß.  Willst du es mir nicht abkaufen? Für tausend Pesos überlasse ich es dir. Du bist ein Kapitän, für dich wird es nicht schwer sein, diese Señorita ausfindig zu machen. Und wer weiß, vielleicht belohnt sie dich mit Gold oder etwas anderem... du verstehst schon, was ich meine?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Na gut, vielleicht finde ich deine Marisa.  Wie auch immer, ich habe nichts zu verlieren. Außer tausend Pesos. Gib mir den Brief.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Nicht genug Geld (1000)", "Money");
			}
			link.l2 = "Sorry, aber du musst dir jemand anderen suchen. Ich habe Wichtigeres zu tun, als Briefe auszutragen.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Hier, bitte. Pass auf dich auf, "+GetSexPhrase("Kamerad","lass")+", ich sollte gehen – ich möchte nicht, dass meine Sachen mit der 'Eagle' davonsegeln.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "Wer bist du? Was willst du?";
			link.l1 = "Mein Name ist Kapitän "+GetFullName(pchar)+". Ich suche Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Ich kenne keine Marisa. Sie sind an der falschen Tür. Gehen Sie jetzt, bevor ich die Wachen rufe – die werfen Sie sofort raus.";
			link.l1 = "Vater "+sld.name+" hat mir erzählt, dass du ihre Freundin bist. Ich habe einen Brief, der an sie adressiert ist. Dem Aussehen nach ist er schon sehr alt. Ich möchte ihn ihr persönlich übergeben.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ach, Vater... Er ist zu allen zu freundlich, aber er irrt sich selten in den Menschen. Du kannst mir den Brief geben. Ich sorge dafür, dass er sie erreicht.";
			link.l1 = "Verzeihen Sie, Señorita, aber ich würde es lieber persönlich übergeben. Sie könnte Fragen haben, wie ich daran gekommen bin und warum es so lange gedauert hat, bis es angekommen ist.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "Und du erwartest, dass ich einfach an deine guten Absichten glaube? Ich habe schon viele Halunken mit tugendhaftem Gesicht gesehen. Lass den Brief hier oder geh deines Weges.";
			link.l1 = "Ich gebe Ihnen mein Wort als Kapitän, dass ich weder Ihnen noch Marisa etwas antun werde. Außerdem dürfen Sie zur Sicherheit den Wachmann oder jeden anderen, der mit einer Waffe umgehen kann, zu unserem Treffen einladen. Ich habe keinen anderen Zweck, als Marisa diesen Brief persönlich zu übergeben.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "In Ordnung. Komm morgen nach elf Uhr abends vorbei. Ich kann nicht versprechen, dass sie einem Treffen zustimmt, aber ich werde ihr alles ausrichten, was du gesagt hast.";
			link.l1 = "Ich bin dabei. Bis bald.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Hallo, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Du hast nach mir gesucht, und hier bin ich. Dolores meinte, du hast einen Brief für mich?";
			link.l1 = "Guten Tag, Frau Caldera. Genau, hier sind Sie. Leider hat es wohl ziemlich lange gedauert, bis Sie erreicht wurden.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Übergeben: Brief an Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Das ist seine Handschrift... Ramiros Handschrift!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Aber wie ist das möglich? Es sind zwei Jahre vergangen!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Kapitän... Wie sind Sie daran gekommen? Wo haben Sie es gefunden? Ich muss alles wissen! Bitte, erzählen Sie mir alles, was Sie wissen.";
			link.l1 = "Dieser Brief kam von einem Seemann zu mir. Er fand ihn in einer dunklen Ecke des Laderaums seines Schiffs und wollte ihn dir selbst übergeben, musste aber eilig zu seinem Schiff zurückkehren. Also bat er mich, dich zu suchen, und hier bin ich. Mehr weiß ich nicht...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Danke, "+GetAddress_Form(NPChar)+"! Vielen, vielen Dank! Bitte, geh nicht. Ich möchte noch weiter mit dir reden, aber zuerst... muss ich diesen Brief lesen.";
			link.l1 = "Natürlich, Lady Caldera. Ich werde hier sein.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Zwanzig Minuten vergingen, Marisa las den Brief...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Er hat diesen Brief vor seiner letzten Reise geschrieben. Er wollte mir sagen, dass er die Gelegenheit hatte, eine große Ladung Ebenholz von einem Händler in Belize zu kaufen, aber ihm fehlte das Geld. Deshalb hat er dieses Darlehen aufgenommen... Zweihundert Dublonen... Wegen denen ich jetzt keinen Frieden mehr finde.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Das erklärt alles... Aber leider wird es deine Last nicht leichter machen. Bleib stark, Marisa. Die Dunkelheit ist nicht ewig, und diese Schuld wird dich nicht für immer verfolgen.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Nein, Dolores, das wird es nicht geben! Ramiro hat geschrieben, dass er ein Versteck hat... an unserem Ort. Wenn es noch unberührt ist, kann ich vielleicht die Schulden begleichen und diesem Albtraum endlich entkommen.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Der Herr hat dir Gnade erwiesen! Er hat unsere Gebete erhört...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Kapitän, noch einmal danke ich Ihnen, dass Sie mir diesen Brief gebracht haben. Er bedeutet mir alles... Aber ich muss Sie um noch einen Gefallen bitten. Sehen Sie, mein Mann Ramiro war alles für mich, und ich habe nie den Schutz eines anderen Mannes gesucht. Jetzt, da er fort ist, habe ich niemanden mehr, an den ich mich wenden kann, keine eigene Familie\nIch muss zu seinem Versteck gelangen – es liegt außerhalb der Stadt. Aber ich habe zu große Angst, allein zu gehen, die Gläubiger meines verstorbenen Mannes sind hinter mir her. Sie haben ehrenhaft gehandelt, als Sie mich aufgesucht und mir den Brief überbracht haben... Bitte, helfen Sie mir noch einmal.";
			link.l1 = "Natürlich, Marisa, ich begleite dich. Wann möchtest du aufbrechen?";
			link.l1.go = "Marisa_16";
			link.l2 = "Es tut mir leid, Señora, aber mein Aufenthalt in Ihrer Stadt hat sich schon zu sehr in die Länge gezogen. Spaziergänge auf dem Land gehören nicht zu meinen Plänen.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Ich verstehe... Sie haben schon mehr für mich getan, als ich je zu hoffen wagte. Danke, Kapitän, und leben Sie wohl.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Danke, Captain. Kommen Sie morgen bei Tagesanbruch, bis sieben Uhr. Ich werde bereit sein.";
			link.l1 = "Dann bis zu unserem nächsten Treffen, Señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, da sind Sie ja... Sie sind wirklich ein Mann von Ehre! Auf geht’s. Unser Weg führt durch den Dschungel zur Grotte, nicht weit von der Mosquitos-Bucht.";
				}
				else
				{
					dialog.text = "Kapitänin, da sind Sie ja... Ich wusste, dass Sie kommen würden. Wissen Sie, das ist das erste Mal, dass ich einer Frau begegne, die ihr eigenes Schiff befehligt. Und ich sehe schon jetzt, dass Sie jedem Mann ebenbürtig sind – an Ehre wie an Edelmut!";
				}
				link.l1 = "Ausgezeichnet, Señora. Dann verlieren wir keine Zeit. Bleiben Sie dicht bei mir und entfernen Sie sich keinen Moment.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Danke, Marisa. Mein Vater war ein Kapitän und ein ehrenhafter Mann – und von klein auf hat er mir dieselben Ideale vermittelt.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Komm im Morgengrauen, bis sieben Uhr. Ich bin bereit.";
				link.l1 = "Bis dann, Señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "War er das? Hat ihn dasselbe Schicksal ereilt wie meinen Ramiro?";
			link.l1 = "Er hätte sicher lieber mit dem Schwert in der Hand oder mitten im Sturm sein Ende gefunden. Doch das Schicksal hatte andere Pläne – eine Krankheit, von der er nie jemandem erzählt hatte, hat ihn dahingerafft.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Es tut mir leid wegen deines Verlusts, "+pchar.name+" Der Herr nimmt die Besten unter uns... Und auch wenn wir nicht immer verstehen, warum, so ist es doch Sein Wille. Alles, was wir tun können, ist für die Ruhe ihrer unsterblichen Seelen zu beten.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Lass uns aufbrechen. Unser Weg führt durch den Dschungel zur Grotte, nicht weit von der Mosquitos-Bucht.";
			link.l1 = "Natürlich. Bleib in meiner Nähe und geh keinen Moment weg.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Hier sind wir... Ramiro und ich haben uns früher einmal hier vor dem Regen untergestellt, damals, als wir noch jung waren, bevor er mein Mann wurde. Damals hat er mir gesagt, dass er mein Herz gewinnen würde, egal was es kostet.";
			link.l1 = "Es tut mir leid, dass Sie allein hierherkommen mussten, ohne Ihren Mann, Señora. Orte wie dieser bergen viele Erinnerungen. Schauen wir uns um – vielleicht finden wir neben Erinnerungen auch das, was Ramiro für die schwersten Zeiten aufbewahrt hat.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... Hast du etwas gefunden? Ist es das, was Ramiro hinterlassen hat? Ich weiß nicht einmal, was mir mehr Angst macht – dass es leer ist oder dass es nicht reicht, um die Schulden zu begleichen...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(zeigt) Hier, das ist alles, was in der Truhe war. Ich hoffe, es reicht, um dein Schicksal zum Besseren zu wenden.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Ich schaue immer noch in die Truhe.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ah, Kapitän! Natürlich! Das sollte reichen! Aber ich kann deine Hilfe nicht unvergütet lassen. Nimm hundert Dublonen. Ohne dich hätte ich nie von diesem Versteck erfahren und würde mich immer noch vor den Männern verstecken, die Ramiro's Gläubiger geschickt hat...";
			link.l1 = "Sie sind sehr großzügig, Señora, danke. In unserem Gewerbe ist Gold niemals vergeudet.";
			link.l1.go = "Marisa_34";
			link.l2 = "Nein, Señora. Sie brauchen dieses Geld viel dringender als ich. Wichtig ist, dass Sie jetzt Ihre Sorgen hinter sich lassen und in Frieden leben können. Das ist mehr als genug für mich.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Übergeben: Amulett 'Cimaruta'", "None");
			notification("Übergeben: Amulett 'Fischer'", "None");
			notification("Übergeben: Luntenschloss Muskete", "None");
			notification("Übergeben: Diamant (10)", "None");
			notification("Übergeben: Rubin (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Na dann, "+GetSexPhrase("Señor",""+pchar.name+"")+", wir sollten weitergehen. Falls man mich in der Stadt gesehen hat, könnte uns jemand folgen. Wir sollten besser nicht hierbleiben.";
			link.l1 = "Du hast recht, Marisa. Lass uns gehen.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Kapitän, bitte... mein Mann hat diese Waffe aufbewahrt, um unsere Familie zu beschützen, und ich bin sicher – in Ihren Händen wird sie einer gerechten Sache dienen. Ramiro wäre froh zu wissen, dass sie an den Menschen gegangen ist, der mich gerettet hat, als alle Hoffnung verloren war.";
			link.l1 = "In Ordnung, Marisa, danke dir. Du bist eine gütige und ehrenhafte Frau, und ich bedaure wirklich, dass das Schicksal so grausam zu dir war.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Manchmal schickt der Herr uns schwere Tage, oder sogar Jahre, um unseren Glauben zu prüfen, aber er verlässt niemals jene, die den rechten Weg gehen. Er hat dich zu mir geschickt, um mir zu helfen, und nun hoffe ich, dass mein größtes Problem bald hinter mir liegt.\nAber jetzt ist es Zeit, zurückzugehen. Wir sind lange genug hier geblieben, und es könnte gefährlich werden, da sie immer noch nach mir suchen.";
			link.l1 = "Natürlich, Señora, gehen wir.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ha! Da ist also unser Vermisster! Hast du wirklich geglaubt, du könntest dich hier in diesem Loch wie eine Maus verstecken und ich würde dich nicht finden? Ich habe die ganze Stadt mehr als einmal auf den Kopf gestellt, und da bist du die ganze Zeit gewesen"+GetSexPhrase(", und obendrein bist du auch noch mit irgendeinem Bengel ausgegangen. Wo ist mein Geld, du kleine Hure? Gib es besser sofort her, sonst wird diese Höhle zu deinem Grab.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Du...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Also bist du derjenige, der seinen Lebensunterhalt damit verdient, Frauen wegen Schulden zu drangsalieren? Nach deiner Berufswahl zu urteilen, war Grips wohl nie deine Stärke. Es ist ein Wunder, dass du überhaupt allein hierher gefunden hast, statt einfach jemand Klügerem hinterherzulaufen... zum Beispiel deinem eigenen Stiefel.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Halt den Mund, Held. Deine Zeit kommt noch, aber zuerst kümmere ich mich um sie. Sie schuldet fünfhundertfünfundzwanzig Dublonen – das ist ihre Schuld samt Zinsen. Entweder sie zahlt alles, oder sie bleibt für immer hier – als Futter für die Würmer. Aber wenn du schon so gerecht bist, kannst du für sie zahlen, und ich bin weg.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Du glaubst wohl, du kannst einfach hier reinspazieren, eine Dame beleidigen, mich ignorieren und dann auch noch unversehrt mit den Dublonen verschwinden? Scheint, als wärst du nicht besonders schlau. Aber ich fange keinen Streit vor einer Frau an. Also hier mein Angebot: Du entschuldigst dich bei Madam Caldera, nimmst deine Dublonen und verschwindest hier. Oder ich bringe dir doch noch ein paar Manieren bei.";
					link.l1.go = "Naemnik_5";
					notification("Überprüfung bestanden (525)", "Dubloon");
				}
				else
				{
					notification("Nicht genug Gold (525)", "Dubloon");
				}
			}
			else
			{
				dialog.text = "Halt den Mund und warte, bis du dran bist. Mit dir befasse ich mich später, wenn ich mit diesem Elend hier fertig bin. Sie schuldet fünfhundertfünfundzwanzig Dublonen – das ist ihre Schuld samt Zinsen. Wenn du so gerecht bist, kannst du für sie zahlen, und ich bin weg.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Also gut, ich bin bereit, dir deine groben Manieren und sogar deine Unhöflichkeit mir gegenüber zu verzeihen. Aber wenn du deine Dublonen bekommen und hier unversehrt verschwinden willst, musst du dich bei Lady Caldera entschuldigen. Andernfalls werden wir sehen, wer besser mit der Waffe umgeht. Und glaub mir, ich trage meine nicht nur zum Schein.";
					link.l1.go = "Naemnik_5";
					notification("Überprüfung bestanden (525)", "Dubloon");
				}
				else
				{
					notification("Nicht genug Gold (525)", "Dubloon");
				}
			}
			link.l2 = "Offensichtlich bist du nicht gerade mit viel Verstand gesegnet, wenn du dachtest, ich würde brav abwarten. Und noch weniger, wenn du glaubst, ich würde all das Unheil, das du und deinesgleichen über Lady Caldera gebracht habt, einfach ignorieren.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Na schön, wie du willst. Wenn wir das Geld ohne unnötiges Risiko bekommen können, sehe ich keinen Grund, meinen Kopf hinzuhalten. Gib die Dublonen her – und verschwinde.";
			link.l1 = "Zuerst entschuldige dich bei der Dame.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Verzeihen Sie mir, Señora. Der Teufel hat das Beste aus mir herausgeholt.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Glücklich"+GetSexPhrase("","")+"? Gib das Gold her und ich bin weg. Ich habe genug zu tun, keine Zeit, hier mit dir Höflichkeiten auszutauschen.";
			link.l1 = "Nimm deine Dublonen und verschwinde hier.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Kapitän, wirklich, ich verstehe nicht... Was soll das bedeuten?";
			link.l1 = "Das heißt, du schuldest jetzt nichts mehr. Du bist frei.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Aber... ich habe den vollen Betrag im Moment nicht, um es dir zurückzuzahlen. Wenn du noch ein wenig warten könntest...";
			link.l1 = "Du verstehst das nicht, Marisa. Du schuldest mir nichts. Du schuldest niemandem mehr etwas. Und das Geld, das du gefunden hast, wird dir sehr nützlich sein. Geh zurück in dein altes Leben – die Kirche wartet auf dich.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Ich... Ich kann es einfach nicht fassen. So etwas passiert doch nicht, "+GetSexPhrase("caballero","Señorita")+"! Du hast ein Vermögen für mich bezahlt... einfach so? Und jetzt ist alles vorbei? Keine Schulden, keine Verfolgung? Sag, stimmt das?";
			link.l1 = "Es stimmt, Señora. Es ist vorbei. Sie schulden niemandem mehr etwas.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Oh, Kapitän, Sie sind so edel! Ich habe das Gefühl, als wären Sie von Gott gesandt! Aber ich weiß gar nicht, wie ich Ihnen danken soll. Sie haben... mein Leben völlig verändert, und ich... was könnte ich nur für Sie tun?";
			link.l1 = "Du musst nichts tun, Marisa. Leb einfach. Ohne Angst, ohne die Fesseln der Vergangenheit. Geh zurück in dein altes Leben und finde dort dein Glück – das wird der beste Dank für mich sein. Komm, ich bringe dich in die Stadt.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Was hast du getan, Captain, du hast ihn getötet!";
			link.l1 = "Das stimmt, Señora. Ich musste Sie und Ihre Ehre beschützen...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Oh, Kapitän, das Nehmen eines Lebens, selbst eines wie seines, ist eine schreckliche und schwere Sünde! Du wirst Tag und Nacht beten müssen, um auch nur einen Teil davon von deiner unsterblichen Seele abzuwaschen. Gott ist mein Zeuge, ich hätte ihm einfach alles geben können, was ich hatte, und er wäre gegangen... Aber jetzt... jetzt klebt sein Blut an deinen Händen, und nur der Himmel wird entscheiden, ob dir vergeben wird!";
			link.l1 = "Vielleicht war es der Wille des Herrn. Aber lass uns nicht darüber nachdenken. Lass uns lieber aus dieser Höhle verschwinden.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Kapitän, erlauben Sie mir, Ihnen noch einmal zu danken! Ich werde für Ihre Gesundheit und Ihr Wohlergehen beten, "+pchar.name+". Bitte, kommen Sie in unsere Kirche – möge der Herr Ihnen Vergebung für all Ihre Sünden und seinen Segen gewähren.";
			link.l1 = "Vielleicht schaue ich irgendwann mal vorbei. Und denk daran, Marisa, wenn ich dein fröhliches Gesicht dort nicht sehe, bin ich sehr enttäuscht.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Du bist so gut zu mir. Ich freue mich wirklich darauf, dich wieder in unserer Stadt zu sehen. Aber jetzt verzeih mir, ich kann es kaum erwarten, mein Leben in Ordnung zu bringen und Dolores die frohe Nachricht zu erzählen.";
			link.l1 = "Natürlich, Marisa. Auf Wiedersehen. Pass auf dich auf.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Kapitän, erlauben Sie mir noch einmal, Ihnen meinen unendlichen Dank auszusprechen! Sie haben für mich das Unmögliche vollbracht! Für Ihre Güte und Ihren Edelmut möchte ich Ihnen erzählen, wie es mir gelungen ist, den Söldnern in den letzten zwei Jahren zu entkommen. Vielleicht wird dieses Wissen eines Tages auch Ihnen von Nutzen sein.";
			link.l1 = "Vielen Dank, Señora. In solchen Angelegenheiten ist Wissen so viel wert wie Gold. Ich höre zu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "So habe ich diese zwei Jahre verbracht. In einer Welt, in der Stärke so viel bedeutet, eröffnet das Wissen, wie man im Schatten bleibt, Möglichkeiten, von denen andere nur träumen können.";
			link.l1 = "Vielen Dank, dass du deine Geschichte erzählt hast, Marisa. Du hast viel durchgemacht, und deine Erfahrung ist wirklich von unschätzbarem Wert.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Ich würde mich wirklich freuen, Sie wieder in unserer Stadt zu sehen. Kommen Sie doch in unsere Kirche—möge der Herr Ihnen Vergebung für all Ihre Sünden schenken und Sie mit seinem Segen begleiten.";
			link.l1 = "Vielleicht schaue ich irgendwann mal vorbei. Und denk daran, Marisa, wenn ich dein fröhliches Gesicht dort nicht sehe, bin ich sehr enttäuscht.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ach, Kapitän... Sie sind so gut zu mir. Aber jetzt, verzeihen Sie, ich kann es kaum erwarten, mein Leben zu ordnen und Dolores die frohe Nachricht zu überbringen.";
			link.l1 = "Natürlich, Marisa. Auf Wiedersehen. Pass auf dich auf.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Habt ihr gehört? Kapitän "+GetFullName(pchar)+" hat aus eigener Tasche die Schulden der Witwe Calder beglichen! Nur wenige wären bereit, so viel für einen Fremden zu opfern. Es gibt sie noch, die wahren Caballeros in Spanien!", "Es ist herzerwärmend zu sehen, dass es in Spanien nicht nur ehrenhafte Caballeros gibt, sondern auch Frauen, deren Mut und Ehre denen der Männer in nichts nachstehen.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Man sagt, ein Kapitän habe sein eigenes Geld gegeben, um die Witwe Calder von den Schulden ihres verstorbenen Mannes zu befreien! Nicht jeder würde so edelmütig handeln. Ein wahrer Ehrenmann, nicht wahr?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitän, es ist so eine Freude, Sie wiederzusehen! Ich hatte gehofft, dass Sie vorbeikommen. Vielleicht haben Sie heute Zeit, ein wenig zu bleiben und zu beten?";
						link.l1 = "Froh"+GetSexPhrase("","")+" Treffen, Marisa. Aber ich fürchte, ich kann es mir im Moment nicht leisten, zu verweilen. Ich erinnere mich an meine Pflicht gegenüber dem Herrn, aber das Gebet muss warten.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Kapitän, Sie schon wieder! Immer eine Freude. Es scheint, der Herr lässt Sie den Weg zur Kirche nicht vergessen... Vielleicht finden Sie ja doch noch einen Moment zum Gebet?";
						link.l1 = "Marisa, es ist gut, dich zu sehen. Aber ich kann nicht bleiben – meine Angelegenheiten dulden keinen Aufschub. Ich glaube, der Herr kennt meine Gedanken auch ohne Gebet.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Kapitän, welch eine Freude, Sie wiederzusehen! Jeden Tag danke ich dem Herrn für Ihre Güte. Die Welt wurde heller, als Sie mir geholfen haben.";
						link.l1 = "Froh"+GetSexPhrase("","")+"   Schön, dich wohlauf zu sehen, Marisa. Ich hoffe, das Leben hat dir keine weiteren unangenehmen Überraschungen beschert. Du siehst viel glücklicher aus.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Kapitän, ich freue mich so, Sie zu sehen! Jedes Mal, wenn Sie unsere Kirche besuchen, fühle ich mich ruhig. Sie bringen das Licht guter Taten mit sich.";
						link.l1 = "Und ich bin froh"+GetSexPhrase("","")+" Schön, dich zu sehen, Marisa. Hast du dich an das ruhige Leben gewöhnt, oder schaust du manchmal noch zurück?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", wenn alle das Gebet immer wieder aufschieben würden, wäre die Welt längst in Dunkelheit versunken. Leg deine Sorgen für einen Moment beiseite – Reue gibt dir die Kraft, weiterzumachen.";
			link.l1 = "Ich verstehe, Marisa, aber ich kann wirklich gerade nicht. Ich glaube, der Herr hört mich auch ohne Worte.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", hast du deine Meinung geändert? Sünden verschwinden nicht einfach so, und je länger du wartest, desto schwerer lasten sie auf dir.";
			link.l1 = "Leider muss ich jetzt gehen. Aber beim nächsten Mal verspreche ich, dass ich beten werde.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Aber Glaube bedeutet nicht nur zu wissen, sondern auch zu handeln! Du kannst den Weg zur Erlösung nicht ewig aufschieben. Willst du nicht die Erleichterung spüren, die Last der Sünde abzuwerfen?";
			link.l1 = "Vielleicht, aber nicht jetzt. Möge der Herr mich erhören, auch wenn das Gebet warten muss.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Kapitän, findest du nicht, dass es schon eine Sünde ist, die Reue aufzuschieben? Eines Tages könnte es zu spät sein.";
			link.l1 = "Vielleicht, aber ich fürchte, ich habe heute keine Zeit. Der Glaube ist bei mir, und der Herr sieht meine Reue auch ohne Gebet.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Ja, dank Ihnen kann ich wieder frei atmen. Möge der Herr über Sie und Ihre Reise wachen. Vielleicht beten Sie mit mir?";
			link.l1 = "Ich glaube, deine Gebete sind stark genug, so wie sie sind. Am wichtigsten ist, dass dich jetzt nur noch Güte umgibt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", hast du es dir doch anders überlegt? Sollen wir zu unserem Schöpfer beten?";
			link.l1 = "Leider, Marisa, muss ich jetzt gehen, ich habe noch etwas zu erledigen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Ich versuche, nur nach vorne zu schauen. Jetzt habe ich eine Zukunft, und das verdanke ich ganz dir. Vielleicht sollten wir gemeinsam dem Herrn dafür danken?";
			link.l1 = "Ich glaube, du wirst das besser machen als ich. Hauptsache, deine Gebete bringen dir Frieden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", vielleicht kann ich Sie dazu überreden, wenigstens ein Gebet zu sprechen?";
			link.l1 = "Vergib mir, Marisa, aber leider habe ich jetzt keine Zeit. Bitte bete auch für mich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Kapitän, das ist nicht der richtige Ort. Die Höhle, die wir brauchen, liegt an der Mosquito-Bucht.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}