// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hast du Fragen, "+GetSexPhrase("mein Sohn","meine Tochter")+"?","Frag ruhig, ich höre zu..."),"Ich höre zu, sprich jetzt, "+GetSexPhrase("mein Sohn","meine Tochter")+"...","Zum dritten Mal, "+GetSexPhrase("mein Sohn","meine Tochter")+", frag mich, was brauchst du?","Ein Geistlicher hat viel Arbeit und du lenkst mich ab, "+GetSexPhrase("mein Sohn","meine Tochter")+".","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt, Padre..."),"Ich habe nichts zu sagen, Entschuldigt mich.","Ich werde fragen haben, aber nicht jetzt. Verzeiht mir, Vater.","Verzeihen Sie mir, heiliger Vater...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "Seid gegrüßt Vater. Oberster Vater "+sld.name+" der Kirche von Willemstad hat mich geschickt. Sie haben ihm von seltsamen Sichtungen in einer Höhle auf Kuba erzählt.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "Ich habe die Höhle im Dschungel besucht, Vater.";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "Gott sei Dank hat er darauf geachtet! Als mich die Gerüchte über die Untoten erreichten, habe ich sofort Seine Eminenz Vater Vincento, den Inquisitor von Santiago, benachrichtigt. Er versprach, sich darum zu kümmern, aber bisher wurde keine Maßnahme ergriffen! Ich befürchte, Seine Eminenz hat wichtigere Angelegenheiten zu erledigen...";
			link.l1 = "Ich werde es selbst untersuchen. Außerdem sind all diese Gerüchte nichts anderes als das Geschwätz betrunkener Jäger - deshalb hat die Inquisition sie nicht ernst genommen. Ich werde in den Dschungel gehen, um es mit meinen eigenen Augen zu sehen.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ich versichere dir, mein Sohn, es ist von entscheidender Bedeutung. Dem Mann, der mir von den Untoten erzählte, vertraue ich mein Leben an.";
			link.l1 = "Sehr gut, dann bereite ich mich auf den Kampf vor. Wenn die unheiligen Kreaturen tatsächlich in der Höhle Fuß gefasst haben, werde ich sie aus dieser Welt vertreiben.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Geh mit dem Segen des Herrn, mein Sohn! Hier, nimm dieses geweihte Amulett. Es wird dir bei deiner Aufgabe helfen. Geh jetzt, vernichte die Brut des Bösen!";
			link.l1 = "Bis bald, Vater "+npchar.name+". Sobald ich fertig bin, komme ich sofort zu Ihnen zurück.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("Sie haben ein Amulett der Kirche erhalten");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "Was hast du gesehen, mein Sohn? Waren unsere Ängste unbegründet?";
			link.l1 = "Es tut mir leid, Vater "+npchar.name+". Die Höhle war voller Untoter, aber mit Gottes Hilfe kam ich siegreich heraus. Sie werden niemanden mehr belästigen.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Lobet den Herrn! Du bist in der Tat sein strafendes Schwert, mein Sohn! Bitte erlaube mir, meine tiefste Dankbarkeit im Namen der gesamten Gemeinde von Havanna auszudrücken. Bitte, nimm diese geweihten Amulette als Zeichen der Dankbarkeit an. Sie werden dir auf deinen gefährlichen Reisen sicherlich nützlich sein.";
			link.l1 = "Danke, Vater "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("Sie haben Amulette der Kirche erhalten");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "Zusätzlich werde ich dafür sorgen, dass sowohl das Gemeine Volk als auch die Adligen von deiner heldenhaften Tat erfahren werden und ich werde unermüdlich Tag und Nacht für dich beten.";
			link.l1 = "Danke, Vater. Ich habe noch eine weitere Frage.";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Frag, mein Sohn.";
			link.l1 = "Sagt mir, Vater "+npchar.name+", ist kürzlich ein Mann namens Joachim Merriman in Ihrer Stadt angekommen? Ein Herr mittleren Alters, ein Portugiese mit einem Schnurrbart, kaiserlichem Bart und durchdringenden Augen?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Weder Name noch Beschreibung sagen mir etwas, es tut mir leid. Wer ist dieser Mann?";
			link.l1 = "Merriman ist ein Hexenmeister. Die Inquisition jagt ihn schon sehr lange. Vater "+sld.name+" und ich vermuten, dass das Auftreten der lebenden Toten auf Kuba sein Werk ist. Noch vor kurzem lebte er in Willemstad, dann verschwand er plötzlich. Kurz darauf wurde die Frau, die ihn untergebracht hatte, in ein wandelndes Skelett verwandelt.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Was für ein Albtraum! Ich werde sofort die Inquisitoren informieren, Vater Vincento selbst! Er muss wissen, was hier vor sich geht! Sag mir, mein Sohn, glaubst du, dass die Menschen, die im Dschungel verschwunden sind...?";
			link.l1 = "Tatsächlich bin ich fast sicher, dass diese lebenden Toten in der Höhle eure ehemaligen Bürger waren. Ich will diesen Portugiesen auf Kuba ausfindig machen und ihn zur Strecke bringen! Dieser Schurke hat es geschafft, eine alte heidnische Reliquie in die Hände zu bekommen - einen Jadeschädel von Yum Cimil. Ich fürchte, dass Merriman mit dem Artefakt und indianischer Hexerei noch mehr Ärger verursachen wird, wenn ihn nicht bald jemand stoppt.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Glaubst du, dass die Untoten wieder auferstehen werden?";
			link.l1 = "Mit Sicherheit. Ich bin mir nur nicht sicher, was ihn antreibt, aber sicherlich sind seine Bestrebungen weit davon entfernt, tugendhaft zu sein.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Möge der Allmächtige uns Gnade zeigen! Suche ihn, mein Sohn! Ich erlaube dir, im Namen unserer Heiligen Kirche jegliche Maßnahmen gegen ihn zu ergreifen! Ich werde sofort einen Boten nach Santiago schicken, um Vater Vincento zu berichten.";
			link.l1 = "Tun Sie das. Auf Wiedersehen, Vater "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
