// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Wir haben nichts zu besprechen!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Bleichgesicht","Weißes Weib")+" will reden?","Du schon wieder, "+GetSexPhrase("Bleichgesicht","Weißes Squaw")+".",""+GetSexPhrase("Bleichgesicht mag das Reden. Er sieht aus wie eine Squaw.","Die weiße Squaw redet gern.")+"","Geister brachten mein bleichgesicht "+GetSexPhrase("Bruder","Schwester")+" zu mir.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ja.","Ja, ich schon wieder.","Sehr poetisch.","Ich freue mich auch, dich zu sehen.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Sag mal, warum bist du gekommen, Bleichgesicht?";
			link.l1 = "Ach, nichts Besonderes, wollte nur hören, was du zu sagen hast...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("Weißer Mann will reden?","Du schon wieder, Bleichgesicht?","Bleichgesicht spricht gerne.","Geister haben meinen bleichgesichtigen Bruder zu mir gebracht.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ja.","Ja, ich schon wieder.","Sehr poetisch.","Ich freue mich auch, dich zu sehen.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" hör zu, Sohn des Meeres.","Was willst du von "+npchar.name+", bleichgesicht?","Meine Ohren sind offen für deine Worte, Fremder.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Ich habe etwas für dich. Möchtest du mal schauen?","Möchtest du dir etwas wirklich Interessantes ansehen? Du wirst es sicher mögen...","Ich habe etwas, das dir gefallen wird, Kind des Dschungels. Willst du mal sehen?");
				link.l1.go = "gift";
			}
			link.l9 = "Oh, nichts Besonderes, ich wollte nur hören, was du zu sagen hast...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" will es sehen. Zeig es.",""+npchar.name+" ist interessiert. Zeige es mir.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Gib einen Spiegel.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Jetzt "+npchar.name+" kann sich nicht nur im Flusswasser betrachten! Danke, freundlicher Fremder!";
			link.l1 = "Sicher, jetzt kannst du dein Gesicht so viel bewundern, wie du möchtest...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! So wunderschön! Dieses Armband ist für "+npchar.name+"? Danke, freundlicher Fremder!";
			link.l1 = "Leg es auf deine dunkle Hand, Schönheit, du wirst umwerfend aussehen...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Was für ein schöner Ring? Es ist für "+npchar.name+", ja? Danke, freundlicher Fremder!";
			link.l1 = "Steck es an deinen Finger, und all deine Freunde werden eifersüchtig sein...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Diese wunderbaren grünen Perlen sind für "+npchar.name+"? So wunderschön! Danke, freundlicher Fremder!";
			link.l1 = "Schmücke deinen Hals damit, Tochter des Urwalds. Jeder wird dich bewundern...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh, was für ein schöner grüner Ring! Ist das ein Geschenk für "+npchar.name+"? Danke, freundlicher Fremder!";
			link.l1 = "Es wird toll an deiner Hand aussehen, hübsche...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Wollte fragen "+npchar.name+" etwas, Sohn des Meeres?";
				link.l1 = "Du hast Recht, hübsche Dame. Ich und meine furchtlosen Krieger gehen in den Dschungel, zur spanischen Siedlung in den Bergen und wir suchen einen Führer. Ich werde dem Mann selbst und auch seiner Frau großzügig sein. Ich habe viele Reichtümer: schöne Gewehre, magische Gläser, Spiegel, Halsketten, Armbänder und Ringe. Vielleicht kann dein Mann der Führer sein, den wir suchen?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Grüße, Sohn des Meeres. Ich bin Kumwana, der Häuptling des Schildkrötenklans der Locono-Leute. Was führt dich in mein Dorf?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ich habe dir ein Geschenk mitgebracht, Chef. Schau mal, es wird dir gefallen.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Häuptling, ich bin gekommen, um deine Hilfe zu bitten. Ich möchte eine spanische Siedlung namens Merida erreichen, sie liegt inmitten der Berge in deinem Dschungel, Problem ist, ich weiß nicht, wie ich dorthin komme.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "Das ist sehr gut für dich, Sohn des Meeres, den Weg dorthin nicht zu kennen. Er führt durch einen Wald, ein Land des furchtlosen Stammes der Capong. Wahre Jaguare sind sie, oh-ey! Ich gehe nie an diesen spanischen Ort. Mein Volk - friedliches Volk, wir gehen nicht ins Land der Capong. Kumwana kann dir keinen Rat geben. Der Weg ist zu gefährlich.";
			link.l1 = "Aber die Spanier haben einen Weg dorthin gefunden! Und ich habe keine Angst vor diesen Capongs...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Aber du solltest. Sie sind grausame Menschen. Sie haben viele meiner Leute im Wald getötet. Kumwana hat alles gesagt.";
			link.l1 = "Nun, Scheiße...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Du schon wieder, Sohn des Meeres. Was willst du zu Kumwana sagen?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ich habe dir ein Geschenk mitgebracht, Chef. Schau mal, es wird dir gefallen.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Die Hoffnung, Merida zu finden, ist immer noch bei mir...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono freuen sich immer, gute Freunde zu sehen.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Schenke eine Pistole."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Schenke einen Kompass.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Schenke ein billiges Spionglas.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Schenke ein gewöhnliches Spionglas."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Schenke ein anständiges Spionglas."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Was für eine hübsche bleiche Waffe! Kumwana akzeptiert dein Geschenk! Du auch, Sohn des Meeres, akzeptiere ein Geschenk von Kumwana und dem Locono Volk.";
			link.l1 = "Ich bedanke mich, Häuptling!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magisches Amulett der bleichgesichter! Kumwana akzeptiert dein Geschenk! Du auch, Sohn des Meeres, akzeptiere ein Geschenk von Kumwana und dem Locono Volk.";
			link.l1 = "Ich bedanke mich, Hauptmann!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magische Röhre der Bleichgesichter! Kumwana akzeptiert dein Geschenk! Du auch, Sohn des Meeres, akzeptiere ein Geschenk von Kumwana und dem Locono Volk.";
			link.l1 = "Ich bedanke mich, Häuptling!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Magische Röhre der Bleichgesichter! Kumwana akzeptiert dein Geschenk! Du auch, Sohn des Meeres, akzeptiere ein Geschenk von Kumwana und dem Locono Volk.";
			link.l1 = "Ich bedanke mich, Häuptling!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Magische Röhre der Bleichgesichter! Kumwana nimmt dein Geschenk an! Auch du, Sohn des Meeres, nimm ein Geschenk von Kumwana und dem Volk der Locono an.";
			link.l1 = "Ich bedanke mich, Häuptling!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Was führt dich zu unserem Dorf, Sohn des Meeres?";
			link.l1 = "Häuptling, ich bin gekommen, um um Ihre Hilfe zu bitten. Ich möchte eine spanische Siedlung namens Merida erreichen, sie liegt mitten in den Bergen in Ihrer Selva, das Problem ist, ich weiß nicht, wie ich dorthin komme. Vielleicht könnten Sie mir einen tapferen Krieger zur Verfügung stellen, der uns den Weg dorthin zeigt?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Gefährlicher Weg, gefährlich. Der Weg führt durch einen Wald, ein Land des furchtlosen Stammes der Capong. Wahre Jaguare, sie sind, oh-ey! Ich gehe nie an diesen spanischen Ort. Mein Volk - friedliches Volk, wir gehen nicht in das Land der Capong.";
			link.l1 = "Ich muss wirklich nach Merida kommen. Kumwana, bitte fragen Sie Ihre Männer, vielleicht ist jemand bereit, meiner Einheit beizutreten? Meine Krieger sind erfahren, gut bewaffnet und fürchten nichts, nicht einmal den Teufel. Wir werden den Führer schützen und ihn großzügig belohnen, wenn alles vorbei ist.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Sehr gut, Sohn des Meeres. Ich werde einen Kreis von Kriegern versammeln und ihnen von deinen Wünschen erzählen. Sieh mich morgen nach der Morgendämmerung.";
			link.l1 = "Ich bedanke mich, Chef!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Du wieder, Sohn des Meeres. Was möchtest du zu Kumwana sagen?";
			link.l1 = "Noch nichts, Chef.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Hör zu, Kumwana. Meine Leute und ich müssen unbedingt den Fluss überqueren und diese verfluchte kleine Stadt erreichen. Lass mich dir erklären, wie entscheidend das für uns ist.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Meine Jäger haben dich bereits informiert, dass...";
			link.l1 = "Es besteht keine Notwendigkeit, dich selbst zweimal zu wiederholen, Kumwana. Aber schau nach draußen - und überschätze deine Fähigkeiten nicht. Meine tapferen Kerle, die hierher gekommen sind für spanische Steine, sind in deinem Dorf verstreut. Und ihre Geduld geht zur Neige. Und was passiert, wenn sie endgültig erschöpft ist, ist es besser für dich nicht zu wissen - glaub mir.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Halt's Maul und hör zu, du rotgesichtiger Affe. Mein Volk kann viel schrecklicher sein als diese verdammten Kapongs. Lass dich nicht davon täuschen, dass wir jetzt so nett sind. Ich gebe dir eine einfache Wahl: Entweder du findest innerhalb von vierundzwanzig Stunden einen Führer, oder wir fesseln euch alle und schicken euch durch den Dschungel vor unserem Trupp. Wenn du uns in die falsche Richtung führst, wirst du selbst in den Sümpfen umkommen oder gefesselt gegen die Kapongs kämpfen. Kapiert?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, ich brauche diesen Führer. Wir haben einen langen Weg hinter uns und ich möchte meinen Leuten wirklich nicht sagen, dass es umsonst war.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana hat schon gesagt, keiner der Lokono will mit dem Bleichgesicht gehen.";
			link.l1 = "Und du kannst nichts dagegen tun? Frag jemanden persönlich. Befehl, schließlich. Bist du der Chef oder nicht?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Der Häuptling zwingt den Indianer nicht. Der Häuptling regiert und will Frieden für sein Volk. Die Indianer wissen - der Kapong wird sehen, dass die Lokono die Bleichgesichter bringen. Ihre Köpfe sollen von Kanaima erobert werden. Sie kommen, um sich an den Lokono zu rächen. Kapong - um zu töten. Fangt die Lokono, macht Sklaven.";
			link.l1 = "Und wer hat Eure Köpfe erobert? Welcher Geist oder Dämon macht die Indianer zu solch feigen Maden? Nun, vielleicht muss ich wirklich den Feldzug gegen Merida aufgeben. Aber denkt daran, Häuptling. Immer wenn ich gefragt werde, was ich über die Lokono weiß, werde ich unweigerlich antworten - dass sie ein Stamm wertloser Feiglinge sind. Angeführt von einem Anführer, der genauso feige und kurzsichtig ist wie sie, dessen Gesicht von einer Grimasse des Horrors verzerrt ist bei der bloßen Erinnerung an die Kapongs. Ihr werdet weder Ruhm unter den Indianern erlangen, noch Respekt bei uns, den Bleichgesichtern.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Bleichgesicht kennt die Bräuche der Indianer nicht...";
			link.l1 = "Ich weiß genug, um zu wissen, wen die Indianer einen Feigling nennen und wer ein tapferer Krieger ist. Lebewohl, Kumwana. Und merke dir meine Worte. Du bist ein feiger und kurzsichtiger Herrscher.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Warum drohst du mir so? Wir denken, du bist gut...";
			link.l1 = "Ich bin zufrieden, solange du kooperierst, verstanden? Du hast einen Tag Zeit. Und glaub mir, meine Leute werden tun, was ich befehle. Wir sind stärker. Und wenn du daran zweifelst... Ich habe deine Frau gesehen. Und deine Töchter. Ich denke, du hast die Botschaft jetzt verstanden.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Warum bedroht ihr mich so? Wir denken, ihr seid gut...";
			link.l1 = "Ich bin gut, solange du kooperierst, verstanden? Du hast einen Tag Zeit. Und glaub mir, meine Leute tun alles, was ich befehle. Wir sind stärker. Und wenn du daran zweifelst... Ich habe deine Frau gesehen. Und deine Töchter. Ich denke, du hast die Botschaft jetzt verstanden.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana versteht, bleiches Gesicht. Im Dorf gibt es einen Jäger namens Tagofa. Vielleicht kann er dich zur Siedlung führen...";
			link.l1 = "Ich komme in vierundzwanzig Stunden zurück. Charlie Prince hat nichts mehr hinzuzufügen, Wilder.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Sohn des Meeres, du bist es. Kumwana hat mit Kriegern der Locono gesprochen.";
			link.l1 = "Und? Hast du einen Freiwilligen?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Wir haben ein paar Jäger hier, die dort gewesen sind. Aber sie fürchten die Capongs, die Jaguare sind auf Kriegspfad. Sie gehen nicht, sie sagen Capong tötet deine Einheit. Sie fürchten nicht die Bleichgesichter.";
			link.l1 = "Meine Krieger sind viel besser als alle von denen! Ein Teil meiner Einheit hat ein Leben lang im Dschungel verbracht! Wir sind keine Amateure!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Es tut mir leid, Sohn des Meeres. Meine Jäger fürchten sich, Capongs sind gefährlich, sehr, sehr.";
			link.l1 = "Gut, dann können sie vielleicht erklären, wie man dorthin kommt? Im Detail.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Um dorthin zu gelangen, solltest du den Fluss entlang segeln und dann an einem besonderen Ort an Land gehen. Wenn es der falsche Ort ist, wirst du im Sumpf landen und sterben. Unser Dschungel ist voller Gefahren. Du wirst den Ort nicht alleine finden, Sohn des Meeres.";
			link.l1 = RandSwear()+"Und was soll ich dann tun? Wie überzeuge ich eure Jäger?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana sagt nichts mehr, Sohn des Meeres.";
			link.l1 = "Gut...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Mein Mann Tagofa ist der beste Jäger des Stammes. Oh-ey!"+npchar.name+" ist stolz auf ihren Ehemann. "+npchar.name+" geht oft mit Tagofa in Selva. Geh weit weg. Tagofa weiß, wo die spanische Siedlung ist.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Kennt Tagofa den Weg zur spanischen Stadt, die die Bleichgesichter Merida nennen?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Nun, nun... Kennt Tagofa den Weg in die spanische Stadt?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Mein Mann geht nicht in den Dschungel, Sohn des Meeres. Er fängt Fische. Guter Fischer, oh-ey!","Mein Mann guter Jäger, oh-ey, aber er geht nicht tief in den Dschungel."),RandPhraseSimple("Ein Jaguar hat meinen Mann auf der Jagd verwundet. Jetzt sitzt er im Dorf, macht Pfeile, oh-ey!","Sechs Monde zuvor haben drei Capongs meinen Mann angegriffen. Jetzt geht er nicht mehr weit vom Dorf jagen. Niemals! oh-ey!"));
				link.l1 = LinkRandPhrase("Schade...","Zu schade...","Wie schade..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa ist in diesem Dschungel aufgewachsen. Er kennt jeden Baum und jeden Stein in der Umgebung!";
			link.l1 = "Ich werde dir und Tagofa viele Geschenke geben, wenn er uns dorthin bringt. Schmuck, Waffen, alles. Alles was du willst. Innerhalb des Vernünftigen, natürlich, he-he. Wie kann ich mit deinem Ehemann reden?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa wird nicht mit dem Bleichgesicht gehen. Tagofa wird im Dorf bleiben. Geh jagen. Kämpfe nicht mit dem Kapong.";
			link.l1 = "Er wird nicht mit den Kapong kämpfen müssen. Sobald er sie sieht, kann er sich verstecken. Nur mein Volk wird kämpfen.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Nein, yalanaui. Der bleiche Gesicht hält nie sein Wort. Der bleiche Gesicht spricht - und das Wort fliegt sofort in die Leere. Die Kapong werden Tagofa töten und dann zu unserem Dorf kommen, die Lokono töten.";
			link.l1 = "Glaubst du, dass diese Kapongs alles sind, worum du dich sorgen musst? Du liegst sehr falsch...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("Die Indianer respektieren dich nicht "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu, um in das Gesicht des Bleichgesichts einzutreten! Hayami spricht nicht mehr mit Yalanaui.";
			link.l1 = "Nun-nun...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa ging vor einem Tag auf die Jagd. Versprach morgen zurückzukommen, wenn die Sonne schläft. Komm morgen, Sohn des Meeres, ich werde mit Tagofa in dieser Hütte sein, geh im Dorf nach rechts. Ich frage ihn, ob er mit dir geht oder nicht.";
			link.l1 = "Sag Tagofa, dass ich ihm die hübscheste Pistole schenken werde. Und du, ich werde dich mit vielen Juwelen beschenken.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono vertrauen den Yalanaui nicht. Yalanaui täuschen den Indianer, machen den Indianer zum Sklaven. Aber Lokono hört deinen Namen, Bleichgesicht. Mein Vertrauen gehört dir. Komm morgen nach Sonnenuntergang, Sohn des Meeres. Ich werde bei Tagofa in dieser Hütte sein. Ich werde ihn fragen, ob er mit dir gehen wird oder nicht.";
			link.l1 = "Sag Tagofa, dass ich ihm meine schönste Pistole geben werde. Und für dich habe ich viele Juwelen.";
			link.l1.go = "hayamee_2";
			notification("Die Indianer respektieren dich "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" freut sich, einen Sohn des Meeres zu sehen. Tagofa ist zurückgekehrt. Aber er hat zu viel Kasheeri getrunken und schläft. Weck ihn nicht auf, Tagofa ruht. Ich werde reden.";
			link.l1 = "Sehr gut, "+npchar.name+". Wird Ihr Mann uns nach Merida führen?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa hat zugestimmt, deine Krieger durch den Dschungel zum spanischen Dorf zu führen. Aber es gibt Bedingungen...";
			link.l1 = "Welche sind das?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Du beschützt Tagofa vor den Capong Kriegern. Tagofa kämpft nicht gegen Spanier, nicht gegen Capong. Wenn er in Gefahr ist, wird er weglaufen und niemand wird ihn finden, er ist der beste Locono Jäger.";
			link.l1 = "Ich verstehe. Sie machen sich Sorgen um Ihren Mann, das ist verständlich. Ich verspreche Ihnen, dass wir uns alleine um all diese Capongs kümmern werden.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa will Geschenke vom Sohn des Meeres: eine kleine, um viele Steine zu schießen und eine große, um einen Stein zu schießen, die hübschen. Er möchte auch Kugeln für jede Waffe: so viele wie die Finger beider Hände dreimal.";
			link.l1 = "Wer! Dein Mann kennt sich also mit Gewehren aus, hm? Sehr gut. Was noch?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Und Tagofa will ein schönes magisches Auge der Bleichgesichter.";
			link.l1 = "Ein Spionglas? Gut. Noch etwas?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Kein weiteres für Tagofa. "+npchar.name+" will hübsche Dinge. Goldring mit großem roten Stein und Perlen aus vielen vielen grünen Steinen. "+npchar.name+" habe es auf der weißen Mary in Maracaibo gesehen.";
			link.l1 = "Ein goldener Ring mit Rubin- und Jadeperlen?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Nicht Jade. Es glänzt und weiße Männer schätzen es.";
			link.l1 = "Smaragd? Smaragdperlen?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" weiß etwas über Juwelen! Sehr gut, du bekommst es.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Bring alle Dinge zu "+npchar.name+" zusammen, Sohn des Meeres. Dann wird Tagofa dich und deine Krieger führen. Vergeude keine Zeit, in einer halben Mondphase werden Tagofa und ich ins Nachbardorf gehen. Für einen hohen Tag. Jetzt geh, "+npchar.name+" will schlafen.";
			link.l1 = "Ich werde dich nicht zu lange warten lassen. Auf Wiedersehen.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Du hast was gebracht "+npchar.name+" und Tagofa fragte?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Ja. Alles ist gemäß Ihrer Liste.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Nein, ich bin immer noch dabei.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" ist glücklich, Sohn des Meeres. Ich nenne jetzt Ehemann. Er geht mit dir. Aber erinnere dich an das, was du versprochen hast "+npchar.name+"!";
			link.l1 = "Ja-ja, ich erinnere mich an alles. Ich werde ihn sicher aufbewahren, mach dir keine Sorgen.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Stecke deine Waffe weg, Bleichgesicht, oder wir zwingen dich dazu!";
			link.l1 = LinkRandPhrase("Gut.","Gut.","Mach dir keine Sorgen, ich stecke es weg...");
			link.l1.go = "exit";
		break;  

	}
}
