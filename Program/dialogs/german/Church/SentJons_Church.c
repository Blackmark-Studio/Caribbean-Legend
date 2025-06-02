// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hast du Fragen, "+GetSexPhrase("mein Sohn","meine Tochter")+"?","Frag ruhig, ich höre zu..."),"Ich höre zu, sprich jetzt, "+GetSexPhrase("mein Sohn","meine Tochter")+"...","Zum dritten Mal, "+GetSexPhrase("mein Sohn","meine Tochter")+", frag mich, was brauchst du?","Ein Geistlicher hat viel Arbeit und du lenkst mich ab, "+GetSexPhrase("mein Sohn","meine Tochter")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt, Padre..."),"Ich habe nichts zu sagen, Entschuldigt mich.","Ich werde fragen haben, aber nicht jetzt. Verzeiht mir, Vater.","Verzeihen Sie mir, heiliger Vater...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Heiliger Vater, ich möchte über Thomas Morrisons Tochter sprechen.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Heiliger Vater, Thomas bat mich auszurichten, dass er Buße tun, sich guten Taten widmen und der Gemeinde eine neue Glocke stiften wird – koste es, was es wolle.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Sprich, mein Kind, ich höre dir zu.";
			link.l1 = "Ich weiß, dass Ihr gegen die Hilfe der Zigeunerin für das Mädchen seid. Doch kann man einen Vater wirklich dazu zwingen, auch nur die kleinste Chance zur Rettung seiner Tochter abzulehnen? Ihre Methoden mögen zweifelhaft erscheinen, doch sie besitzt Wissen, das helfen könnte.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Mein Sohn, nur der Herr kann das Mädchen heilen. Der Glaube an seinen Plan führt uns durch Prüfungen. Wenn Thomas fleißig betet, dem Wort Gottes folgt und großzügig der Kirche spendet, wird der Herr sein Gebet erhören und Gnade zeigen.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Vertrauenswürdig) Doch selbst Ihr müsst anerkennen, dass der Herr durch Menschen wirkt. Was, wenn die Zigeunerin nur ein Werkzeug in seiner Hand ist? Was, wenn sein Plan so tief ist, dass wir ihn nicht begreifen können? Gottes Wege sind unergründlich, nicht wahr?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Vertrauenswürdig", "Trustworthy");
			}
			else
			{
				link.l1 = "Ihr zwingt einen Vater, zuzusehen, wie seine Tochter langsam dahinsiecht, anstatt ihm zu erlauben, sie zu retten. Ist das Barmherzigkeit?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Fähigkeit nicht freigeschaltet", "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Eure Worte, Kapitän, sind wahrlich weise. Doch ich kann nicht zulassen, dass Ketzerei ins Herz unserer Gemeinde dringt und den Glauben eines der treuesten Söhne erschüttert.";
			link.l1 = "Nichts könnte seinen Glauben mehr erschüttern als der Tod seiner Tochter. Wenn Ihr ihm erlaubt, alle Mittel zu nutzen – selbst jene, die als Sünde gelten könnten –, wird sein Glaube nicht schwächer, sondern stärker denn je.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Aber... welches Beispiel gibt das dem Rest der Gemeinde?";
			link.l1 = "Ein Beispiel dafür, dass die Kirche nicht blind straft, sondern zur wahren Reue führt. Lehren uns die Schriften nicht, dass aufrichtige Reue und gute Taten Sünden tilgen können? Ein großzügiges Opfer an die Kirche kann der erste Schritt zur Sühne sein.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Vielleicht habt Ihr recht, Kapitän. Ich bin bereit, Thomas diese Chance zu geben. Aber wenn er vom rechten Weg abkommt, wird auch Ihr Verantwortung tragen! Was die Spenden angeht – die Kirche braucht kein Reichtum. Außer... die Glocke wurde beim Angriff der Spanier beschädigt...";
			link.l1 = "Ich werde Thomas Eure Worte übermitteln. Danke für das Gespräch, Heiliger Vater. Gott schütze Euch.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "Das ist keine Gefühllosigkeit, Kapitän, das ist Glaube. Wir überlassen das Schicksal des Mädchens nicht dem Zufall, sondern legen es in Gottes Hände. Wenn Thomas betet, glaubt und geduldig wartet, bin ich sicher, der Herr wird unsere Gebete erhören und sie heilen.";
			link.l1 = "Ihr wisst doch, dass selbst die Elite der Insel – einschließlich des Gouverneurs – die Hilfe der Zigeunerin in Anspruch genommen hat. Und sie wurden nicht exkommuniziert. Warum also seid Ihr bei Thomas so streng?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Natürlich weiß ich das, mein Sohn. Aber sie sind verlorene Seelen, die das wahre Licht Gottes nicht erkannt haben. Thomas jedoch ist eine Stütze unserer Gemeinde, einer der besten. Ihn vom Glauben abbringen zu lassen, würde die ganze Kirche gefährden, und das kann ich nicht zulassen.";
			link.l1 = "Also verweigert Ihr ihm selbst die kleinste Hoffnung? Ist das der Weg der Rechtschaffenheit?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "Was Ihr Rettung nennt, könnte der direkte Weg ins Verderben sein. Ich weiß das aus eigener Erfahrung. Eine ähnliche Heilerin behandelte einst meine Nichte – sie starb unter Qualen. Nur Gott weiß, ob ihre Seele durch die Rituale verdammt wurde. Versucht also nicht, mich zu überzeugen – es ist sinnlos.";
			link.l1 = "Wenn das Eure endgültige Entscheidung ist, werde ich nicht weiter diskutieren. Gott schütze Euch.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddQuestRecord("DWH", "4");

			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Sehr gut, mein Sohn. Die neue Glocke wird ein Symbol seiner Treue zu Gott und der Kirche sein. Er soll tun, was nötig ist, aber nicht vergessen: Das Auge des Herrn sieht alles, und nichts auf dieser Welt entgeht seinem Willen.";
			link.l1 = "So sei es, Heiliger Vater. Auf Wiedersehen.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";

			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
