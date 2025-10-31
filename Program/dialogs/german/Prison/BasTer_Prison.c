// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprechen Sie, ich höre zu.";
			link.l1 = "Ich habe mich geirrt. Lebewohl.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "Es gibt einen Indianer unter Arrest. Er wurde von Fadey, dem Moskowiter, gefangen genommen. Kann ich mit ihm sprechen?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Sagen Sie mir, wollen Sie diesen Inder wirklich hängen? Ist das nicht eine zu harte Strafe für ein so kleines Verbrechen?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Es ist wieder ich, Kommandant. Fadey der Moskoviter hat diese Petition zur Freilassung des Indianers geschrieben. Hier ist sie.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Ich bin auf Anfrage des örtlichen Ladenbesitzers zu Ihnen gekommen, sein Name ist "+pchar.questTemp.Shadowtrader.Tradername+". Er bat mich, Ihnen diesen Brief zu geben.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Das bin ich wieder. Ich habe erhebliche Beweise, dass "+pchar.questTemp.Shadowtrader.Tradername+" ist richtig.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Ich suche einen Mann namens Longway. Ich höre, Sie suchen ihn auch, Monsieur Offizier. Haben Sie ihn gefunden, oder vielleicht irgendwelche Hinweise?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "A-ah, hat Fadey Ihnen seine Geschichte erzählt? Ich habe keine Gründe, Ihnen zu verbieten, ihn anzusehen, Monsieur. Sie sind nicht der Erste, der kommt, um diesen Rothaut zu sehen. Nun, in zehn Tagen wird jeder Bürger ihn ansehen können, wenn wir ihn zum Trocknen in der Sonne aufhängen ...";
			link.l1 = "Kann ich also das Gefängnis betreten?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Wie ich Ihnen bereits gesagt habe 'Ich habe keinen Grund, Ihnen das zu verbieten'. Machen Sie weiter.";
			link.l1 = "Danke!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Sie sind neu hier, nicht wahr, Monsieur? Direkt aus Europa? Sie verstehen die Situation in den Kolonien nicht. Diese Hinrichtung wird eine Lehre für diese Rothaut-Bastarde sein, die es wagen würden, sich am Eigentum der französischen Kolonisten zu vergehen. Außerdem besteht Fadey selbst darauf und er ist ein sehr angesehener Mann hier und ein enger Freund unseres Gouverneurs.";
			link.l1 = "Gibt es eine Möglichkeit, die Strafe zu mildern? Ich denke immer noch, dass sie zu streng ist...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Oh, gehen Sie nicht in die Philosophie! Gehen Sie zu Fadey und fragen Sie nach diesem Indianer, wenn Sie sich wirklich so sehr um sein Schicksal kümmern. Wenn Fadey eine Petition zur Freilassung schreibt, werden wir sie erfüllen.";
			link.l1 = "Verstanden, Offizier. Ich gehe zu Fadey.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(liest) Hm... Dieser Fadey ist merkwürdig... Er hat eine demonstrative Hinrichtung gefordert und jetzt bittet er, diesen Indianer freizulassen... Wie auch immer, ich vermute, alle Freunde des Gouverneurs sind wie er. Also gut, du kannst gehen und diesen Rothäutigen mitnehmen.";
			link.l1 = "Mein Dank, Offizier!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Wieder das "+pchar.questTemp.Shadowtrader.Tradername+" mit seinen Beschwerden! Also gut, schauen wir mal, was diesmal los ist... (liest durch)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Noch einmal, absurd Vermutungen und kein einziges starkes Beweisstück! Gut. Sag ihm, dass das einfach nicht genug für mich ist, um die Wachen zu alarmieren und sie anzuweisen, die Stadt zu durchsuchen.";
			link.l1 = "Willst du, dass ich ihm das sage?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Genau - und vorzugsweise, Wort für Wort. Er wird verstehen, was ich meine. Ich werde kein Papier verschwenden, um eine Antwort auf diesen nervigen zu schreiben.";
			link.l1 = "Ich verstehe. Auf Wiedersehen, dann.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "Und was ist diese 'substantielle' Beweise, die Sie behaupten gesammelt zu haben?";
			link.l1 = "Ich habe einen Deal mit den Schmugglern bezüglich des Kaufs von Waren durch ihren inoffiziellen Laden ausgehandelt. Ihr Agent wird heute Nacht zum Hafenamt kommen, um mich zu ihrem sogenannten 'Laden' zu bringen.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Hmm... Nun, hervorragende Arbeit, Kapitän! Dann werden wir weiter agieren. Wir werden unseren Mann zu ihrem Treffen schicken, ihr Versteck ausfindig machen und alle von ihnen festnehmen. Danke für Ihre Initiative!";
			link.l1 = "Immer froh zu helfen. Ich bin sicher, dass Ihre Operation erfolgreich sein wird.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Wer? Lange... Weg? Ich erinnere mich nicht an Engländer in unserer Stadt in letzter Zeit.";
			link.l1 = "Nein, Longway ist... Chinese.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Nun, nun. Und warum suchen Sie diesen Longway von Ihnen, Monsieur?";
			link.l1 = "Er ist ein Freund von mir. Ich habe bereits gehört, was passiert ist - es ist ein trauriges Missverständnis, das versichere ich Ihnen.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Ich suche ihn, weil er ein bekannter Verbrecher im Archipel ist.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ach, ein Missverständnis. Wir haben nicht versucht, ihn sofort zur Vernunft zu bringen, wenn überhaupt. Wir wollten nur mit ihm reden... für den Anfang. Aber dieser aggressive gelbe Mann von Ihnen hat nicht nur mehrere Stadtwachen niedergemetzelt, sondern auch die Einheiten abgeschlachtet, die geschickt wurden, um ihn im Dschungel zu verfolgen.";
			link.l1 = "Planen Sie, eine weitere Einheit zu schicken? Ich könnte mit Ihren Männern gehen, mit ihm reden, ihn beruhigen und eine weitere Katastrophe verhindern. Würde es genügen, wenn die Morde aufhörten und Longway die Stadt für immer verließe?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "Unter normalen Umständen könnte ich Ihnen zustimmen. Aber sehen Sie, einer der Getöteten war ein Offizier - ein vielversprechender junger Leutnant, der Liebling Seiner Gnaden. Die Stadt trauert. Es gibt kein Wegsehen oder Wiedergutmachung. Verstehen Sie?";
			link.l1 = "Ich verstehe vollkommen. Ich entschuldige mich für die Handlungen meines Freundes. Ich werde Ihnen keine weiteren Probleme bereiten.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Sie wissen, Gott allein weiß, was im Dschungel vor sich geht. Jeder hätte diese Männer töten können.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "Und wer glauben Sie könnte eine ganze Patrouille unter der Führung eines Offiziers außer Gefecht gesetzt haben?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Vertrauenswürdig) Banditen, wer sonst? Es ist mir peinlich, es zuzugeben, aber ich bin kürzlich nur knapp einer riesigen Bande entkommen.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Aber wie sollte ich das wissen? Es könnte jeder gewesen sein - Briganten, Piraten, Spione...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Heh, das ist nicht überraschend - wenn man Ihre Körpergröße betrachtet, Kapitän. Ja, wir haben solche Halunken heutzutage auf der Insel...";
			link.l1 = "Genau! Also, sie könnten die Patrouille und den armen Leutnant niedergemetzelt haben.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "Leider ist das durchaus möglich.";
			link.l1 = "Genau. Also frage ich Sie noch einmal, lassen Sie mich der nächsten Suchgruppe beitreten - Longway wird mir zuhören, und so können wir weitere Todesfälle vermeiden.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "In Ordnung. Aber es gibt noch ein 'aber', Herr.";
			link.l1 = "Und was ist das?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "Anders als im Dschungel, ist die Schuld Ihres Freundes in der Stadt klar und vollständig bewiesen. Sie wird nicht ungestraft bleiben. Also müssen diese Tode kompensiert werden, wenn Sie wollen, dass er die Stadt lebend verlässt.";
			link.l1 = "Gut genug. Wie viel wird es kosten, Herr Offizier?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Dreihundert Dublonen. Dieses Geld geht an die Stadt, nicht an die Marktplatz-Wrangler.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Natürlich. Dreihundert Dublonen - bitte sehr.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Ich habe meine Dublonen diesmal nicht in die Stadt gebracht. Aber wenn du mich sie holen lässt...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Ausgezeichnet. Sie haben Ihre Verantwortung bewiesen. Wir schließen gerade das Briefing für das nächste Team ab. Ich erlaube Ihnen, sich ihm anzuschließen.";
			link.l1 = "Danke. Auf Wiedersehen, Herr Offizier.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Ich bin nicht gestern geboren. Ich weiß, du beabsichtigst zu fliehen - nicht für Dublonen, sondern für deinen lieben Chinesen.";
			link.l1 = "Ich gebe dir mein Wort, ich werde die Stadt nicht mit Longway verlassen.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Worte, Worte... Ich habe genug von deinem Geschwätz, Kapitän. Du gehst nirgendwo hin, bis wir diesen verfluchten gelbhäutigen Mann selbst gefangen haben.";
			link.l1 = "Ich werde Ihrem Befehl folgen, wenn Sie versprechen, Longway nicht auf der Stelle zu töten, Herr Offizier.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Aber habe ich heute persönlich die Gesetze der Stadt verletzt?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Dann wissen Sie es nicht. Ich bleibe bei meiner aktuellen Vermutung - der Chinese muss gefangen werden, egal was passiert.";
			link.l1 = "Deine aktuelle Vermutung? Aber du hast keinen Beweis dafür, dass Longway alle im Dschungel getötet hat.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "Und haben Sie Beweise für seine Unschuld? Nein? Dann hören Sie auf, aus Ihrem gelbhäutigen Mann einen Heiligen zu machen. Verstehen Sie mich?";
			link.l1 = "Ich verstehe vollkommen. Ich entschuldige mich für die Handlungen meines Freundes. Ich werde Sie nicht weiter belästigen.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Ich fürchte, ich kann Sie noch nicht gehen lassen, Kapitän.";
			link.l1 = "Was meinst du?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "Was ich meine ist, dass, da dieser Longway dein Freund ist, es keine Garantie gibt, dass du ihm nicht nachläufst und versuchst, mit ihm zu entkommen. Also, ich werde dich festhalten müssen, bis wir diesen gelbhäutigen Schlächter selbst fangen.";
			link.l1 = "Ich werde Ihrem Befehl gehorchen, wenn Sie versprechen, Longway nicht sofort zu töten, Herr Offizier.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Aber habe ich heute persönlich die Gesetze der Stadt verletzt?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Ich kann nichts versprechen. Wer weiß, was Ihr Freund im Sinn hat, oder ob er ein weiteres Massaker beginnt, wenn er uns sieht. In der Zwischenzeit genießen Sie bitte Ihre luxuriösen Unterkünfte, Kapitän.";
			link.l1 = "Zum Brüllen komisch...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Verstehen Sie, ich habe nichts gegen Sie persönlich. Und Sie haben recht - Sie haben kein Verbrechen begangen. Aber wir müssen sicherstellen, dass Ihr gelbhäutiger Freund der Gerechtigkeit nicht entkommt.";
			link.l1 = "Dann verstehen Sie, dass ich mich nicht auf so schändliche Weise festnehmen lassen werde.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "In diesem Fall müssen wir Sie beruhigen, Herr.";
			}
			else
			{
				dialog.text = "Ich habe genug von alldem! Sergeant, führen Sie das Kommando zu dieser verdammten Höhle und finden Sie die Chinesen! Ich werde mich persönlich um diesen kümmern...";
			}
			link.l1 = "Zum Teufel, das wirst du.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Ein Kopfgeldjäger, hm? Normalerweise mag ich es nicht, mit Eurer Sorte zu tun zu haben, aber in diesem Fall ist es zu meinem Vorteil, dass unsere Interessen übereinstimmen. Anscheinend ist dieser Gelbhäutige ein berüchtigter Mörder. Er hat viele meiner Männer ermordet, sowohl in der Stadt als auch im Dschungel.";
			link.l1 = "Ich verfolge ihn schon seit einiger Zeit durch das Archipel.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Verdammter Schuft! Hier ist, was wir tun werden: Ich werde eine weitere Truppe zusammenstellen und du wirst mit ihnen gehen. Diesmal hat er keinen Ort zum Fliehen und mit deiner Hilfe haben wir eine bessere Erfolgschance. Erwarte jedoch keine Belohnung von mir - du bist ein Kopfgeldjäger, also wird deine Bezahlung von demjenigen kommen, der dich eingestellt hat. Du solltest dankbar sein, dass ich dich überhaupt mit mir zusammenarbeiten lasse.";
			link.l1 = "Das ist wahr genug. Bis später, Offizier. Wenn einer Ihrer Männer eine weitere Begegnung mit unserem chinesischen Freund überlebt, werde ich Ihnen sagen, wie es gelaufen ist.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Sie haben recht. Sie beide kennen sich, nehme ich an? Wer sind Sie füreinander?";
			link.l1 = "Er ist Navigationsoffizier auf meinem Schiff, und...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Ich suche ihn, weil er ein bekannter Verbrecher im Archipel ist.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "Er kann besser mit Kanonen umgehen als mit Karten. Hast du eine Ahnung, was dein Schoßhündchen von einem Chinesen getan hat?";
			link.l1 = "Ehrlich gesagt, nein, weil ich gerade angedockt habe und zu suchen begonnen habe. Ich bin sicher, es war alles ein Missverständnis.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Genau. Wer sind Sie für ihn, wenn Sie ihn so sehr wollen? Das spielt keine Rolle - was wichtig ist, ist der Zweck Ihres Besuchs in der Stadt.";
			link.l1 = "Nichts Illegales, Herr. Aber was meinten Sie mit „es ist nicht mehr wichtig“? Hat er...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Ja. Er wurde hinter einem der Hügel begraben, ein Stück vom Friedhof entfernt. Die heiligen Väter erlaubten keine ordnungsgemäße christliche Beerdigung für einen Heiden.";
			link.l1 = "Wie ist das passiert, wenn es kein Geheimnis ist?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Sehr einfach - er kam in die Stadt, schnupperte ohne Ende herum. Wir versuchten mit ihm zu reden, herauszufinden, was er hier machte, aber er tötete einige Männer und floh in den Dschungel. Ich schickte mehrere Suchtrupps hinter ihm her, einen nach dem anderen, aber er räumte sie alle ab! Wir mussten ihn in einer Höhle einfangen, und die Schützen erledigten den Rest.";
			link.l1 = "Und Sie wissen nicht, was er gesucht hat? Sehen Sie, er hat so etwas noch nie gemacht - er war ein Navigator auf meinem Schiff. Aber dann hat er von mir gestohlen und ist weggelaufen.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Es ist mir einfach entfallen, ja. Also, du hast auch unter seinen Taten gelitten? Das wird dir eine Lektion sein, Kapitän. Du wirst es besser wissen, als dich mit jemandem einzulassen, dem du nicht vertrauen kannst. Vertraue nie einem gelbhäutigen Mann - merk dir meine Worte!";
			link.l1 = "Ja, das werde ich im Hinterkopf behalten. Haben Sie etwas bei ihm gefunden?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "Oh, Sie wollen die gestohlenen Waren zurückhaben? Er hatte etwas Silber in seinen Taschen, also wenn er von Ihnen gestohlen hat, hat er bereits alles ausgegeben. Und da waren noch einige andere Papiere... aus Ihrem Schiffstagebuch? Wir haben es sowieso nicht verstanden - vielleicht eine Art Code? Alles war mit Blut bedeckt, sodass wir die unbeschädigten Teile nicht ausmachen konnten.";
			link.l1 = "Äh, ja. Danke. Ich habe mir immer Sorgen gemacht, was passieren würde, wenn meine Tagebücher und Journalen von jemand anderem aufgegriffen würden...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "Und musstest du wegen all dem einen komplexen Geheimcode erfinden? Hast du dein Zeit und Mühe nicht bedauert? Hier hast du es. Und was das Silber angeht - sei nicht sauer, aber wir haben es der Stadt zurückgegeben. Dieser Chinese hat an diesem Tag viele meiner Männer begraben.";
			link.l1 = "Dann wage ich nicht zu bestehen. Auf Wiedersehen.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
