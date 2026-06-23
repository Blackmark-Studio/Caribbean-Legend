// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Natürlich, Helen. Was ist los?","Ach, endlich daran erinnert, was du wolltest?","Bist du sicher, dass es dir gut geht? Du fängst an, mir Sorgen zu machen. Vielleicht solltest du einen Arzt aufsuchen?","In Ordnung, Helen. Schlaf ein bisschen, hol dir frische Luft - kurz gesagt, mach eine Pause. Dann komm zurück. Mhm?","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nein, eigentlich nichts.","Nein, nein, Entschuldigung, dass ich Sie belästige.","Du hast wahrscheinlich recht...","Ja, du hast wahrscheinlich recht. Das ist das Beste, was man tun kann.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"..., Freund.","Über den ganzen Tag hinweg ist dies das dritte Mal, dass du von irgendeiner Frage redest...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Hör zu, "+npchar.name+", wer ist Jan Svenson und wie kann ich ihn finden?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Hör zu, ist hier in dieser Stadt ein Alchemist angekommen, ein Arzt? Er ist Italiener, etwa dreißig Jahre alt, sein Name ist Gino Gvineili. Haben Sie etwas darüber gehört?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "Dies ist das erste Mal, dass ich einen Mann treffe, der nicht weiß, wer der Waldteufel ist. Diesen Spitznamen hat ihm die spanische Regierung gegeben und sie haben vor fünfzehn Jahren einen ganzen Sack voll Gold für den Kopf dieses Freibeuters von Providence Island angeboten! Ja, die Jahre fliegen vorbei... Die Leute haben bereits begonnen, unseren Jan zu vergessen. Vielleicht ist es wirklich Zeit für ihn, sich auszuruhen.";
			link.l1 = "Ich bin erst kürzlich hier angekommen und ich weiß nicht viel...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Wenn du dich für die Vergangenheit interessierst, kann ich dir ein Geschichtsbuch verkaufen. Viele würden ein Vermögen dafür geben, aber ich...";
			link.l2 = "Geben Sie mir nicht die Ausflüchte! Ich habe Ihnen eine Frage gestellt. Ich wiederhole. Wo wohnt Jan Svenson? Ich habe ein ernstes Gespräch mit ihm.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Er wohnt in einer Villa gegenüber der Residenz unseres Bürgermeisters, neben dem Brunnen. Aber momentan durchlebt er schwere Zeiten und ich würde nicht empfehlen, ihn zu belästigen, es sei denn, es ist von größter Wichtigkeit.";
			link.l1 = "Warum das?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Sein Lieblingsmädchen Helen, auch bekannt als Rumba, die Tochter seines verstorbenen alten Freundes Shawn McArthur, ist verschwunden. Ruhe in Frieden, alter Mann... Jan behandelt die junge Teufelin als seine eigene Tochter, da er keine eigenen Kinder hat. Aber das Mädchen ist zusammen mit ihrer Schoner 'Regenbogen' und der ganzen Crew verschwunden\nIch fühle mich schlecht für das Mädchen. Eine seltene Schönheit, auch schlau. Heiß und feurig wie Feuer, darum haben sie sie Rumba genannt! Ihr Vater hat ihr alles beigebracht, was er wusste, sie hat das Schiff geerbt und jeder einzelne Besatzungsmitglied blieb auf ihrer Seite. Sogar die ältesten Seewölfe erkannten sie als Kapitänin an...";
			link.l1 = "Eine Piratenlady? Was könnte mit ihr passiert sein?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Wer weiß... Eine Woche ist nicht so lang, aber MacAthur's Witwe ist sicher, dass ihrer Tochter etwas Schlimmes passiert ist und sie hat Svenson davon überzeugt. Er hat seine Leute zusammengetrommelt und hat selbst angefangen zu suchen, bisher ohne Erfolg. 'Regenbogen' und ihre Crew sind einfach verschwunden\nIch kann dir für tausend Achtstücke sagen, wo du Gladys finden kannst.";
			if (int(pchar.money) >= 1000)
			{
				link.l1 = "Dein Wissen ist ziemlich teuer, aber du hast mein Interesse geweckt. Hier ist dein Geld. Wo finde ich sie?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Mach dir keine Sorgen. Ich werde es selbst regeln, wenn ich es brauche. Tschüss, danke für die Geschichte!";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Ihr Zuhause ist neben dem Pier, links von der Anlegestelle. Aber sie ist wahrscheinlich nicht dort. Sie verbringt den ganzen Tag an den Mauern des Forts und hält Ausschau nach ihrer geliebten Tochter. Sie muss schon ihre Augen ausgeweint haben.";
			link.l1 = "Danke für die Geschichte! Tschüss, Kumpel!";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nein, habe ich nicht. Wir haben Kräuterkenner und Ärzte, aber keiner mit so einem Namen.","Das ist das erste Mal, dass ich so einen seltsamen Namen höre. Nein, der Mann, von dem du sprichst, hat uns noch nie besucht.","Wir haben hier überhaupt keine Alchemisten. Wir haben Ärzte, aber keinen mit einem so merkwürdigen Namen.");
			link.l1 = "Ich verstehe. Das ist schade. Ich werde weiter suchen!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
