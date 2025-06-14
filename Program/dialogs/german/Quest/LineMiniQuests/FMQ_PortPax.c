// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ein offensichtlicher Fehler. Sag es den Entwicklern.";
			link.l1 = "Oh, ich werde.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Was zum Teufel geht hier vor sich, Herren? Ich habe einen Kampf gehört.";
			link.l1 = "Hallo Offizier, ich hörte eine Frau schreien und...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Sie können gehen, Kapitän. Ich sehe, was hier passiert ist, wir werden Sie rufen, falls wir Fragen haben.";
			link.l1 = "Sehr gut...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Was zum Teufel geht hier vor, Herren? Ich habe Kämpfe gehört.";
			link.l1 = "Danke, Offizier, ich hörte eine Frau um Hilfe schreien und sah, wie dieser Herr von zwei Schurken angegriffen wurde. Ich versuchte, den armen Mann zu retten, aber, ach, ich kam zu spät. Die Bastarde haben ihn getötet!";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Verdammt noch mal... Er ist ein Spanier! Warum sollte er hier sein? Hm. Und wer sind Sie dann, mein Herr?";
			link.l1 = ""+GetFullName(pchar)+". Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Kapitän, Sie sind vorerst frei zu gehen. Ihre Worte stimmen mit den Zeugen überein. Wir werden Sie rufen, wenn es nötig ist.";
			link.l1 = "Sehr gut...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Erlauben Sie mir, alles zu erklären, senor! Mein Name ist Don Domingo Ortiz Albalate aus Santo Domingo. Ich kam auf Einladung einer jungen senorita nach Port-au-Prence und machte einen Halt in dieser Taberna, um auf das vereinbarte Treffen zu warten. Während ich mich um meine eigenen Angelegenheiten kümmerte, wurde ich von diesen beiden verfluchten ladrones angegriffen. Wäre dieser Gute Samariter nicht zufällig vorbeigekommen, würde ich jetzt bei den Engeln speisen.";
			link.l1 = "Don Domingo Ortiz Albalate? Sie sind Spanier?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "So spanisch wie Rey Felipe selbst, ha! Ich möchte auch darauf hinweisen, dass meine Papiere in Ordnung sind. Ich bin ein Adeliger aus Spanien, nicht irgendein dreckiger Pirat!";
			link.l1 = "Don Domingo, unsere aufrichtigsten Entschuldigungen für diesen bedauerlichen Vorfall! Bitte kommen Sie mit uns zu einigen Fragen und einer Flasche Wein in die Garnison. Wir kümmern uns um alles. Was Sie betrifft...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = "Herr Kapitän! Herr Kapitän! Ich schwöre bei Santiago und der Heiligen Jungfrau, Sie sind ein edler Mann, und ein wahrer Sohn von Kastilien belohnt stets solche Adel! Ich würde Sie gerne später belohnen, wenn ich meine Geschäfte hier beendet habe. Bitte, ehren Sie mich mit einem Besuch in meinem bescheidenen Haus in Santo Domingo! Es ist in der Nähe der Stadttore. Ich werde ein Fest für Sie ausrichten, mein buen caballero Carlos! Merken Sie sich meinen Namen, er ist Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Kapitän "+GetFullName(pchar)+"?! Oh Mutter Gottes! Was für eine Katastrophe! Das ist ein Massaker! Was ist hier passiert, guter Freund? Wer sind diese Männer?";
			link.l1 = "Freut mich, Sie zu sehen, Don Domingo. Das sind... Ich bin hierher gekommen, um Ihnen einen Besuch abzustatten. Siehst du den Kerl dort drüben? Das ist Ugo, dein Diener und er...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Oh nein, du wurdest getäuscht, Kapitän!";
			link.l1 = "Ich verstehe, das passiert mir oft. Drei Schurken sind in dein Zuhause eingebrochen, haben deinen treuen Mann Ugo ermordet - ich habe seine Leiche bereits oben gefunden - und dann einen Hinterhalt für dich vorbereitet. Meine Ankunft war nicht Teil ihres Plans. Sie haben unser Treffen nicht überlebt.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! Du führst dein Schwert wie die Fechtmeister von Toledo! Es ist gut, dass du auf meiner Seite bist! Oh, mein armer Ugo! Er hat mich großgezogen, seit ich ein Kind war und jetzt... ermordet von verdammten Canallas!";
			link.l1 = "Don Domingo, es sieht so aus, als wären Sie noch nicht außer Gefahr. Ihr Mann Ugo wusste etwas, lesen Sie diesen Zettel. Ich habe ihn auf einem Tisch gefunden.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Gib es mir... (liest) Das kann nicht sein... oh, nein! Das ist unglaublich! Tio Luis... Aber...";
			link.l1 = "Gibt es einen Hinweis darauf, wer das getan hat?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Nur Verdächtigungen... schreckliche Verdächtigungen mi amigo! Wie könnte der Bruder meiner Mutter so etwas tun?";
			link.l1 = "Hätten Sie etwas dagegen, mich aufzuklären? Es tut mir leid, Don Domingo, aber meiner Erfahrung nach sind Verwandte oft die schlimmsten Feinde, die ein Mann haben kann...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Ja, du hast recht, Carlos! Ich werde dir alles erzählen! Du hast mich schon zweimal gerettet und es scheint, dass du momentan der einzige Mann bist, dem ich vertrauen kann! Aber lass uns diesen schrecklichen Ort verlassen, er macht mich krank. Ich muss den Alcalde über dieses Durcheinander informieren, sie werden sich um den armen Ugo kümmern. Wie wäre es, wenn wir in der örtlichen Taverne etwas Wein trinken, um unsere Nerven zu beruhigen?";
			link.l1 = "Deine Nerven brauchen es sicherlich mehr als meine, führe den Weg senor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "So, mein Freund, erlaube mir, dir eine... gekürzte Form meiner Familiengeschichte zu erzählen. Meine Mutter, Dona Isabella Ortiz, heiratete meinen Vater, ek Marquis Ricardo Albalate, und nahm nach Brauch seinen Familiennamen an. Ihr Bruder, Luis Ortiz, war ein Garnisonskommandant in den Kolonien, aber nach der Heirat meiner Mutter wurde er von meinem Vater zum Verwalter einer Zuckerplantage unweit von Portobello ernannt\nDies war eine riesige und wohlhabende Plantage, sehr profitabel tatsächlich. Nach dem tragischen Tod meiner Eltern auf See vor ein paar Jahren, erbte ich als einziger Sohn alles, einschließlich der Plantage. Mein Onkel hat seine Position behalten und ich war mit der Miete, die er mir zahlte, durchaus zufrieden. Er hat seine Zahlungen immer pünktlich geleistet.";
			link.l1 = "Also du denkst, dein Onkel...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Ja. Momentan ist er nichts weiter als ein Mieter. Ich besitze die Plantage, nicht er. Aber! Wenn mir etwas zustößt - wird es sein Eigentum.";
			link.l1 = "Du weißt, Domingo, ich kannte Männer, die alle ihre Verwandten kaltblütig für einen Preis ermorden würden, der viel weniger saftig ist als dieser.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Du solltest offensichtlich bessere Gesellschaft halten, Carlos. Mein lieber Ugo erwähnte die Papiere meines Onkels in seiner letzten Notiz... Das ist ein direkter Hinweis. Oh, ich will das nicht glauben! Aber... meine Cousine, Margarita Ortiz, die in Spanien lebt, wurde vor nicht allzu langer Zeit verlobt. Könnte das der Grund sein, mein guter Kapitän?";
			link.l1 = "Dein hingebungsvoller Onkel könnte plötzlich etwas Geld benötigen...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Geld?! Aber natürlich... aber vergiss nicht den Titel des Marquis! Das würde meinen Cousin zu einer passenden Partie für ihren zukünftigen Ehemann machen! Jesu Christo! Wie dumm ich war!";
			link.l1 = "Dieser Adelstitel hat mehr Wert als die Zuckerplantage.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Warte mein Freund! Mir ist gerade eingefallen, dass dies nicht der erste Mordversuch an mir war! Ich hatte vor ein paar Wochen eine Begegnung mit einem Bettler auf der Straße! Der betrunkene Canaille beleidigte mich auf eine Weise, die ich nicht ignorieren konnte. Er stellte sich als verdammt guter Fechter heraus, er zog Stahl und schaffte es sogar, mich mit einem Degen zu verwunden, bevor ich ihn tötete.";
			link.l1 = "Und wie zur Hölle bist du in einer Taverne in Port-au-Prince gelandet? Du hast von irgendeiner jungen Senorita gesprochen?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(wird rot) Herr ... Ja Kapitän, es gab eine junge und hübsche Senorita vor Ort ... jetzt sehe ich, dass sie nur der Köder für die Falle war. Bastarde, Bastarde sind überall, man kann niemandem vertrauen! Der arme Ugo ... er ist jetzt tot.";
			link.l1 = "Du solltest etwas dagegen unternehmen, Domingo. Wie wäre es mit einer Flucht nach Spanien?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "Nach Spanien? Und meine Plantage diesem Schurken überlassen? Kapitän, ich bin Marquis Domingo Ortiz Albalate!";
			link.l1 = "Aber...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "Mein Freund Carlos, darf ich um deine Hilfe bitten? Da Ugo tot ist, habe ich niemanden an meiner Seite, dem ich vertrauen kann. Du hast mich schon zweimal gerettet! Zweimal! Ich schulde dir viel, ich bin dir auf ewig verpflichtet und dennoch wage ich es, dich um einen weiteren Gefallen zu bitten. Ich schwöre bei der gesegneten Mutter, es wird sich für dich lohnen!";
			link.l1 = "Sehr gut, du bist ein guter Mann für einen Spanier. Was kann ich für dich tun, Domingo?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Lass uns zu meiner Plantage in Portabello gehen! Ich weiß, dass mein Onkel gerade in Cartagena ist. Ugo hat einige Papiere erwähnt, also lass uns die Bücher und Dokumente von Don Luis Ortiz überprüfen! Wir könnten etwas finden, das uns hilft, seine abscheuliche Verschwörung ans Licht zu bringen. Es ist ein ziemlicher Weg bis nach Portobello, aber ich werde dich für die Reise voll bezahlen!";
			link.l1 = "Es wäre absurd, Sie jetzt abzulehnen, Don Domingo. Ich stecke zu tief drin, um jetzt noch auszusteigen.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Dank Gott, ich wusste, dass du mir helfen würdest, Freund! Hier, nimm diese zwanzigtausend Pesos als Bezahlung für die Reise nach Portobello. Wann setzen wir die Segel? Wir müssen uns beeilen, bevor mein Onkel aus Cartagena zurückkehrt!";
			link.l1 = "Lassen wir dann keine Zeit verschwenden.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Hier ist eine Lizenz der Niederländischen Westindischen Kompanie. Sie hat eine Gültigkeit von zwanzig Tagen, lass uns einfach deinen Namen eintragen. Fertig. Das sollte uns helfen, Ärger mit der Costa Garda zu vermeiden.";
			link.l1 = "Ausgezeichnet!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Darf ich jetzt an Bord Ihres Schiffes kommen, mein Freund?";
			link.l1 = "Betrachten Sie sich als geehrten Gast. Sobald wir den richtigen Wind bekommen - setzen wir die Segel.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "So Kapitän Carlos, hier sind wir. Jetzt sollten wir das Haus meines Onkels finden und sehen, was drin ist.";
			link.l1 = "Don Domingo, sollten wir irgendwelche Probleme mit der Wache erwarten?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Nein. Obwohl... hm. Es besteht die Möglichkeit, dass Luis sie gegen mich aufgehetzt hat. Wie dem auch sei, Vorsicht ist stets besser als Nachsicht. Lassen Sie uns das Haus finden, das wir brauchen.";
			link.l1 = "Weißt du es nicht schon? Es ist deine Plantage.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm.. Um ganz ehrlich zu sein, das letzte Mal, als ich hier war, war ich erst acht Jahre alt. Aber ich beabsichtige, dies so schnell wie möglich zu beheben!";
			link.l1 = "Ich verstehe. Dann fangen wir an zu suchen. Das Haus deines Onkels muss das größte hier sein.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Was hast du hier, mein Freund?";
			link.l1 = "Schauen Sie mal, Don Domingo. Sieht aus wie Buchhaltungsunterlagen. Das könnte interessant sein.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(liest) Hm... Ja. Schau dir das an... Ay caramba! Hunderttausend Pesos! Und noch einmal hundertfünfzigtausend! Und hier... (blättert Seiten um) Onkel Luis!";
			link.l1 = "Gibt es etwas von Interesse?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Alles von Interesse! Mein wertvoller Onkel hatte ein Einkommen, das fünfmal größer war als das, was er mir erzählt hat! Dieb! Veruntreuer!";
			link.l1 = "Kann nicht sagen, dass ich überrascht bin. Man kann niemandem vollkommen vertrauen, ohne von Zeit zu Zeit den tatsächlichen Geschäftszustand zu überprüfen. Das ist einfach gesunder Menschenverstand.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Allgemeiner Menschenverstand für gewöhnliche Männer, vielleicht. Meine Erziehung hat mich vor solchen Täuschungen bei Herren, die ich für ehrenwert hielt, geblendet! Wie immer hast du Recht, Carlos! Mein eigener Onkel stiehlt von mir! Scheiße! Das ist mein Fehler, aber ich werde das regeln. Diese Plantage gehört mir und mein Onkel ist ab heute seiner Pflichten enthoben! Er ist niemand! Ich werde ihn kielholen lassen!";
			link.l1 = "Don Domingo... Glauben Sie nicht, dass Ihr Onkel eine solche Entscheidung vielleicht nicht gutheißen könnte?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Ich gebe einen Dreck darauf, ob er einverstanden ist oder nicht! Ich bin Marquis Domingo Ortiz Albalate und Luis Ortiz ist nichts weiter als ein Mieter, und das auch noch ein ehemaliger! Und er...";
			link.l1 = "Beruhige dich, senor. Du bist ein unbekanntes Gesicht hier und ich bin ein Franzose, der unter einer holländischen Lizenz segelt mit einer...schillernden Vergangenheit mit den spanischen Piratenabwehrpatrouillen. Was deinen Onkel betrifft, er besitzt praktisch diese Stadt. Denk an die Wachen und den lokalen Gouverneur. Glaubst du, sie werden sich für deine Seite entscheiden?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Du triffst den Punkt mit einem Degen... Vielleicht... Nein. Spanische Soldaten würden es niemals wagen, Hand an einen Adligen zu legen! Mein Onkel kann mich herausfordern, wenn er es wagt!";
			link.l1 = "Dennoch schlage ich vor, einen anderen Weg zu gehen. Wie wäre es mit dem Gericht?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! Du hast recht, Carlos. Lassen wir uns mit den zuständigen Behörden sprechen. Mein Onkel hat einen Fehler gemacht, indem er genaue Details in seinen Notizen über seine Geschäfte mit Schmugglern aufschrieb. Er kaufte Sklaven von ihnen für sehr billig. Diese Bücher werden uns einen großen Dienst erweisen, ich bezweifle, dass der Bastard mir auf irgendeine Weise schaden kann, während er in den Verliesen sitzt. Lass uns gehen, mein Freund! Nach Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "Das ist nichts als eine schmutzige und freche Lüge! Wie wagt er es, den guten Namen meiner Eltern mit seiner unwürdigen Zunge zu beschmutzen! Verdammt sei er, ich werde ihn dafür bezahlen lassen! Zieh dein Schwert, du Mörder!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Onkel Luis ist am richtigen Ort für seine Seele - in der Hölle... Carlos, du wurdest mir von meinem Schutzengel geschickt! Ich bin froh, dass du dem Wort dieses Schurken nicht vertraut hast. Um ehrlich zu sein, hatte ich Angst, dass du mich einfach hier alleine lassen würdest, um gegen diesen Canalla zu kämpfen. Ja, Senor, ich bin selbst nicht perfekt, aber das... diese widerliche Lüge, dass ich Piraten angeheuert habe, um meine eigenen Eltern zu ermorden! Mich dafür zu beschuldigen... das! Bah! Ein wohlverdientes Schicksal.";
			link.l1 = "Wir haben es geschafft, Don Domingo. Was nun? Ich hoffe, wir haben das spanische Gesetz nicht verletzt.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Mit dem Gesetz? Ha-ha! Nein Carlos, ich werde dieses feine Buchhaltungsbuch mit all den Schmuggelaktionen meines Onkels darin zeigen. Vergiss nicht die vielen Versuche auf mein Leben, wir haben eine große Anzahl von Zeugen nach seinem letzten Versuch gerade jetzt. Mach dir keine Sorgen, mi buen amigo. Dies ist meine Stadt, es ist Zeit, dass ich es ihnen allen zeige!";
			link.l1 = "Bitte bewegen Sie sich vorsichtig, Senor. Lassen Sie sie besser von Ihnen denken, als sie von Ihrem verstorbenen Onkel gedacht hatten.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Das ist der Plan, Kapitän. Aber ich werde niemandem Gnade zeigen, der es wagt, sich mir zu widersetzen. Lassen Sie mich Ihnen meine aufrichtige Dankbarkeit ausdrücken, Carlos! Bitte, gehen Sie zur Taberna, ruhen Sie sich aus, trinken Sie ein oder zwei Gläser. Ich würde mich freuen, mich Ihnen anzuschließen, aber Sie hatten recht. Es ist Zeit, weiser zu werden und die Kontrolle über die Plantage selbst zu übernehmen. Besuchen Sie mich morgen hier, Kapitän!";
			link.l1 = "Sehr gut, Don Domingo. Wir sehen uns morgen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ach, da bist du ja, mein guter Freund!";
			link.l1 = "Wie geht es Ihnen, Don Domingo? Wie steht es um Ihre Plantage?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Die Plantage ist großartig, das Gleiche kann ich nicht über das Geld sagen - es stellt sich heraus, dass mein lieber Onkel all das Geld auf die Bank von Cartagena überwiesen hatte. Es wird viel Anwaltszeit benötigen, um mein Gold zurückzubekommen. Aber das ist in Ordnung, ich kann das schaffen. Sei nicht traurig Kapitän, ich werde meine Versprechen halten, dich für deine Adel, Ehrlichkeit und Freundschaft zu belohnen!";
			link.l1 = "Noch nie habe ich an eine Belohnung gedacht, als ich an Ihrer Seite gekämpft habe, senor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Ich weiß das, Kapitän, und das sagt viel über Ihren Charakter aus! Jede gute Tat muss belohnt werden. Also, obwohl ich im Moment kein Geld habe, werde ich den Befehl geben, Ihr Schiff mit Waren meiner Plantage zu beladen. Ich meine Kaffee, eine große Menge davon. Sie werden in der Lage sein, ihn mit großem Gewinn zu verkaufen, da bin ich sicher.";
			link.l1 = "Oh! Das ist schön..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Darüber hinaus habe ich ein paar Gegenstände von geringem Wert für mich, aber von großem Wert für jeden Seemann wie dich. Ein feines Fernrohr und drei Amulette. Bitte nimm diese an, sie gehören jetzt alle dir.";
			link.l1 = "Dankbarkeit!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Endlich schenke ich Ihnen meinen Degen als Zeichen meiner unermesslichen Dankbarkeit. Sie hat mir gut gedient, nun soll sie Ihnen noch besser dienen. Schauen Sie sie an und erinnern Sie sich an Ihren guten spanischen Freund - Marquis Domingo Albalate!";
			link.l1 = "Vielen Dank, Senor! Ich habe nicht erwartet...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Und nun, ach, muss ich mich verabschieden. Ich sollte nach Portobello gehen, um den Gouverneur zu sehen und dann nach Cartagena... Kurz gesagt, meine sorglose Existenz ist vorbei, es ist Zeit, als erwachsener Mann zu leben.";
			link.l1 = "Nun, du bist jetzt viel klüger...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "Das stimmt. Es war ein Vergnügen, mein Freund! Komm mich mal besuchen. Viel Glück auf See!";
			link.l1 = "Gleiches gilt für Ihr Plantagengeschäft, Don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, wir sind spät dran, Señor! Was für ein Pech, mein guter alter Onkel hat bereits eine ordentliche Aufräumarbeit unter seinen Papieren gemacht. Sieht so aus, als hätte man ihm von Santo-Domingo erzählt und er hätte Vorsichtsmaßnahmen getroffen... Aber ich werde es nicht dabei belassen! Ich sollte den Gouverneur von Portobello aufsuchen, um ein rechtliches Verfahren gegen meinen Onkel einzuleiten. Ich habe genug davon, dass er mein Vermögen verwaltet.";
			link.l1 = "Gute Entscheidung.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Ich möchte Ihnen danken, Kapitän! Es war mir eine Freude! Ich schenke Ihnen meinen Degen als Zeichen meiner Dankbarkeit. Sie hat mir gut gedient, jetzt soll sie Ihnen noch besser dienen. Schauen Sie sie an und erinnern Sie sich an Ihren guten spanischen Freund - Markgraf Domingo Albalate!";
			link.l1 = "Vielen Dank, Senor! Ich habe nicht erwartet...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "Und nun, leider, muss ich Abschied nehmen. Ich sollte nach Portobello gehen. Meine sorglose Existenz ist vorbei, es ist Zeit als erwachsener Mann zu leben. Gott gebe dir eine schnelle Seereise!";
			link.l1 = "Viel Glück mit deinem Onkel, Don Domingo! Ich bin sicher, du wirst siegen!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			dialog.text = "Sieht so aus, als hätte ich es rechtzeitig geschafft. Mein sorgloser Neffe und sein Schutzengel Kapitän "+GetFullName(pchar)+". Sei nicht so überrascht, Franzose, ich weiß, wer du bist.";
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Sie haben recht, Kapitän, aber alles andere haben Sie falsch verstanden. Sie sollten Ihre Nase nicht in die Familienangelegenheiten anderer Leute stecken. Sie haben nicht mal eine Ahnung, wen Sie da schützen. Mein liederlicher Neffe Domingo ist ein wertloser Tunichtgut, der Stammgast in jeder Kneipe und jedem Bordell ist und jede Frau am Horizont beglückt oder zumindest versucht, dies zu tun. Ich zahle ihm jeden Monat seine Miete und er verschwendet sie in Tagen und verlangt immer mehr und mehr. Immer wieder. Sein ständiges unwürdiges Verhalten trieb seine Mutter und meine Schwester in den Wahnsinn. Ich habe Gerüchte gehört, dass dieser ungezogene Junge sogar einige englische Freibeuter angeheuert und auf ein bestimmtes Schiff des Marquis Ricardo Albalate angesetzt hat, das sie versenkt haben, zusammen mit diesem ehrwürdigen Mann und meiner geliebten Schwester. Domingo wollte unser Familienvermögen so sehr, dass er dafür töten würde... Leider konnte ich nicht genug Beweise sammeln, um diesen Schurken an den Galgen zu schicken.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "Typisch. Geschrei, das Klirren von Schwertern und Bechern, voller Lärm und Wut, bedeutet nichts. Wie viel hat er Ihnen bezahlt, Kapitän, für Ihren Schutz?";
			link.l1 = "Soweit ich verstehe, nachdem Sie es nicht geschafft haben, irgendwelche Beweise gegen Ihren Neffen auszugraben, haben Sie angefangen, Attentäter nach ihm zu schicken. Klingt, als hätte eine einfache Klage ausgereicht.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Du sprichst Lügen. Domingo hier hat eine unzählige Menge an Feinden gemacht. Er hat eine Spur von enttäuschten Liebhabern und gehörnten Ehemännern hinterlassen. Ich frage mich, wie er es überhaupt geschafft hat, so lange zu überleben! Frag ihn, wie viele Hochzeiten hat er ruiniert? Wie viele beleidigte Verlobte hat er verletzt oder getötet?";
			link.l1 = "Sein Diener Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ach Ugo! Der schlimmste Schurke von allen! Ugo liebte seinen Tunichtgut von einem Meister. All die Verbrechen seines Meisters waren für ihn nichts weiter als ein Kinderspiel. Erinnere dich, Franzose, Familiengeschäfte sind nur für die Familie. Diejenigen, die schnüffeln und neugierig sind, werden sich in heißem Wasser wiederfinden.";
			link.l1 = "Jetzt drohst du mir.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Keine Bedrohung, Kapitän, ein Versprechen. Schau her, Junge, du hast einen weiten Weg hinter dich gebracht, aber da ich dich als ein getäuschtes Opfer und nicht als einen Feind sehe, hör dir mein einfaches und großzügiges Angebot an: Geh weg. Ich möchte hier kein Blut vergießen. Wir brauchen deine Hilfe nicht, um unsere familiären Angelegenheiten zu klären. Ich bin sogar bereit, die Unannehmlichkeiten, die du wegen meines idiotischen Neffen durchgemacht hast, zu entschädigen - "+FindRussianMoneyString(iTotalTemp)+" Stücke von Acht. Nimm es und lass uns in einem Stück. Lehnst du mein Angebot ab, schicken wir dich in dünnen Scheiben zurück zu deinem Schiff.";
			link.l1 = "'Familie zuerst' sage ich immer. Nicht meine Angelegenheit dann, gib das Geld rüber und 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Deine Geschichte stinkt schlimmer als der Dünger deiner Plantage. Don Domingo mag kein Heiliger sein, aber du, Senor, bist ein Teufel!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Ich wusste, dass Sie ein vernünftiger Mann sind. Nehmen Sie Ihr Geld und adios Kapitän. Versuchen Sie in der Zukunft nicht, in der schmutzigen Wäsche anderer zu wühlen - sie schätzen es nie.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Ein Teufel? Nun, es wird mir ein Vergnügen sein, dich zur Hölle zu schicken!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+"Señor. Wie kann ich Ihnen behilflich sein?";
			link.l1 = "Grüße. Entschuldigung, aber ist dies die Residenz von Senor Domingo Albalate?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Ja, dies ist das Albalate-Haus. Es ist bescheiden und doch gemütlich. Mein Name ist Ugo, ich diene dem jungen Meister. Sind Sie wegen ihm hier?";
			link.l1 = "Ja, Senor. Don Domingo hat mich vor nicht allzu langer Zeit zu sich eingeladen. Er war sehr überzeugend. Darf ich ihn sehen?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Ach, mein guter Caballero, Don Domingo ist gerade nicht zu Hause. Persönlich würde ich selbst gerne wissen, wo man diesen ungezogenen Jungen... äh, entschuldige, jungen Senor, finden kann. Darf ich fragen, was du von ihm brauchst?";
			link.l1 = "Nun... Ich habe Don Domingo zufällig geholfen. Er wurde in einer Kneipe in Port-au-Prince von zwei Schurken angegriffen. Ich habe Ihrem Meister geholfen, sich gegen diese... wie hat er sie genannt... maldita canalla zu verteidigen. Don Domingo lud mich ein, ihn hier zu besuchen, nachdem er mit der Untersuchung fertig war. Ich dachte, alles sollte schon geregelt sein, also erwartete ich, ihn zu Hause zu sehen.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! Was für schreckliche Geschichten erzählst du hier! Ich muss sofort den Kommandanten sehen - um ihn vor den Gefahren zu warnen, denen Don Domingo gerade jetzt gegenübersteht! Senor, du musst gehen und ich sollte mich beeilen!";
			link.l1 = "Nimm es leicht, Ugo. Dein junger Meister ist sicher. Er erwähnte, dass seine Papiere in Ordnung sind, sie sollten ihn bereits freilassen, deshalb bin ich hier. Ich glaube, wir sollten ihn bald sehen.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! Wie könntest du? Mein junger Meister, dieser naive Junge - und in den Händen dieser Frosch fressenden Franzosen?! Ganz zu schweigen von den Ladrones, die sein Leben bedrohen? Nein, ich muss den Kommandanten sehen! Herr, bitte gehen Sie!";
			link.l1 = "Gut gut, dräng mich nicht so. Ich gehe jetzt.";
			link.l1.go = "ugo_exit";
			link.l2 = "Herr, warum so nervös? Ich habe Ihnen bereits gesagt, dass für Ihren Meister keine Gefahr besteht. Lassen Sie mich hier bleiben und auf die Ankunft von Herrn Domingo warten, ich bin sehr müde von meiner langen Reise und würde Ihre Gastfreundschaft schätzen. Ich hätte gerne etwas kühles frisches Wasser und ein heißes Bad, um die salzige Brise aus meinem Hals zu spülen. Dann können Sie zur örtlichen Garnison gehen und tun, was immer Sie wollen.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Herr, verlassen Sie dieses Haus sofort!";
			link.l1 = "Ugo, ich bezweifle wirklich, dass ein Diener es sich erlauben darf, mit einem Herrenbesucher auf diese Weise zu sprechen. Ich bezweifle auch, dass Don Domingo eine solche Behandlung eines Mannes gutheißen würde, der ihm das Leben gerettet hat!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Ach wirklich? (ruft nach oben) Jungs, kommt runter, wir haben ein Problem!";
			link.l1 = "Was zum Teufel?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
