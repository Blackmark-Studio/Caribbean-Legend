// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast schon versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Sie sprechen heute bereits zum dritten Mal über eine bestimmte Frage...","Schau, wenn du mir nichts über die Hafenangelegenheiten zu erzählen hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Entschuldigung, aber ich interessiere mich momentan nicht für die Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "Die Tatsache ist, dass ich jeden Tag mit einer Ladung von bei Ihnen in der Kolonie gekauften Waren nach Porto Bello gehen werde. Ich dachte: Vielleicht haben Sie irgendeine Art von Fracht oder Geschäft, das ich unterwegs erledigen kann ... Gegen eine Gebühr, natürlich.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Hallo erneut. Ich habe Ihren Brief nach Porto Bello geliefert. Dort wurde ich gebeten, Ihnen eine Antwort zu geben.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Hallo. Ich komme zu Ihnen aus Porto Bello. Ihr Kollege von der örtlichen Hafenbehörde hat mich gebeten, Ihnen diesen Brief zu übergeben.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Danke für Ihre Besorgnis, aber ich habe keine solchen Fälle. Es gab tatsächlich eine Aufgabe, aber Sie waren buchstäblich ein paar Tage zu spät: Ich habe für diesen Zweck einen Hochgeschwindigkeitskurierlugger geschickt.";
				link.l1 = "Verstanden... Nun, danke dafür.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Ich sehe, du hast nicht mal ein Schiff. Du musst ein reicher Kaufmann sein. Hmm ... Aber ich kenne alle lokalen Kaufleute mit Geschwadern auf Sicht, aber ich kenne dich nicht. Also nimm es mir nicht übel, aber ich kann dir nichts Ernsthaftes anvertrauen.";
					link.l1 = "Habs... Nun, danke dafür.";
					link.l1.go = "exit";
				}
				else
				{
					if(int(RealShips[int(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hmm... Ich habe eine Aufgabe. Nur passt dein Schiff jetzt nicht. Ich brauche ein Schiff, das gleichzeitig schnell und kraftvoll ist, und deins erfüllt diese Anforderungen nicht vollständig. Zumindest nicht gleichzeitig. Also bitte verzeih mir.";
						link.l1 = "Verstanden... Nun, danke dafür.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Ich habe etwas zu tun... Und du hast ein gutes Schiff. Es sieht nur nicht wie ein Händlerschiff aus. Und soweit ich sehen kann, hast du keine Langzeitlizenz von der Niederländischen Westindien-Kompanie. Sei nicht beleidigt, aber du wirkst nicht wie ein Händler. Ich kann dieses Risiko nicht eingehen.";
							link.l1 = "Habs... Nun, danke dafür.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Ich habe etwas zu tun... Und du hast ein gutes Schiff. Nur verstehe ich jetzt nicht, was du handeln willst... Du sagtest, du gehst nach Porto Bello, um die Waren zu verkaufen, aber soweit ich weiß, hast du sie nicht bei uns in der Kolonie gekauft. Sei nicht beleidigt, aber du kommst nicht als Kaufmann rüber. Ich kann dieses Risiko nicht eingehen.";
								link.l1 = "Verstanden... Nun, danke dafür.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Ich habe etwas zu tun. Natürlich kenne ich dich nicht... Aber, um die Wahrheit zu sagen, merke ich mir nur Kaufleute mit Geschwadern zu ihren Namen. Den Rest - nein. Ja, und Sie haben eine langfristige Lizenz, man kann sofort einen erfahrenen Kaufmann erkennen. Ihr Schiff ist jedoch interessant. Warum würden Sie auf einer Fregatte handeln?";
								link.l1 = "Hah, das ist keine gewöhnliche Fregatte. Sie kann eine sehr hohe Geschwindigkeit erreichen, selbst mit voller Ladung. Es ist immer einfacher, vor Piraten zu fliehen, als mit ihnen zu kämpfen, nicht wahr? Obwohl mein Schiff eine kleinere Kapazität hat als gewöhnliche Handelsschiffe, ist das Risiko viel geringer.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Hmm, aber du hast recht! Die Spanier wissen, wie man Schiffe baut, nicht wahr? Ja, ja, ich habe sofort gesehen, dass dieser stattliche Mann die Lager unserer Werften verlassen hat. Und ja, mir wurde tatsächlich heute gesagt, dass du eine Charge Kaffee und Kakao von unserem Händler für den Wiederverkauf in Porto Bello gekauft hast. Guter Deal, sage ich dir. Menschen, die mit dem Handel nicht vertraut sind, wissen nicht, dass diese Waren hier dank Plantagen billig sind und in Porto Bello sehr gefragt sind, da sie von dort aus in die Metropole gehen.";
			link.l1 = "Nun, darum geht es, Senor. Für ein paar Pesos würde ich mein Boot nicht so weit fahren.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Nun, um Ihnen die Wahrheit zu sagen, habe ich Geschäfte für Sie. Und es ist sehr gut, dass Sie ein so schnelles Schiff haben, das sich auch im Notfall zur Wehr setzen kann.";
			link.l1 = "Warte, señor... Dein Fall lässt vermuten, dass ich kämpfen muss...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Nein, nein! Tatsächlich ist meine Aufgabe so einfach wie möglich. Ich brauche dich, um einen Brief an die Hafenbehörde in Porto Bello zu liefern. Der Brief ist versiegelt und darf nicht geöffnet werden. Niemand muss darüber reden, Korrespondenz ... persönlich. Persönlich übergeben. Die Frist beträgt zehn Tage. Danach wird es irrelevant sein.";
			link.l1 = "So einfach? Und wie viel bekomme ich dafür?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Fünftausend Pesos. Betrachten Sie es als Bezahlung dafür, keinen Kurierkutter nach Porto Bello schicken zu müssen.";
			link.l1 = "Und was waren Ihre Fragen über mich und mein Schiff?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Macht nichts. Es ist nur so, dass die Korrespondenz wichtig genug ist und ich sicher sein muss, dass sie den Adressaten erreicht. Und so nichts Besonderes. Bürokratie... Für einen gewöhnlichen Menschen sind diese Dokumente von keinem Interesse.";
			link.l1 = "Nun, ich stimme zu. Lassen Sie uns Ihre Papiere hier bekommen. Sobald ich in Porto Bello ankomme, bringe ich sie zu Ihrem Kollegen. Ich werde es in zehn Tagen schaffen, mach dir keine Sorgen.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Einen Moment. Es tut mir leid, ich habe Ihren Namen völlig vergessen. Könnten Sie ihn bitte sagen? Ich muss ihn in den Dokumenten aufschreiben.";
			link.l1 = "Mein Name ist Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Danke dir. Also... großartig. Denk dran, dass du es bist, der dieses Dokument übergeben muss und direkt in die Hände des Empfängers. Hier hast du es. Die Belohnung wird dir vom Leiter der Hafenbehörde in Porto Bello gegeben. Gute Reise!";
			link.l1 = "Danke! Nun, entschuldigen Sie mich.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Großartig! Du hast mir sehr geholfen. Gab es Schwierigkeiten?";
			link.l1 = "Nein, es gab keine Schwierigkeiten. Wahr ist, dass Ihr Kollege Sie verflucht hat: Er sagte, dass Sie alle hier Geizhälse sind, weil Sie kein Kurierschiff schicken, sondern vorbeiziehende Kaufleute, und sogar die Zahlung auf den Empfänger aufhängen. Er drohte, dass er eine Beschwerde nach Havanna schreiben würde ...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Was?! Bin ich der Griesgram?! Was hat er sich dabei gedacht? Zuerst behalte deine fünf... nein, sechstausend Pesos! Ich weine ehrlich gesagt!";
			link.l1 = "Danke. Es ist schön zu sehen, dass Ihr Kollege mit seiner Meinung über Sie falsch lag.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "Und zweitens, dieser Schurke scheint vergessen zu haben, wie er vor zwei Monaten alle Kosten für die Instandhaltung eines Handelsschiffes, das von Caracas nach Porto Bello und von dort nach Havanna fuhr, auf mich abgewälzt hat! Und wir haben vereinbart, dass er für den zweiten Teil der Reise bezahlen würde! Und er hat die Schuld nie zurückgezahlt, aber versprochen, dass er letzten Monat alles begleichen würde! Und ich bin immer noch der Geizhals ... Ja, ich werde selbst eine Beschwerde gegen ihn in Havanna einreichen!";
			link.l1 = "Nun, Sie haben natürlich die Leidenschaften des Madrider Hofes ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nein, wenn ich darüber nachdenke ... Was für ein Frechdachs! Gut, ich werde mich erneut mit ihm auseinandersetzen ... Und jetzt bitte ich Sie, mich zu entschuldigen: Ich habe dringende Geschäfte vor mir. Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen!";
			link.l1 = "Und viel Glück für dich!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Großartig! Du hast mir sehr geholfen. Obwohl, ich habe ihnen einen Kurierkutter geschickt, und sie haben mir die Antwort mit einem vorbeifahrenden Schiff zurückgesendet. Ja ... Und danach beschweren sie sich immer noch, dass wir hier Geizhälse sitzen haben.";
			link.l1 = "Nun, vielleicht haben sie das Geld für den Kurier gespart ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Nicht 'vielleicht', sondern definitiv, sage ich dir! Gut, es spielt keine Rolle. Hier, nimm deine Arbeit. Und jetzt habe ich viel Arbeit, entschuldige mich.";
			link.l1 = "Nun, vielleicht haben sie das Geld für den Kurier gespart ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
