// Абрахам Норман
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
		case "First time":
			dialog.text = "Gibt es etwas, das du brauchst?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Was brauchst du, Kumpel? Geh deinen Weg, kümmere dich um deine Angelegenheiten. Lass mich einfach in Ruhe.","He, he, Kumpel. Gehst du spazieren? Nun, du gehst einfach weiter und lässt den Herrn Abraham in Ruhe. Er geht auch spazieren. Er holt sich eine frische Meeresbrise.","Hallo, Freund. Lust zu plaudern? Es gibt nur ein Problem: Ich bin nicht in der Stimmung zum Reden. Such also jemand anderen, den du belästigen kannst. Geh zurück in die Taverne. Trink etwas Rum...");
				link.l1 = "Hör zu, Abraham, bist du zufällig auf einen Mann namens Miguel Dichoso auf Isla Tesoro gestoßen? Er ist hier irgendwie ein bekannter Kater.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("Was brauchst du, Kamerad? Geh deinen Weg, kümmere dich um deine Angelegenheiten. Lass mich einfach in Ruhe.","He, he, Kumpel. Gehst du spazieren? Nun, du gehst einfach weiter und lässt Herrn Abraham in Ruhe. Er geht auch spazieren. Er holt sich eine frische Meeresbrise.","Hallo, Kumpel. Lust zu plaudern? Es gibt nur ein Problem: Ich bin nicht in Stimmung zum Reden. Also geh jemand anderen belästigen. Geh in die Taverne und entspann dich. Trink etwas Rum..."),LinkRandPhrase("He, Matrose. Was, bist du stur oder so? Ich dachte, ich wäre ziemlich deutlich gewesen.","Kumpel, geh und ruh dich aus. Du scheinst ein wenig schwerhörig zu sein.","Hallo Kumpel, was, bist du dumm oder so? Ich habe es dir praktisch schon buchstabiert."),"Kumpel, bring mich nicht auf die Palme. Ich habe in meiner Zeit so viele Landratten abgeschlachtet, eine mehr oder weniger macht wirklich keinen Unterschied.","In Ordnung, du hast mich verärgert. Jetzt zieh entweder dein rostiges Schwert oder lauf so schnell du kannst. Ich empfehle die zweite Option...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("In Ordnung, Freund. Ich werde dich nicht belästigen.","Gut, gut. Ich habe es verstanden...","Woah, na du siehst aus wie der Donner der Meere! Okay, ich bin hier raus.","Was?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("Was brauchst du, Kumpel? Geh deinen Weg, kümmere dich um deine Angelegenheiten. Lass mich einfach in Ruhe.","He, he, Kumpel. Gehst du spazieren? Nun, du gehst einfach weiter und lässt Herrn Abraham in Ruhe. Er geht auch spazieren. Er holt sich eine frische Meeresbrise.","Hallo, Kumpel. Lust zu plaudern? Es gibt nur ein Problem: Ich bin nicht in Stimmung zum Reden. Also geh jemand anders belästigen. Geh in die Taverne und entspann dich. Trink etwas Rum...");
				link.l1 = "Hör zu, Abraham, bist du zufällig auf einen Mann namens Miguel Dichoso auf Isla Tesoro gestoßen? Er ist hier irgendwie eine bekannte Katze.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "Halt! Ich bin der Gouverneur dieser Insel. Was, du glaubst mir nicht?!";
					link.l1 = "Natürlich weiß ich das! Wer kennt den Gouverneur von Isla Tesoro nicht...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "Ha, nenn dich doch gleich einen Admiral, das kaufe ich dir auf jeden Fall ab!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "Achtung! Siehe - Admiral Barbarigo! Erkennst du nicht mein berühmtes Kavallerieschwert?";
					link.l1 = "Meine Entschuldigung, Herr Admiral! Von nun an werde ich aufmerksamer sein.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "Dein Kavallerieschwert ist weithin bekannt. Schade, dass es in den Händen eines Narren ist.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "Wie Sie sehen können, bin ich hier im Exil. Ich warte auf weitere Benachrichtigungen von General Monk. Ich bitte Sie, meine verborgene königliche Identität nicht zu verbreiten. Cromwells Geheimdienst hat lange Ohren.";
					link.l1 = "Aber natürlich, Eure Majestät. Niemand wird jemals erfahren, dass Karl der II. sich in Westindien versteckt.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "Nun, und ich bin dann Papst Innozenz X.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "Was ist mit dir passiert, Blaze? Ich habe zwei Tage lang nach dir gesucht. Du hast deinen Vater Nicolas völlig vergessen!";
					link.l1 = "Ich habe keine Zeit für dich Vater! Ich bin überlastet.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "Sie irren sich, mein Herr. Mein Name ist "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "Sh-sh... Ich bin Davy Jones. Sag mir, hast du Angst vor dem Tod?";
					link.l1 = "Natürlich bin ich das, Herr Jones. Besonders nach einem Kater.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "Einer Tod ist eine Tragödie, tausend Tode sind nur eine Statistik.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "Ich bin in Eile, mein neues Stück zu beenden. Du musst mir helfen, den Satz 'Sein oder nicht sein' zu beenden?!";
					link.l1 = "Das ist die Frage! Sollen wir die Beleidigung ertragen und weitermachen...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "Ein Getränk, sicher. Aber es würde mich nicht überraschen, wenn ich in einem Bordell eine Krankheit einfange!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "Wovon zum Teufel redest du? 'Tesoro'?! Du könntest es genauso gut die Bermudas nennen! Diese Insel heißt Norman Island nach mir und das vergiss nicht! Ich werde dir Geographie beibringen müssen...";
			link.l1 = "Huh! Was meinst du?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "Du hast recht, Seemann. Ich bin wirklich Admiral Barbarigo, aber das bleibt streng unter uns. Mach dich bereit zum Marsch. Wir brechen bald auf. Das wird dir nützlich sein.";
			link.l1 = "Ich bin äußerst dankbar!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "Wir werden jetzt gleich sehen, wer der Narr ist. En garde!";
			link.l1 = "Bist du ernst?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "Was habe ich dir gesagt! Hier, trink auf meine Gesundheit.";
			link.l1 = "Trink aus, Admiral!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "Ich habe dich gebeten, meinen Namen nicht zu verbreiten! Jetzt muss ich dich als gefährlichen Zeugen loswerden...";
			link.l1 = "Oh, ich habe darauf gewartet!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "Verzeihen Sie mir, Eure Gnaden! Ich habe Sie in dieser Kleidung nicht erkannt. Bitte, akzeptieren Sie dieses bescheidene Geschenk von einem wahren Katholiken.";
			link.l1 = "Der Wahnsinn meldet sich...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "Alle kommen auf mich zu! Ich habe einen Spion gefangen, der genauso aussieht wie mein Sohn! Ich bin sicher, Thomas hat ihn geschickt, um mein zweites Auge auszuschlagen!";
			link.l1 = "Verschwinde, Trottel!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "Du bist müde und siehst nicht so gut aus, mein Junge. Geh und hol dir etwas Behandlung.";
			link.l1 = "Danke!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "Hab keine Angst, Kumpel. Siehst du, Sterben ist überhaupt nicht beängstigend...";
			link.l1 = "Sieht so aus, als ob Sie keinen Scherz machen!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "Anscheinend hast du keine Angst. Ich wusste es. Das ist Mut!";
			link.l1 = "Du bist ein lustiger alter Mann...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "Du bist ein miserabler Dichter, Seemann. Könnte es sein, dass deine Klinge agiler ist als deine Zunge?";
			link.l1 = "Caramba! Dieses Kavallerieschwert von dir ist überhaupt kein Schwindel!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "Verdammt! Die Dinge sind ziemlich gut für dich gelaufen! Was hältst du davon für deine Fantasie!";
			link.l1 = "Komm wieder.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "Aha, ich erkenne dich! Ha-ha!";
			link.l1 = "Nochmal...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "In Ordnung, Kumpel, wir haben unser Gespräch gehabt. Mach dich jetzt auf den Weg.";
			link.l1 = "Wie du sagst...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "Dichoso? Wofür brauchst du ihn, huh?";
			link.l1 = "Nun, ich brauche ihn. Ich brauche ihn einfach. Also, hast du ihn gesehen?";
			link.l1.go = "tieyasal_1";
			link.l2 = "Was meinst du, wofür ich ihn brauche? Miguel ist mein alter Kumpel, könnte man sagen, ein Freund. Er sollte eigentlich...";
			link.l2.go = "tieyasal_2";
			link.l3 = "Ich möchte, dass er für mich ein neues Schiff schleppt, genau wie er es einmal für Shark Dodson getan hat.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso hat einen Mann getötet. Deshalb suche ich ihn.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "Du brauchst ihn nur... Du brauchst ihn wirklich nur! Alles, was du brauchst, ist Miguel Dichoso! Nein, ich habe ihn nicht gesehen. Ich habe ihn schon lange nicht mehr gesehen. Ich kann dir nicht helfen, Seemann.";
			link.l1 = "Hm... Also gut, auf Wiedersehen.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "Ein Freund, sagst du... Er scheint einen ganzen Haufen Freunde angehäuft zu haben. Er steht kurz davor, einen Freund weniger zu haben...";
			link.l1 = "He, alter Mann. Was ist los mit dir?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "Ja, Dichoso ist ein Meister solcher Handwerke, egal wie man es betrachtet. Aber ich weiß nicht, wo er ist. Er kam vorbei, aber machte sich wieder aus dem Staub. Also geh zu Alexus, Matrose. Er wird dir eine wunderbare Kiste zusammenzimmern.";
			link.l1 = "Hm... Danke für den Tipp, Kumpel.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "Und wen hat Dichoso für dich erledigt, dass du ihn suchst, he Kumpel? ";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_4_1":
			dialog.text = "Was meinst du? Welchen Sharp hat er genau getötet? Es gibt viele Sharps, weißt du.";
			link.l1 = "";
			Link.l1.edit = 8;
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			sTemp = GetStrSmallRegister(dialogEditStrings[8]);
			if (sTemp == "blaze sharp")
			{
				dialog.text = "Sh-sh-sh ...(umschauend) Also denkst du auch, dass Blaze Sharp von Dichoso getötet wurde?";
				link.l1 = "Ja. Ich habe nicht nur meine Vermutungen, sondern auch handfeste Beweise. Einträge in seinem Logbuch...";
				link.l1.go = "tieyasal_6";
				break;
			}
			if (sTemp == "sharp")
			{
				dialog.text = "Mach weiter, kleiner Seemann...";
				link.l1 = "Was meinst du? Erzähl mir mehr.";
				link.l1.go = "tieyasal_4_1";
				break;
			}
			dialog.text = "Ach...Nun. Er hat ihn getötet und das ist alles dazu. Weißt du, wie viele Mörder wir hier herumlaufen haben? Jeder zweite Mann! Nein, Matrose. Ich habe Dichoso schon lange nicht gesehen. Ich kann dir bei nichts helfen.";
			link.l1 = "Schade...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "Beruhige dich, Kamerad. Wie heißt du nochmal? Es ist mir irgendwie entfallen...";
			link.l1 = "Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Hör zu, "+pchar.name+". Dichoso hat den armen Blaze getötet. Ich habe es mit meinen eigenen Augen gesehen, ja-ja. Aber sie glauben mir nicht. Siehst du, sie denken, ich sei verrückt. Einer von ihnen, aber verrückt. Und ich war einst der beste Enteroffizier in der Mannschaft von Nicolas Sharp selbst! Gute Zeiten! Aber schließlich habe ich meine Krallen, Hufe und Linse verloren und bin gestrandet.\nWas? Ah, richtig! Jeder dachte, der Hai wäre schuld, aber das war er nicht. Nein-nein-nein. Es gab einen Haizahn, ein Talisman von Dodson, aber es war Dichoso, der ihn dort platzierte.\nEr muss ihn von Shark gestohlen haben, als sie zusammen auf einer Fregatte namens Fortune segelten. Ich habe an diesem Tag nicht gut geschlafen und bin für einen Spaziergang hinausgegangen. Ich sah, wie Dichoso sich in Sharps Residenz geschlichen hatte, hörte jemanden schreien und dann stöhnen. Kurz danach verließ Dichoso die Residenz und seine Hände waren blutig.\nSie glaubten mir nicht, nein-nein. Denn an diesem Tag war kein Dichoso auf der Insel, aber Shark war es. Und sie fanden seinen Zahn. Aber ich sah Dichoso, ich bin mir sicher. Niemand wusste, dass er an diesem Tag dort war. 'Der Glückliche' ist ein sehr listiger und furchterregender Mann...";
			link.l1 = "Du bist nicht der Erste, der Dichoso 'den Glücklichen' nennt. Warum ist das so? Ist es sein Spitzname?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Weißt du kein Spanisch, Kerl? 'Dichoso' bedeutet 'glücklich' in der Papisten-Sprache. Glücklicher Miguel, Miguel der Glückliche. So heißt er.";
			link.l1 = "Miguel der Glückliche?... Hm. Das erinnert mich an etwas. Hm. Dieser Ausdruck klingt so vertraut...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Nun, auch wenn sein Nachname Dichoso ist, halte ich ihn immer noch nicht für einen Spanier. Nein, nein. Er ist kein Spanier. Obwohl er wie ein Spanier aussieht.";
			link.l1 = "Dann was könnte er sein? Englisch, Französisch?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Das ist nicht, worüber ich spreche, Seemann... Oh, verzeih mir, Kapitän. Ja, Dichoso plappert ganz fabelhaft auf Französisch, nicht schlechter als du. Und auch auf Englisch. Allerdings fließt in seinen Adern indisches Blut. Ich habe in meinem Leben viele solcher Leute gesehen. Es ist nicht offensichtlich zu sehen, aber er ist ein Mischling. Ich garantiere dir.";
			link.l1 = "Spricht er Indisch?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "Oh, die Hölle weiß es. Vielleicht tut er es ja. Obwohl, warte. Er tut es! Er pflegte ständig seltsame Sätze in irgendeiner bizarren Sprache zu äußern, und er machte ein erschreckend weises Gesicht und blies seine Wangen auf, während er sie aussprach. Zum Beispiel würde er so etwas sagen: cogito ergo sum! Und dann würde er die Augen verdrehen und auf die Reaktion der Matrosen warten. Oder er würde so ausrufen: aut Caesar, aut nihil! Er hat auch noch eine Menge anderer Dinge herausgeplappert. Ich erinnere mich nicht an alles, was er gesagt hat.";
			link.l1 = "Das ist keine indische Sprache. Das ist Latein. Latein... Latein?! Heilige Scheiße!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Warum so zappelig, Kerl? Warum schreist du? Hat dich eine Schlange oder so etwas gebissen? Wo ist sie hin?";
			link.l1 = "Warum habe ich es nicht von Anfang an gesehen! Alles starrte mir ins Gesicht! Latein! Miguel... Miguel der Glückliche!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "Hallo, Kumpel. Würdest du aufhören zu brüllen. Die Leute starren uns an. Was frisst dich, Matrose... Entschuldigung, Kapitän?";
			link.l1 = "Ich weiß, wer Miguel Dichoso wirklich ist. Er ist nicht Spanier. Er ist Franzose! Oh, ich war so blind!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "Nein, Dummkopf. Er ist nicht Franzose. Er ist ein Halbblut. Sein weißer Vater hat mit einem kleinen indianischen Mädchen, einer dieser Arawaks oder Miskito aus der Karibik oder sogar einer Itza, Stiefel geschüttelt, und so kam der heilige Miguel Dichoso auf diese Erde. Du siehst das nicht, aber ich schon. Es steht in seinen Augen geschrieben...";
			link.l1 = "Lassen wir die Frage seiner Herkunft für einen Moment beiseite. Wo ist er, Abraham?! War er hier?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "Sh-sh... Ja, er war hier. Aber er ist gegangen. Er ist nicht mehr auf Isla Tesoro.";
			link.l1 = "Wofür ist er hierher gekommen? Was für ein Schiff hat er?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "Sein Schiff ist eine Galeone. Eine große Kriegsgaleone. Warum er hierher kam... Nun, er schnüffelte herum und stellte Fragen. Aber ich habe seine Gespräche belauscht, ja ja! Er suchte nach einem Charles de Maure. Ja, das ist es. Charles de Maure. Warte, das bist du, Charles de Maure! Er suchte nach dir, Kumpel.";
			link.l1 = "Weißt du wofür?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "Nun, definitiv nicht, um die Taverne zu besuchen und mit dir etwas Rum zu schlürfen. Er wollte dich fangen. Ja, ja! Fange dich! Du steckst tief in der Scheiße, Kapitän!";
			link.l1 = "Ich zweifle nicht daran...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "Und du? Warum suchst du nach ihm? Ach, ich verstehe, ich verstehe: um ihn zu töten! Töte ihn, töte diesen Bastard! Räche Blaze Sharp! Blaze war ein fantastischer Kerl. Ich erinnere mich an ihn, schon als Kind war er genau wie Nicholas.";
			link.l1 = "Wo ist Dichoso hin?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "Er war auf dem Weg nach Blueweld. Er sagte, dass Charles de Maure unter dem Schutz des Waldteufels gesucht werden soll. Aber er hat seine Leute hier gelassen... Warte. Ich glaube, du bist schon aufgefallen!";
			link.l1 = "Wer hat mich bemerkt?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "Dichosos Männer. Er hat befohlen, dich hier zu beobachten. Oh, ich weiß, ich weiß! Sei wachsam, Kapitän: Die Riffe von Isla Tesoro sind von Schiffen umgeben und sie warten dort auf deinen Kopf. Der Kapitän ist schlau wie ein Fuchs. Lass dich nicht hereinlegen.";
			link.l1 = "Ich werde es versuchen...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "Und noch etwas: hier, nimm mein Kavallerieschwert. Nimm es, nimm es. Du wirst es brauchen. Das ist das Schwert von Kapitän Barbarigo selbst. Es ist eine ausgezeichnete Klinge. Die Beste im Archipel. Sei nicht schüchtern, nimm es. Blaze Sharp soll gerächt werden!";
			link.l1 = "Danke dir, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Geh jetzt. Geh, du wirst beobachtet. Tu so, als wärst du schlau. Oder dumm. Es spielt keine Rolle. Sei einfach vorsichtig!";
			link.l1 = "Danke, Kumpel. Du kannst dir nicht vorstellen, wie sehr du mir geholfen hast. Viel Glück!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
