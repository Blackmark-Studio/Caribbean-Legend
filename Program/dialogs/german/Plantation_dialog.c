// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, i, n;
	string sTemp;
	bool bOk;
	
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
			dialog.text = "Brauchen Sie etwas?";
			link.l1 = "Nein, das tue ich nicht.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// рабы
		case "plantation_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Ich bin so müde, ich falle schon um...","Kann nicht weiter so leben!"),RandPhraseSimple("Diese Arbeit bringt mich um.","Die Wachen wollen uns alle tot sehen!"));				
			link.l1 = RandPhraseSimple("Wie schade.","Es tut mir leid.");
			link.l1.go = "exit";				
		break;
		
		// рабы-пираты по пиратской линейке
		case "pirate_slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Hör zu, geh weg!","Verschwinde!"),RandPhraseSimple("Was willst du?!","Verschwinde hier verdammt noch mal!"));				
			link.l1 = RandPhraseSimple("Hm...","Nun...");
			link.l1.go = "exit";				
		break;
		
		// охрана - солдаты
		case "plantation_soldier":
            dialog.text = RandPhraseSimple(RandPhraseSimple("Geh, belästige den Leiter der Plantage","Störe die Sklaven nicht, Kumpel."),RandPhraseSimple("Meine Aufgabe ist es, diese faulen Bastarde zu motivieren.","Verdammt, heute ist es wieder zu heiß, wie immer..."));
			link.l1 = RandPhraseSimple("Ich sehe...","Tatsächlich...");
			link.l1.go = "exit";
		break;
		
		// охрана - протектор
		case "plantation_protector":
            if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					PlaySound("Voice\English\soldier_arest_1.wav");
    				dialog.text = RandPhraseSimple("Pirat?! Ergreift ihn!","Er ist ein Pirat! Angriff!");
					link.l1 = RandPhraseSimple("Pirat. Na und?","Heh, versuch es doch.");
					link.l1.go = "fight"; 
					break;
				}
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = RandPhraseSimple("Ho-ho, du segelst unter der Flagge von "+NationNameGenitive(sti(pchar.nation))+"! Ich denke, unser Kommandant wird sich freuen, mit Ihnen zu sprechen!","Nun, es riecht nach "+NationNameAblative(sti(pchar.nation))+" hier! Ein Spion?! Es ist Zeit, dass du mit unserem Kommandanten sprichst.");
				link.l1 = RandPhraseSimple("Zuerst schick ich dich in die Hölle!","Es ist Zeit, dass du mit meiner Klinge sprichst!");
				link.l1.go = "fight"; 
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						PlaySound("Voice\English\soldier_arest_1.wav");
						dialog.text = RandPhraseSimple("Pirat?! Ergreift ihn!","Er ist ein Pirat! Angriff!");
						link.l1 = RandPhraseSimple("Pirat!? Wo?","Heh, versuch es doch.");
						link.l1.go = "fight"; 
						break;
					}
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Wer bist du und was willst du hier?","Halt! Was ist dein Anliegen hier?");
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Ich möchte den Kopf dieses Ortes sehen, um Geschäfte zu besprechen. Ich habe eine Handelslizenz.";
						link.l1.go = "Licence";
					}
					else
					{
						link.l1 = "Ich möchte den Leiter dieses Ortes sehen, um Geschäfte zu besprechen.";
						if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50))) link.l1.go = "PegYou";
						else link.l1.go = "NotPegYou";
					}
					if (IsCharacterPerkOn(pchar, "Trustworthy"))
					{
						link.l2 = "(Vertrauenswürdig) Ehrenwerte Herren, ich bin hier für fairen und beiderseitig vorteilhaften Handel. Bitte, lassen Sie mich den Plantagenbesitzer sehen.";
						link.l2.go = "mtraxx_soldier_1";
						notification("Trustworthy", "Trustworthy");
					}
				}
				else
				{
					PlaySound("Voice\English\soldier_arest_4.wav");
					dialog.text = RandPhraseSimple("Wer sind Sie und was wollen Sie hier?","Halt! Was treibt euch hier?");
					link.l1 = "Ich will den Chef dieses Ortes sehen, um Geschäfte zu besprechen.";
					link.l1.go = "NotPegYou";
				}
			}
		break;
		
		case "Licence":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				PlaySound("Voice\English\soldier_arest_2.wav");
				dialog.text = "Eine Lizenz? Warte mal... Ha-ha, das ist lustig! Ich weiß, wer du bist. Du bist gesucht, Kumpel! Und die Belohnung für deinen Kopf ist sehr groß! Ergreift ihn!";
				link.l1 = RandPhraseSimple("Nun, in diesem Fall musst du einfach meiner Klinge begegnen!","Leck mich.");
				link.l1.go = "fight";	
				break;
			}
			if (iTemp == -1)
			{
				PlaySound("Voice\English\soldier_arest_1.wav");
				dialog.text = "Lassen Sie uns sehen... ha! Ihre Lizenz ist überfällig. Also folgen Sie mir, ich bringe Sie zum Kommandanten...";
				link.l1 = RandPhraseSimple("Scheiße! Ich denke, es ist Zeit, dass du meine Klinge triffst, Kumpel.","Ich glaube nicht...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			dialog.text = "Gut. Du kannst hereinkommen. Benimm dich und belästige die Sklaven nicht.";
			link.l1 = "Mach dir keine Sorgen, Freund.";
			link.l1.go = "plantation_exit";
		break;
		
		case "PegYou":
			PlaySound("Voice\English\soldier_arest_2.wav");
            dialog.text = "Geschäft? Ha-ha! Nun, das ist lustig! Du riechst nach "+NationNameAblative(sti(GetBaseHeroNation()))+" aus tausend Meilen! Es ist Zeit, dass du unseren Kommandanten triffst.";
			link.l1 = "Nein, ich denke, es ist Zeit, dass du meine Klinge kennenlernst.";
			link.l1.go = "fight";
		break;
		
		case "NotPegYou":
            dialog.text = "Gut. Du kannst reinkommen. Benimm dich und belästige die Sklaven nicht.";
			link.l1 = "Mach dir keine Sorgen, Freund.";
			link.l1.go = "plantation_exit";
		break;
		
		case "plantation_exit":
           DialogExit();
		   NextDiag.CurrentNode = "plantation_repeat";
		break;
		
		case "plantation_repeat":
            dialog.text = "Mach schon, geh weiter!";
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;
		
		// управляющий в Маракайбо // Addon 2016-1 Jason
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2") // belamour legendary edition 
			{
				dialog.text = "Was führen Sie hier im Schilde, Señor?";
				link.l1 = TimeGreeting()+", senor. Ich habe einen Geschäftsvorschlag für Sie. Ich habe Sklaven zu verkaufen. "+FindRussianQtyString(sti(GetSquadronGoods(pchar,GOOD_SLAVES)))+". Interessiert?";
				link.l1.go = "mtraxx";
				break;
			}
            dialog.text = "Was machen Sie hier, Senor?";
			link.l1 = "Einfach nur herumlaufen, wollte hallo sagen.";
			link.l1.go = "plantator_x";
		break;
		
		case "plantator_x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator";
		break;
		
		case "plantator_1":
			bOk = GetSquadronGoods(pchar, GOOD_COFFEE) >= 500 || GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500 || GetSquadronGoods(pchar, GOOD_COPRA) >= 500;
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup") && bOk) //пробуем выкупить Красавчика
			{
				dialog.text = "Sie schon wieder, Senor. Wie geht es Ihnen?";
				link.l1 = "Ich habe einen Geschäftsvorschlag für Sie. Sie produzieren Zucker und Kakao. Ich würde gerne Ihre Waren kaufen, aber nicht für Geld, ich kann meine eigenen Waren im Austausch anbieten. Vielleicht könnten wir einen Handel machen?";
				link.l1.go = "mtraxx_5";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_6" && bOk)
			{
				dialog.text = "Sie schon wieder, Señor. Wie geht es Ihnen?";
				link.l1 = "Ich habe einen Geschäftsvorschlag für Sie. Sie produzieren Zucker und Kakao. Ich möchte Ihre Waren kaufen, aber nicht für Geld, ich kann meine eigenen Waren im Austausch anbieten. Vielleicht könnten wir einen Handel machen?";
				link.l1.go = "mtraxx_5";
				break;
			}
            dialog.text = "Sie schon wieder, Senor. Wie geht es Ihnen?";
			link.l1 = "Danke, mir geht's gut.";
			link.l1.go = "plantator_1x";
		break;
		
		case "plantator_1x":
           DialogExit();
		   npchar.dialog.currentnode = "plantator_1";
		break;
		
		case "mtraxx":
			// belamour legendary edition возможность обмануть плантатора -->
			if(GetSquadronGoods(pchar, GOOD_SLAVES) >= 50 || CheckCharacterPerk(pchar, "Trustworthy") || ChangeCharacterHunterScore(Pchar, "spahunter", 0) <= -50)
			{
            dialog.text = "Ich muss Sie enttäuschen, Senor, aber wir brauchen im Moment keine Sklaven. Kapitän Eduardo de Losada hat uns bereits mit Piraten versorgt, die er bei seinem letzten Überfall gefangen genommen hat.";
			link.l1 = "Piraten hier? Wie kannst du hier überhaupt schlafen?";
			link.l1.go = "mtraxx_1";
			}
			else
			{
				dialog.text = "Ach, lass uns mal sehen... Ich kaufe deine Sklaven. Es scheint mir nur, dass du nicht der bist, der du vorgibst zu sein. Komm mit mir ins Kommandantenbüro, mein Lieber, und wenn ich mich irre, werde ich deine moralischen Kosten vollständig decken. Und jetzt bitte ich um Entschuldigung. Wache!";
				link.l1 = RandPhraseSimple("Träum weiter, ich gebe mich nicht lebendig hin!");
				link.l1.go = "mtraxx_fail";
			}
		break;
		
		case "mtraxx_fail":
            DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddQuestRecord("Roger_3", "27");
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			Mtraxx_PlantPellyClear();
			Mtraxx_TerraxReset(3);
		break;
		// <-- legendary edition
		case "mtraxx_1":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(characterFromId("Fadey"));
            dialog.text = "Wir haben eine gute Wache, also sind die Chancen auf einen Aufstand gering. Aber Sie haben in einem Punkt recht: diese Bastarde sind schreckliche Arbeiter. Ich hätte sie nicht gekauft, wenn der Gouverneur mich nicht gebeten hätte, Don de Losada Respekt zu erweisen. Außerdem hat er auch nicht viel für sie verlangt.";
			link.l1 = "Ich verstehe. Dann muss ich wohl nach Los-Teques segeln... Señor, darf ich auf Ihrer Plantage herumlaufen und sie erkunden? Vielleicht möchte ich etwas von Ihrer Produktion kaufen...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Bist du ein Händler?";
			link.l1 = "In gewisser Weise, ja. Ich bin kein professioneller Händler, aber ich würde niemals von einem vielversprechenden Geschäft zurücktreten.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Interessant. Sehr gut, du hast meine Erlaubnis. Komm zurück, wenn du irgendwelche Ideen hast.";
			link.l1 = "Danke, Senor. Ich glaube, ich werde.";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   NextDiag.CurrentNode = "plantator_1";
		   pchar.questTemp.Mtraxx = "plant_3";
		   AddQuestRecord("Roger_3", "5");
		   Mtraxx_PlantSetMaxRocur();
		break;
		
		case "mtraxx_5":
            dialog.text = "Warum nicht? Welche Waren bieten Sie an?";
			if (GetSquadronGoods(pchar, GOOD_COFFEE) >= 500)
			{
				link.l1 = "500 Kisten Kaffee.";
				link.l1.go = "mtraxx_coffee";
			}
			if (GetSquadronGoods(pchar, GOOD_CINNAMON) >= 500)
			{
				link.l2 = "500 Kisten Vanille.";
				link.l2.go = "mtraxx_cinnamon";
			}
			if (GetSquadronGoods(pchar, GOOD_COPRA) >= 500)
			{
				link.l3 = "500 Kisten mit Kopra.";
				link.l3.go = "mtraxx_copra";
			}
		break;
		
		case "mtraxx_coffee":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 11;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Fünfhundert Kisten Kaffee? Nun, nun... Lassen Sie uns sehen... (zählt) Ich bin bereit, Ihren Kaffee zu tauschen für "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" Säcke mit Zucker und "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  Kisten mit Kakao. Deal?";
			link.l1 = "Hmm... Ich hatte auf bessere Bedingungen gehofft. Na ja, wen kümmert's. Abgemacht!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Vertrauenswürdig) Hochgeschätzter Herr, gestatten Sie mir, Einwände zu erheben! Ich habe Ihnen Waren von höchster Qualität gebracht. Ich kenne den Wert jeder Einheit, sowohl dessen, was ich anbiete, als auch dessen, was Sie im Gegenzug anbieten. Ich verdiene eine etwas größere Ladung von Ihrer Seite, und dieser Handel wird immer noch profitabel für Sie sein - das wissen Sie sehr gut.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_cinnamon":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 19;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 106;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 106;
            dialog.text = "Fünfhundert Kisten Vanille? Nun-nun... Lass mal sehen... (zählt) Ich bin bereit, deine Vanille zu tauschen für "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" Säcke Zucker und "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  Kisten mit Kakao. Abgemacht?";
			link.l1 = "Hmm... ich hatte auf bessere Bedingungen gehofft. Nun, wen kümmert's. Abgemacht!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Vertrauenswürdig) Hochgeschätzter Herr, erlauben Sie mir, Einspruch zu erheben! Ich habe Ihnen Waren von höchster Qualität gebracht. Ich kenne den Wert jeder Einheit, sowohl von dem, was ich anbiete, als auch von dem, was Sie im Gegenzug anbieten. Ich verdiene eine etwas größere Ladung von Ihrer Seite, und dieser Handel wird immer noch profitabel für Sie sein - das wissen Sie sehr gut.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_copra":
			i = hrand(3)+1;
			n = 5 - i;
			pchar.questTemp.Mtraxx.PlantGood.Cargo = 20;
			pchar.questTemp.Mtraxx.PlantGood.Sugar = i * 100;
			pchar.questTemp.Mtraxx.PlantGood.Cocoa = n * 100;
            dialog.text = "Fünfhundert Kisten mit Kopra? Nun-nun ... Lass mal sehen... (zählt) Ich bin bereit, deine Kopra zu tauschen für "+sti(pchar.questTemp.Mtraxx.PlantGood.Sugar)+" Säcke mit Zucker und "+sti(pchar.questTemp.Mtraxx.PlantGood.Cocoa)+"  Kisten Kakao. Deal?";
			link.l1 = "Hmm... Ich hoffte auf bessere Bedingungen... Na ja, wer kümmert sich darum. Abgemacht!";
			link.l1.go = "mtraxx_6";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup"))
			{
				link.l1 = "(Vertrauenswürdig) Geschätzter Herr, erlauben Sie mir zu widersprechen! Ich habe Ihnen Waren von höchster Qualität gebracht. Ich kenne den Wert jeder Einheit, sowohl von dem, was ich anbiete, als auch von dem, was Sie im Gegenzug anbieten. Ich verdiene eine etwas größere Ladung von Ihrer Seite und dieser Handel wird immer noch profitabel für Sie sein - das wissen Sie sehr gut.";
				link.l1.go = "mtraxx_PlantVykup_2";
				notification("Trustworthy", "Trustworthy");
			}
		break;
		
		case "mtraxx_6":
            dialog.text = "Hervorragend! Es ist ein profitables Geschäft für uns beide! Wann werden wir den Austausch durchführen?";
			link.l1 = "Ich sollte die Waren zuerst vorbereiten. Du auch, glaube ich. Lassen wir den Austausch morgen um vier Uhr Nachmittags beginnen. Meine Männer werden die Kisten vor dem Sonnenuntergang liefern.";
			link.l1.go = "mtraxx_7";
		break;
		
		
		case "mtraxx_7":
            dialog.text = "Abgemacht. Nun, dann sehe ich Sie morgen, Senor!";
			link.l1 = "Bis dann...";
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			AddQuestRecord("Roger_3", "10");
			pchar.questTemp.Mtraxx = "plant_7";
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.mtraxx_plant_goods.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtraxx_plant_goods.win_condition.l1.location = pchar.location;
			pchar.quest.mtraxx_plant_goods.function = "Mtraxx_PlantFindRocurDay";
		break;
		
		case "mtraxx_9":
            dialog.text = "Das ist es, Señor. Wenn Sie jemals Zucker oder Kakao brauchen, kommen Sie bitte und sehen Sie mich an. Jederzeit!";
			link.l1 = "Wenn sich dieser Handel als gewinnbringend erweist - wir werden uns wiedersehen. Ich muss jetzt gehen, Senor.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_10":
            dialog.text = "Auf Wiedersehen, senor!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantAfterTrading");
		break;
		
		case "mtraxx_soldier_1":
            dialog.text = "Sie sehen nicht wie ein Händler aus, Ausländer. Zeigen Sie Ihre Lizenz.";
			link.l1 = "Verschont mich! Entscheidet ein Stück Papier, ob eine Person handeln kann oder nicht? Sie sind zu teuer! Ich habe erst kürzlich mit dem Handel begonnen, aber es ist bereits meine Leidenschaft geworden! Lasst mich durch, und ich werde sicherstellen, dass ich beim Besitzer ein gutes Wort für euch einlege.";
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_soldier_2":
            dialog.text = "Du hast eine Silberzunge, du Geizhals. Gut, mach weiter. Aber vergiss nicht, dem Boss zu sagen, dass wir diejenigen sind, die dich ihm empfohlen haben.";
			link.l1 = "Sicherlich. Danke.";
			link.l1.go = "plantation_exit";
		break;
		
		case "mtraxx_PlantVykup_2":
            dialog.text = "Sie kennen sich gut mit aktuellen Preisen aus, Kapitän! Sie haben ein klares Händchen für Verhandlungen, auch wenn Sie wie ein Neuling wirken. Nun, wenn Ihre Ware wirklich erstklassig ist, sollte ich wohl ein kleines Extra für Sie hinzufügen.";
			link.l1 = "Natürlich, erstklassig, ich schwöre! Noch etwas, Herr. Ich möchte Ihnen etwas abkaufen.";
			link.l1.go = "mtraxx_PlantVykup_3";
		break;
		
		case "mtraxx_PlantVykup_3":
            dialog.text = "Oh? Und was könnte das sein?";
			link.l1 = "Jemand, nicht etwas. Ich möchte einen deiner Sklaven als persönlichen Diener kaufen. Ist das möglich?";
			link.l1.go = "mtraxx_PlantVykup_4";
		break;
		
		case "mtraxx_PlantVykup_4":
            dialog.text = "Kein Problem. Wir werden jemanden Passendes für Sie finden.";
			link.l1 = "Ich interessiere mich für einen bestimmten Sklaven. Den mit dem charmanten Gesicht - jemanden, den man nicht schämen würde, zu formellen Veranstaltungen mitzubringen oder seinen Gästen Wein servieren zu lassen. Er stellte sich als Jean Picard vor. Wir haben uns bereits gut verstanden.";
			link.l1.go = "mtraxx_PlantVykup_5";
		break;
		
		case "mtraxx_PlantVykup_5":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 70)
			{
				dialog.text = "Ja, es besteht Bedarf an Jean Picard - nicht nur zum Weinschenken. Ein einflussreicher Engländer hat mich bereits kontaktiert. Ein Mann namens, wie war es ... Pattornson? Er hat mir einen Brief zugestellt.";
				link.l1 = "Aber weder Pattornson noch sein Kunde sind bisher aufgetaucht. Ich bin bereit, Jean hier und jetzt von dir zu kaufen. Nenne deinen Preis - die Damen warten!";
				link.l1.go = "mtraxx_PlantVykup_10";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ach, hau ab. Ich verstehe. Aber ich fürchte, ich muss ablehnen - Jean Picard steht nicht zum Verkauf. Es tut mir leid, senor.";
				link.l1 = "Oh? Warum ist das so? Ich bin bereit, gut zu bezahlen. Nennen Sie einfach Ihren Preis.";
				link.l1.go = "mtraxx_PlantVykup_6";
				notification("Skill Check Failed (70)", SKILL_COMMERCE);
			}
		break;
		
		case "mtraxx_PlantVykup_6":
            dialog.text = "Unbezahlbar. Er hat bereits einen Käufer. Ich habe ihn jemand anderem versprochen. Es gibt nichts mehr zu sagen. Lassen Sie uns zu unserem ursprünglichen Geschäft zurückkehren und den Handel abschließen.";
			link.l1 = "Hmm, wie Sie wünschen, senor.";
			link.l1.go = "mtraxx_PlantVykup_7";
		break;
		
		case "mtraxx_PlantVykup_7":
            dialog.text = "Wunderbar! Das ist ein profitabler Deal für uns beide! Wann werden wir den Austausch durchführen?";
			link.l1 = "Ich sollte zuerst die Waren vorbereiten. Du auch, glaube ich. Beginnen wir den Austausch morgen um vier Uhr nachmittags. Meine Männer werden die Kisten vor Sonnenuntergang liefern.";
			link.l1.go = "mtraxx_PlantVykup_8";
		break;
		
		
		case "mtraxx_PlantVykup_8":
            dialog.text = "Abgemacht. Nun, dann werde ich Sie morgen sehen, senor!";
			link.l1 = "Auf Wiedersehen...";
			link.l1.go = "mtraxx_PlantVykup_9";
		break;
		
		case "mtraxx_PlantVykup_9":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup2 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_1");
		break;
		
		case "mtraxx_PlantVykup_10":
            dialog.text = "Wie Sie wünschen, senor. Aber verstehen Sie, der Preis ist hoch: fünfhundert Dublonen.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Das ist kein Problem - hier bitte. Ein guter persönlicher Diener ist mehr wert als ein gewöhnlicher Sklave, wie Sie ja wissen.";
				link.l1.go = "mtraxx_PlantVykup_11";
			}
			else
			{
				link.l2 = "Ein ziemlich hoher Preis, den Sie da angesetzt haben, Herr. Aber dieser Sklave interessiert mich sehr. Warten Sie hier. Wenn Pattornson auftaucht, sagen Sie ihm, Picard sei bereits verkauft worden - ha-ha-ha!";
				link.l2.go = "mtraxx_PlantVykup_13";
			}
		break;
		
		case "mtraxx_PlantVykup_11":
            dialog.text = "Du hast recht. Ich werde die Vorbereitungen treffen. Picard wird draußen auf dich warten.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "mtraxx_PlantVykup_12":
            DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.mtraxx_PlantVykup3 = true;
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
			DoFunctionReloadToLocation("Maracaibo_ExitTown", "rld", "loc17", "Mtraxx_PlantPlantVykup_2");
		break;
		
		case "mtraxx_PlantVykup_13":
            dialog.text = "Wenn er mit dem vollen Betrag kommt, bezweifle ich, dass ich ihn wegschicken werde. Also beeilen Sie sich, Kapitän.";
			link.l1 = "Ich komme bald zurück.";
			link.l1.go = "mtraxx_PlantVykup_14";
		break;
		
		case "mtraxx_PlantVykup_14":
            DialogExit();
			NextDiag.CurrentNode = "mtraxx_PlantVykup_15";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantVykup");
		break;
		
		case "mtraxx_PlantVykup_15":
            dialog.text = "Haben Sie das Gold für Jean Picard gebracht, Kapitän? Die Zeit drängt.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Ich bin mir dessen wohl bewusst. Also hier, nimm dein Gold und gib mir meinen neuen Hausdiener.";
				link.l1.go = "mtraxx_PlantVykup_16";
			}
			else
			{
				link.l2 = "Immer noch am Sammeln - Sie sind derjenige, der einen so hohen Preis festgesetzt hat, senor.";
				link.l2.go = "mtraxx_PlantVykup_14";
			}
		break;
		
		case "mtraxx_PlantVykup_16":
            dialog.text = "Ich habe noch nie gesehen, dass jemand so viel ausgibt, um einen Diener zu erwerben. Aber anhand Ihrer feinen Kleidung zu urteilen, müssen Sie an solch großzügige Käufe gewöhnt sein. Ich werde meine Leute informieren und Picard wird am Ausgang auf Sie warten.";
			link.l1 = "...";
			link.l1.go = "mtraxx_PlantVykup_12";
			RemoveDublonsFromPCharTotal(500);
		break;
	}
} 
