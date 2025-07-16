void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Glückwunsch! Das ist ein Fehler. Kontaktiere Jason und sag ihm, wie und wo du diesen gefunden hast. Frieden!";
			link.l1 = "Ich werde es sofort tun!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Sei gegrüßt, Sohn des Meeres! Ich habe von dir gehört. Du kannst ruhig auf unserem Land gehen.",""+npchar.name+" begrüßt Sie, bleichgesichtiger Bruder. Wir freuen uns, Sie als unseren Gast zu sehen.","Ich grüße dich, tapferer bleichgesichtiger Krieger! "+npchar.name+" freut sich, einen Freund der Indianer zu treffen. Geh in Frieden!");
				link.l1 = RandPhraseSimple("Und sei gegrüßt, rothäutiger Bruder! Wünsche dir eine gute Jagd!","Grüße, tapferer Krieger! Mögen die Götter dich und deine Familie segnen!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Ich habe etwas, was für dich interessant sein könnte, rothäutiger Bruder. Lust zu handeln?","Ich kann Ihnen anbieten, etwas Interessantes zu kaufen, tapferer Krieger. Möchtest du handeln?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Halt, bleichgesicht! Mit welchem Recht gehst du auf meinem Land?","Halt, weißer Mann! Du bist auf dem Land meiner Vorfahren und meinem Land!","Halt, bleichgesicht! Du gehörst nicht zu meinem Land");
				link.l1 = RandPhraseSimple("Dein Land? Verzieh dich, du rotgesichtiger Abschaum!","Schau ihn dir an - ein sprechender Affe! Verschwinde jetzt!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Ich komme in Frieden, rotgehäuteter Krieger. Wir sollten nicht umsonst kämpfen.","Ich bin kein Feind für dich und dein Land, Krieger. Ich bin in Frieden gekommen.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Ich bin gekommen, um mit dir zu handeln, nicht um zu kämpfen.","Ich kämpfe nicht mit Indianern. Ich handle mit ihnen.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Du bedauerst es, geboren zu sein, bleichgesichtiger Hund... Ich schneide dein Herz heraus und brate es am Feuer!","Ich zwinge dich Steine zu fressen, bleichgesichtiger Hund! Wir lachen, während du auf deinen Knien um den Tod bettelst, weißer Tölpel!");
			link.l1 = RandPhraseSimple("Du kannst immer noch nicht dein stinkendes Maul halten, bemalter Vogelscheuche? Ich werde dich zurück in den Dschungel treiben, aus dem du gekommen bist!","Du wagst es, mir zu drohen, Abschaum?! Nun, jetzt wirst du wieder auf den Baum klettern, von dem du gerade heruntergekommen bist!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Ich höre, deine Stimme spricht die Wahrheit. Wir ziehen unsere Äxte nicht gegen dich an diesem Tag. Geh in Frieden, Bleichgesicht.","Bleichgesicht bringt selten Frieden, aber ich sehe in deinen Augen, dass du die Wahrheit sprichst. Geh jetzt.");
			link.l1 = RandPhraseSimple("Eine weise Entscheidung, Krieger. Viel Glück für dich.","Ich bin froh, dass wir zu einem Verständnis gekommen sind, Krieger.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Du lügst, bleichgesichtiger Hund! Du bist hierher gekommen um Indianer zu töten! Bist du bereit für den Kampf, bleichgesicht?!","Du tötest Indianer. Weiße Zunge ist lügende Zunge. Ich schneide sie ab und brate sie über dem Feuer!");
			link.l1 = RandPhraseSimple("Nun, Kumpel, mach mir dann keine Vorwürfe. Gott weiß, ich habe versucht, es zu vermeiden...","Nun, du hast danach gefragt, Krieger.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Handel? Wir brauchen Waffe des weißen Mannes. Eine Hand feurige Waffe des bleichgesichts! Für sie tauschen wir unsere Waren! Hast du feurige Waffe zum Tausch?";
				link.l1 = "Hmm. Ich mache. Und was wirst du mir im Austausch geben?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Du Schuft! Und dann schießt du mit meinen Pistolen auf die Kolonisten? Nein, das wird nicht passieren! Was euch, Schakale, betrifft, ich werde euch jetzt alle niederhauen...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Du hast nicht, was wir wollen, bleichgesicht... Du wirst unsere Kriegstrophäe sein!";
				link.l1 = "Versuche es, wenn du dich traust, Vogelscheuche...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Wir handeln nicht mit bleichgesichtigen Hunden. Wir töten und nehmen!","Wir sind keine dreckigen Miskito oder Arawaks, wir handeln nicht mit Bleichgesichtern! Wir töten sie und holen uns Kriegstrophäen!");
			link.l1 = RandPhraseSimple("Nun, dann versuche mich auszurauben, Schurke!","Zuerst musst du mir mein Säbel abnehmen, du Abschaum!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Du zeigst, was du hast, und wir sagen, was wir dafür geben.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "He, ho! Wir geben dir dafür "+sText+".";
			link.l1 = "Abgemacht!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "He-ho! Listige Waffe... Wir geben sie dir dafür "+sText+".";
			link.l1 = "Abgemacht!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "He, ho! Mächtige Waffe! Viele-viele Feinde töten! Wir geben sie dir dafür "+sText+".";
			link.l1 = "Abgemacht!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Heu-ho! Furchterregende Waffe... Wir geben dir dafür "+sText+".";
			link.l1 = "Abgemacht!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Schöne und mächtige Waffe! Viele-viele Feinde töten! Wir geben sie dir dafür "+sText+".";
			link.l1 = "Abgemacht!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Heu-ho! Praktische Waffe... Wir geben dir dafür "+sText+".";
			link.l1 = "Handel!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nein. Auf keinen Fall.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Gut. Hier deine Waren. Wir handeln nicht mehr. Komm später. Bessere feurige Waffe, mehr geben wir dafür. Jetzt geh!";
				link.l1 = "Auf Wiedersehen, rothäutiger Krieger.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Gut. Hier sind deine Waren. Hast du noch mehr feurige Waffen zum Handeln?";
				if (CheckCaribGuns())
				{
					link.l1 = "Ich habe. Wirst du kaufen?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Nein. Das nächste Mal bringe ich mehr.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Bring. Bessere feurige Waffe mehr geben wir dafür. Jetzt geh!";
			link.l1 = "Auf Wiedersehen, Krieger...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Dann nehmen wir alles kostenlos, Bleichgesicht!";
				link.l1 = "Du kannst es versuchen...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Heil, weißer Mann. Was brauchst du in unserem Dschungel?","Unser Dschungel ist sehr gefährlich. Was machst du hier?","Was bringt dich hierher, tapferes Bleichgesicht?");
			link.l1 = RandPhraseSimple("Ich bin nur vorbeigekommen, mein rotgesichtiger Freund. Ich glaube, auf diesem Weg ist genug Platz für uns beide?","Grüße, Sohn des Dschungels! Ich bin geschäftlich hier und kämpfe nicht gegen Indianer.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("Und warum müssen Sie das wissen? Geh deinen eigenen Weg und halte dich von Ärger fern!","Geh deinen eigenen Weg, Rothäutiger. Ich habe keine Zeit, mit dir zu sprechen.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Wir friedliche Leute. Wir nicht Feinde mit weißen Männern. Geh, aber sei vorsichtig auf unserem Land!","Ich freue mich, bleichgesichtigen Freund der Indianer zu treffen. Geh in Frieden, Sohn des Meeres!");
			link.l1 = RandPhraseSimple("Viel Glück auch dir, Sohn des Dschungels...","Auf Wiedersehen, rothäutiger Freund.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Wir friedliche Jäger. Aber wir dulden es nicht, wenn Bleichgesichter so auf unserem Land reden!","Wir kämpfen nicht mit weißen Männern, aber wenn weiße Männer uns beleidigen, antworten wir wie unsere Vorfahren es uns gelehrt haben!");
			link.l1 = RandPhraseSimple("Du kannst immer noch nicht dein stinkendes Maul halten, bemalter Vogelscheuche? Ich werde dich zurück in den Dschungel treiben, aus dem du gekommen bist!","Du wagst es, mir zu drohen, Abschaum?! Jetzt wirst du den Baum wieder hochklettern, von dem du gerade heruntergekommen bist!");
			link.l1.go = "exit_fight";
		break;
	}
}
