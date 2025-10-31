// Лукас Роденбург - вице-директор ГВИК
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
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Sprich Junge, aber sei schnell. Ich bin ein beschäftigter Mann .";
				link.l1 = "Ich habe gehört, dass Sie Kapitäne einstellen.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Haben Sie Geschäft für mich?";
			link.l1 = "Nein, sorry. Ich gehe.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Sie sollten jetzt schon auf halbem Weg nach Sint Maarten sein, Kapitän.";
				link.l1 = "Ich bereite mich darauf vor, in See zu stechen, Mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ach, Kapitän, da bist du ja! Ich habe dich nicht kommen sehen, ich habe gerade Ridderbrocks Brief fertig gelesen. Du hast einen ganz besonderen Eindruck hinterlassen. Er nennt dich den 'Wächter der Händler und Geißel der Piraten. Das Geschenk Gottes an die Gesellschaft!' Was sagst du dazu?";
				link.l1 = "Ich würde lieber ein gewöhnlicher Kapitän bleiben. Ein gewöhnlicher, aber reicher Kapitän.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Warum bist du noch hier und nicht auf dem Weg nach Kuba?!";
				link.l1 = "Ja, ja, ich bin auf dem Weg, Mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ach, Kapitän! Ich gebe zu, dass ich anfing, mir Sorgen zu machen. Wie war es?";
				link.l1 = "Es war nicht ohne Probleme, aber ich werde Ihnen später davon erzählen. Geschäft zuerst. Senor "+GetFullName(sld)+" hat mir gesagt, Ihnen folgendes zu sagen: 'Dieser Mann muss sterben'. Dann wird Geraldi den Vorfall als erledigt ansehen. Außerdem sagte er, dass diese Entscheidung der Wille ihrer Familie ist.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Froh dich zu sehen, Kapitän! Es ist gut, dass du mich besucht hast.";
				link.l1 = "Guten Tag, Mynheer. Ich nehme an, Sie haben einen weiteren Auftrag der Gesellschaft für mich?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Ich habe Ihnen gesagt, Sie sollen Ihr Schiff vertäuen. Sind Sie zu dumm oder unwissend, um direkte Befehle zu befolgen?";
					link.l1 = "Weder noch, Mynheer. Ich bin auf meinem Weg.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Also, du hast dein Schiff festgemacht. Jetzt werde ich dir meine Xebec leihen. Bist du bereit, diese Mission sofort zu starten? Mein Schiff ist gut ausgerüstet und bereit zu segeln, also gibt es für dich nichts mehr zu befürchten.";
					link.l1 = "Ja, sicher. Ich bin bereit, Mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Warum bist du noch hier? Geh sofort zu Longway.";
				link.l1 = "Entschuldigung, ich bin auf dem Weg.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitän... Ich weiß bereits von Ihrer Reise.";
					link.l1 = "Ach wirklich? Dann müssen Sie ja wissen, dass...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitän... Ich weiß bereits von Ihrer Reise.";
					link.l1 = "Ist das so? Dann müssen Sie wissen, dass...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitän... Ich weiß bereits von Ihrer Reise.";
					link.l1 = "Ist das so? Dann müssen Sie wissen, dass...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Hier sind Sie, Kapitän... Ich weiß bereits alles über Ihre Reise.";
					link.l1 = "Ist das so? Dann musst du wissen, dass...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Geh sofort nach Antigua.";
				link.l1 = "Entschuldigung, ich bin unterwegs.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Ich wurde über Ihre Ankunft informiert, Kapitän. Mir ist auch bekannt, dass Sie meine Mirage im Kampf verloren haben.";
					link.l1 = "Sie sind gut informiert, Mynheer Rodenburg. Trotz all meiner Bemühungen konnten wir sie nicht retten.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Ich wurde über Ihre Ankunft informiert, Kapitän. Ich sehe, dass die Mirage sicher angedockt ist. Das ist gut.";
					link.l1 = "Alles geschah nach Ihren Anweisungen, Mynheer. Sie befahlen mir, Fleetwood zu töten und er ist tot. Sie befahlen mir, die Mirage zurück zum lokalen Hafen zu bringen und sie ist hier.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ach, da bist du ja. Schön dich zu sehen. Ich habe eine weitere Mission für dich, wie versprochen.";
				link.l1 = "Ich höre zu, Mynheer.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ach, ich bin froh, dich zu sehen, mein Junge. Du bist spät gekommen und ich habe angefangen, mir Sorgen zu machen. Konntest du etwas von Abigail bekommen?";
				link.l1 = "Nicht nur das, ich habe auch Ihre anderen Probleme gelöst. Ich habe die Insel und das verlorene Vermögen der Shneurs gefunden. Solomon ist glücklich und Abigail wird Ihrem Antrag zustimmen. Herzlichen Glückwunsch, Mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ach, ich bin froh, dich zu sehen, mein Freund. Konntest du etwas von Abigail bekommen?";
				link.l1 = "Ja. Ich habe mit Abigail und ihrem Vater gesprochen. Es gibt ein Problem, Mynheer: das verlorene Vermögen ihres Vaters. Abigail fühlt sich Ihrer unwürdig, sie fürchtet das Gerede und Geflüster der Leute, wenn sie als Mädchen ohne Mitgift einen Gentleman wie Sie heiraten würde. Ich hoffe, Sie verstehen das.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ach, mein Freund! Ich hoffe, du hast gute Nachrichten gebracht?";
				link.l1 = "Ihr Plan war erfolgreich. Abigail wird ja sagen. Herzlichen Glückwunsch, Mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Ich habe auf dich gewartet. Mein Junge, du bist in großer Gefahr.";
				link.l1 = "Was meinst du damit?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Meine Agenten am Dock haben mir gesagt, dass du angekommen bist. Ist Johan van Merden tot?";
				link.l1 = "Ja. Er und sein Komplize sind weg. Es war ein harter Kampf, aber ich habe es durchgestanden.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Wir haben nichts weiter zu besprechen, Kapitän.";
			link.l1 = "Verstanden, ich gehe jetzt.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Was ist los? Zeit ist Geld.";
		link.l1 = "Entschuldigung, ich gehe jetzt.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Vielleicht. Wer bist du? Sprich schnell, Zeit ist Geld.";
			link.l1 = "Ich bin Kapitän "+pchar.name+", mein Schiff und ich können Ihnen nützlich sein.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, eine unbekannte Legierung, die im Tiegel analysiert werden soll.";
			link.l1 = "Darum bin ich hier, Mynheer.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Sehr gut, wir werden die Farbe deines Mutes sehen. Also Kapitän, wie auch immer dein Name ist, kennst du Balthazar Ridderbrock? Nein? Wie glücklich. Solche gierigen, mürrischen, hitzköpfigen Idioten wie er sind seltene Anblicke.\nAber es scheint, dass solche herausragenden Qualitäten für den Mann nicht genug waren, also war er klug genug, um einen Freibeuter namens "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" im örtlichen Wirtshaus und rief die Wache in dem Moment, als die beleidigte Partei ein Schwert berührte...";
			link.l1 = "...und sie hängten den Piraten mit dem ersten freien Seil auf?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "Es ist nicht so einfach. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" ist kein gewöhnlicher Pirat, sondern ein niederländischer Freibeuter, ein Veteran der letzten beiden Kriege gegen die Briten. Die örtlichen Steuerzahler mögen ihn sehr. Das gleiche kann ich nicht über Ridderbrock sagen.";
			link.l1 = "Also lebt unser Freibeuter noch?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Ja, aber er ist wirklich wütend. Deshalb hat Ridderbrock die Hosen voll.";
			link.l1 = "Ich vermute, dass mein Glück bald zu Ende geht. Wann treffe ich Mynheer Ridderbrock?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Unverzüglich. Die guten Leute von Philipsburg erwarten eine Zuckerlieferung, eine, die unser gemeinsamer Bekannter Ridderbrock versprochen hat zu liefern. Ich halte den Mann nicht für das Leder seiner Stiefel wert, aber leider arbeitet er für uns, also geh zum Hafenbüro. Finde dort Ridderbrock und sag ihm, dass ich ihm befohlen habe, sofort in See zu stechen.\nDu wirst ihm folgen und... ihn in einem Stück nach Philipsburg begleiten. Ich will nicht "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" den Ruf der Gesellschaft zusammen mit seiner Fracht auf den Grund der Karibik zu schicken.";
			link.l1 = "Pfui, eine Eskortmission. Wie sieht es mit der Bezahlung für diesen... unangenehmen Auftrag aus?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitän, erledigen Sie zuerst die Aufgabe. Balthazar wird Sie bezahlen, sobald er sein Ziel erreicht. In Philipsburg! Nicht in Davy Jones' Kiste! Melden Sie sich danach bei mir, sobald die Arbeit erledigt ist. Wenn Sie erfolgreich sind, können Sie auf meine weitere Unterstützung und die der Gesellschaft zählen. Entlassen.";
			link.l1 = "Auf Wiedersehen, Mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Ja, Ridderbrock ist ein geiziger Hurensohn, selbst für einen Holländer. Wie auch immer, er ist nicht länger meine Angelegenheit. Sprechen wir über Sie, Kapitän Wie-auch-immer-Sie-heißen. Mir gefällt Ihr Stil, deshalb biete ich Ihnen einen weiteren Job an. Dieses Mal werde ich dafür selbst bezahlen.";
			link.l1 = "Ich höre zu, Mynheer.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Ich brauche einen Mann für eine sehr wichtige Angelegenheit. Sie haben im Fall Ridderbrock gute Arbeit geleistet, daher glaubt die Gesellschaft, dass ich es Ihnen anvertrauen kann.";
			link.l1 = "Ich nehme an, ich fühle mich geehrt. Was ist los?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Ich kann Ihnen keine genauen Details geben, aber seien Sie sich bewusst, dass dies nicht meine Aufgabe ist, sondern die der Kompanie, so haben Sie die Chance, sich bei uns beliebt zu machen, was ich Ihnen versichere, sehr lukrativ ist.\nSegeln Sie nach Santiago in Kuba und liefern Sie dieses Paket an Don "+GetFullName(sld)+". Er hat eine hohe Position in Geraldis Bank und er ist auch mein... unser Geschäftspartner. Sie sollen ihm dieses Gold liefern, das ich Ihnen jetzt geben werde. Ich vertraue auf Ihre Ehrlichkeit, Kapitän. Nun, wenn nicht auf Ihre Ehrlichkeit, dann auf Ihren Überlebensinstinkt. Die Firma findet immer diejenigen, die versuchen, uns zu bestehlen.";
			link.l1 = "Zweifeln Sie an mir, Mynheer?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "Im Moment zweifle ich nicht an dir. Glaub mir, ich würde nicht einmal mit dir über diese Angelegenheit sprechen, wenn ich es täte. Wisse, dass wir viel Zeit verschwendet haben, um diesen Job in die Wege zu leiten, also hast du nur fünfzehn Tage Zeit zur Lieferung."+sTemp+"\nMeine Nachricht und mein Paket müssen rechtzeitig geliefert werden. Dies ist lebenswichtig, Junge. Beeile dich, aber sei vorsichtig, das wird kein Spaziergang.";
			link.l1 = "Noch etwas? Warum warnen Sie mich, Mynheer Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Lassen Sie uns einfach sagen, dass ich meine Verdächtigungen habe. Machen Sie sich keine Sorgen, wenn Sie es so schnell erledigen wie den letzten Job, dann haben Sie die Chance, ein wertvoller Agent für heikle Angelegenheiten der Firma zu werden.";
			link.l1 = "Alles, was ich tun muss, ist, diesen Brief und das Geld innerhalb von fünfzehn Tagen beim Bankier in Santiago abzugeben? Klingt an der Oberfläche nicht allzu schwierig.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Nicht so schnell, Junge... Ich nehme an, du verstehst die Schwere der Situation nicht wirklich. Diese Aufgabe zu erledigen wird mich dir sehr verpflichten. Scheiterst du jedoch, werde ich sehr verärgert sein. In diesem Fall werde ich dann auf dich pissen. Verstehen wir uns, Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Punkt genommen. Sie haben mein Wort. Ich werde mein Bestes tun, um Sie in guter Stimmung zu halten.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Sehr gut. Nun, nehmen Sie den Brief, diese Kisten und denken Sie an die Bedingungen. Und noch eine Sache: Halten Sie sich in Santiago aus Ärger fern.";
			link.l1 = "Sehr gut.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Muss sterben'... einfach so. Das habe ich nicht kommen sehen. Hm. Du hast deine Arbeit gut gemacht, Kapitän. Jetzt gib mir eine Zusammenfassung.";
			link.l1 = "Nichts Besonderes... es war ein Milchlauf.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Ich wurde in Santiago betäubt und entführt von einem Mann. Er war sehr interessiert an deinem Geschäft mit Geraldi. Ich konnte zwar fliehen, musste ihn aber zuerst töten. Der einzige Hinweis, den er fallen ließ, war der Name eines gewissen Gaston. Ich habe keine Ahnung, um was es dabei ging.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Ich wurde in Santiago von einem Mann überwältigt und entführt. Er war sehr an deinem Geschäft mit Geraldi interessiert. Mir gelang die Flucht, aber ich musste ihn zuerst töten. Ich konnte nichts aus ihm herausbekommen, bevor ich ihn zur Hölle schickte.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "Die Dankbarkeit der Kompanie beschränkt sich nicht nur auf Worte. Nimm deine Belohnung, du hast sie verdient.";
			link.l1 = "Für die Firma zu arbeiten ist ziemlich lukrativ.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Was! Entführung... Warte, allerdings... Gaston! Ich verstehe... Ich vermute. Ach mein Junge, du wurdest in eine schmutzige Angelegenheit hineingezogen. Wir sind in unerforschten Gewässern, also müssen wir sehen, wie es sich entwickelt. Froh, dass du am Leben bist.\nLass uns über angenehmere Dinge sprechen - nimm diese Belohnung an, sie ist wohlverdient.";
			link.l1 = "Für die Kompanie zu arbeiten ist ziemlich profitabel";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Unsinn! Dich zu entführen... Ich habe allerdings einige Vermutungen. Du wirst mehr erfahren, wenn du weiter für mich arbeitest. Du hast Glück und ich bin froh, dass du es geschafft hast.\nLass uns über angenehmere Dinge sprechen - nimm diese Belohnung an, sie ist wohlverdient.";
			link.l1 = "Für die Firma zu arbeiten ist ziemlich lukrativ";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Genau, mein Junge! Du kannst ein gut bezahlter Agent der Kompanie werden, wenn wir weiterhin zusammenarbeiten. Jetzt geh, erhole dich von deiner Reise. Du hast meinen Erwartungen entsprochen. Ich wäre wirklich dankbar, wenn du in einer Woche zurückkommst, wir haben noch viel Arbeit vor uns.";
			link.l1 = "Sie können auf mich zählen, Mynheer Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Sie sind schlau, Kapitän. Genau. Nun, sprechen wir über die Details der bevorstehenden Mission...";
			link.l1 = "Ich bin ganz Ohr.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "Ich habe eine sehr ernste und wichtige Mission für Sie und ich erwarte, dass Sie alles nach meinen Anweisungen machen. Wie Sie wissen, sind die Beziehungen zwischen den Vereinigten Provinzen und England...nicht herzlich. Die Briten sind sicher, dass sie diejenigen sein sollten, die die Welt beherrschen. Problem ist - nicht jeder neigt dazu, solch eine Behauptung zu akzeptieren. Überall, wo sie hinfahren, um Geschäfte zu machen, können Sie sicher sein, dass die Niederländische Westindien-Kompanie zuerst dort war.\nWir Niederländer haben die größte Handelsflotte der Welt und unsere militärischen Geschwader können die Interessen der Republik sowohl hier als auch im Ausland verteidigen. Die Engländer beneiden uns um unsere Handelsmacht und sie tun, was sie können, um die Aktivitäten der Gesellschaft zu sabotieren. Jetzt gibt es einen bestimmten englischen Marinekapitän namens Richard Fleetwood. Obwohl er ein Kommissionsoffizier des Commonwealth ist, agiert er derzeit als Pirat. Er greift jedes Schiff an und plündert es, das es wagt, unter der niederländischen Flagge in der Karibik zu segeln. Er erklärt seine Handlungen als Gegenmaßnahmen gegen das 'Geisterschiff', das englische Händler versenkt. Er behauptet, dass dieses 'Geisterschiff' ein Freibeuter ist, der unter einem niederländischen Kaperbrief segelt.\nHaben Sie von dem 'Geisterschiff', Kapitän, gehört?";
			link.l1 = "Du kannst diese Art von Unsinn in jeder Taverne hören. Kauf einfach etwas Rum für einen alten Bootsmann und du wirst jede Geschichte hören, die du willst...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Diese Angelegenheit ist keine Trunkenboldfantasie. Ich habe die Aktionen dieses 'Geisterschiffs' untersucht. Ich fand heraus, dass sie ein Schiff aus Holz und Leinen ist und von gewöhnlichen Männern bemannt wird, eine Ketsch namens 'Mirage'. Sie steht unter dem Kommando eines Mannes namens Jacob van Berg, der sie als die legendäre 'Fliegende Holländerin' ausgibt.";
			link.l1 = "Van Berg? Das ist ein niederländischer Nachname. Ein echter 'Fliegender Holländer', hm?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Richtig. Jacob van Berg ist ein Holländer, ursprünglich aus Leiden. Aber die Republik hat ihn vor langer Zeit zum Galgen verurteilt. Er ist ein flüchtiger Verbrecher, ein Pirat, der nur in seinem eigenen Interesse handelt. Richard Fleetwood jagt van Berg. Diese Tatsache werden wir gegen diesen unverschämten Engländer verwenden.\nIch würde Fleetwood lieber nicht auf der Stelle töten, obwohl er es schon lange verdient hat. Der Tod wäre für ihn nicht genug. Ich möchte ihn nicht nur töten, sondern auch seinen Namen und seine Ehre zerstören. Das ist es, was ich will. Das wird auch den anderen arroganten englischen Schweinen eine Lektion erteilen.\nLassen Sie uns die Details besprechen.";
			link.l1 = "Mynheer, es klingt so, als ob es etwas Persönliches wäre...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Das geht dich nichts an. Du wirst Befehlen folgen, dann bekommst du bezahlt. Ich habe dank meines Agenten herausgefunden, wo Jacob van Berg mit seiner 'Mirage' lauert. Er operiert aus einer Stadt im südlichen Spanischen Haupt. Geh zu ihm und finde heraus, wo er sein Geisterschiff vertäut hat.\nDann töte ihn, finde seine 'Mirage', nimm sie als Preis und bring sie hierher zurück. Du musst die 'Mirage' einfangen, denke nicht einmal daran, sie zu versenken.";
			link.l1 = "Klingt einfach genug. Wo sollte ich nach van Berg suchen?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Alle Details werden Ihnen von meinem Agenten zur Verfügung gestellt. Sein Name ist Longway, ein Chinese. Ich stelle Ihnen mein persönliches Schiff, die Xebec 'Meifeng' für diese Mission zur Verfügung. Longway ist ihr Kapitän, aber er wird Ihre Befehle entgegennehmen.\nGehen Sie zur örtlichen Hafenverwaltung und legen Sie dort all Ihre Schiffe an. Kommen Sie zu mir zurück, wenn es erledigt ist.";
			link.l1 = "Gut, ich werde den Hafenmeister besuchen. Ich werde dich nicht zu lange warten lassen.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway wartet draußen auf Sie. Er wird Ihnen Ihr neues Schiff zeigen und Ihnen einige Informationen über den Standort von van Berg geben. Viel Glück, Kapitän, und enttäuschen Sie mich nicht. Denken Sie daran, dass Sie die 'Meifeng' zu mir zurückbringen müssen, also versuchen Sie nicht, sie zu versenken, während Sie die 'Mirage' nehmen.";
			link.l1 = "Auf meinem Weg!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Du inkompetenter Narr. Du hast deine Mission versagt, das Piratenschiff zu erobern. Alle meine Pläne sind ruiniert. Ich nehme dir 'Meifeng' weg. Geh weg, wir brauchen dich nicht mehr.";
			link.l1 = "Es tut mir leid. Auf Wiedersehen, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Du verdammter Idiot. Du hast die 'Meifeng' verloren. Das ist inakzeptabel... Ich werde dir die 'Mirage' abnehmen und deine Bezahlung als Entschädigung für meinen Verlust einbehalten. Geh, wir brauchen dich nicht mehr.";
			link.l1 = "Es tut mir leid. Auf Wiedersehen, Mynheer Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Mein Gott, du bist wirklich ein seltenes Exemplar. Ein inkompetenter Stümper UND ein Idiot. Du hast es nicht geschafft, die Mirage zu fangen und hast dabei die Meifeng verloren. Verpiss dich aus meinem Büro!";
			link.l1 = "Ich gehe.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Gut gemacht. Gerüchte von Ihrem Erfolg haben bereits meine Ohren erreicht. Van Berg ist tot und Sie haben sein Schiff erobert. Ihre Bezahlung beträgt 50.000 Pesos, nehmen Sie es.\nIch nehme die 'Meifeng' von Ihnen zurück. Nun ist es an der Zeit, dass Sie das Kommando über die 'Mirage' übernehmen, sie wird eine wichtige Rolle in der nächsten Phase spielen. Sind Sie bereit?";
			link.l1 = "Ja, Mynheer Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Jetzt kümmern wir uns um Fleetwood. Du wirst ihn mit dem 'Geisterschiff' Mirage, das er so begeistert gejagt hat, hervorlocken. Stelle eine Falle in der Nähe von Dominica auf, die Mirage wird als Köder dienen. \nZuerst lässt du Fleetwood wissen, dass die Mirage nicht weit von Dominica gesehen wurde. Unser tapferer Engländer wird alles fallen lassen, was er tut, und sofort nach Dominica eilen, um seine Beute zu suchen. Rede nicht direkt mit Fleetwood oder du wirst die Begegnung nicht überleben. Finde die Drogerie in St. John's. Der Apotheker John Murdock ist ein alter Freund von mir. \nSag ihm, dass du unter meinem Befehl handelst und er wird dir helfen, lokale Ohren mit saftigen Lügen über das 'Geisterschiff', das englische Händler um Dominica herum angreift, zu füllen.";
			link.l1 = "Ich kann das tun. Das Ziel ist es, Fleetwood auf Dominica zu überfallen, habe ich recht?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Genau. Longway und 'Meifeng' werden auf dich in der Nähe von Dominica warten. Ihr beide könnt den englischen Hund leicht erledigen. Entert sein Schiff und durchsucht seine Kabine. Ich will sein Logbuch. Ich werde dafür extra bezahlen.\nAber deine Hauptpriorität ist es, diesen Bastard Fleetwood zu töten, also wenn es unpraktisch ist, ihn zu entern - schick ihn auf den Grund. Vor allem musst du 'Mirage' um jeden Preis bewahren. Sie spielt eine entscheidende Rolle in der nächsten Phase des Plans.";
			link.l1 = "Verstanden.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Einen Rat, Kapitän. Werfen Sie nicht den Anker bei St. John's. Landen Sie in einer der Buchten der Insel und laufen Sie durch den Dschungel zur Stadt, sonst wird John nicht mit Ihnen sprechen. Wenn Sie zu viel Aufmerksamkeit auf sich ziehen, wird er so tun, als ob er Sie nicht kennt. Seien Sie auch auf See vorsichtig - die 'Mirage' ist unter den englischen Kolonien berüchtigt, daher vermeiden Sie ihre Kriegsschiffe und Siedlungen, wenn Sie nicht von einem Rudel Seewölfe überfallen werden wollen. Das ist alles. Gott sei mit Ihnen.";
			link.l1 = "Aye aye.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Sie sind zurückgekehrt, Kapitän... Haben Sie das Logbuch von Richard Fleetwood?";
				link.l1 = "Leider nein. Ich hatte keine Gelegenheit, sein Schiff zu betreten, bevor er es versenkte.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Sie sind zurückgekehrt, Kapitän... Haben Sie Richard Fleetwoods Logbuch?";
				link.l1 = "Leider habe ich das nicht getan. Ich konnte die Walküre entern und den Mann im Nahkampf töten, aber ich habe sein Tagebuch nicht gefunden. Einer seiner Männer zündete das Magazin an und wir hatten nur wenige Sekunden Zeit, um mit unserem Leben davon zu kommen.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Sie sind zurückgekehrt, Kapitän... Haben Sie Richard Fleetwoods Logbuch?";
			link.l1 = "Ich habe es gemacht. Hier ist es. Ich habe es geschafft, die Walküre zu entern, obwohl es eine knappe Sache war. Der Bastard hat sein Magazin auf seinem Schiff abgefeuert und es in die Luft gejagt. Wir sind gerade noch mit unserem Leben davongekommen.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Das ist verdammt schade, es hätte viele Fragen beantwortet, die wir haben. Es ist jetzt egal. Du hast diesen frechen englischen Hund getötet und das ist das Wichtigste. Hier ist deine Belohnung - 100.000 Pesos. Ich nehme die 'Mirage' von dir, wir werden dieses Schiff nach England zurückbringen.";
			link.l1 = "Was zum Teufel?! Sie ist ein feines Schiff, ich wollte sie behalten!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Ausgezeichnet! Sie sind ein sehr fähiger Mann. Wenn all unsere Kapitäne wie Sie wären, wäre die Niederländische Republik die erste unter den größten Seefahrernationen der Geschichte. Hier ist Ihre Belohnung - 100.000 Pesos und 50.000 Pesos extra für das Logbuch. Ich nehme die 'Mirage' von Ihnen, wir werden dieses Schiff nach England zurückbringen.";
			link.l1 = "Was zum Teufel?! Sie ist ein feines Schiff, ich wollte sie behalten!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Mein Junge, du bist ein ausgezeichneter Soldat, aber vertraue mir und meiner Erfahrung in politischen Angelegenheiten. Erinnerst du dich an das, was ich über Fleetwood gesagt habe? Ich werde seinen Namen und Ruf an einen Mühlstein nageln und in die Tiefe werfen. Und diese arroganten Adligen aus Port Royal werden schlucken und ersticken müssen.\nWir werden Richard Fleetwood zum Kapitän des 'Geisterschiffs' Mirage machen, einem Werwolf, der die beiden Nationen England und die Niederlande gegeneinander ausspielt, plündert, brandschatzt und friedliche Bürger beider nur um sich selbst zu bereichern ermordet! Was für eine Farce! Ich habe bereits Beweise und Zeugen vorbereitet, aber die 'Mirage' wird das Hauptereignis meines perfekten Spiels sein.";
			link.l1 = "Nun, dann fick mich. Du wirst mein hervorragendes Schiff für deinen Plan opfern!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Hüte deine Zunge, Junge, das ist Krieg. Manchmal müssen wir nicht nur Männer, sondern auch Schiffe und wohlhabende Siedlungen opfern, um unsere politischen Ziele zu erreichen. Jeder Krieg geht mit Verlusten einher...Apropos Verluste, ich habe schlechte Nachrichten für dich.\nWährend du weg warst, wurde Willemstad von englischen Freibeutern angegriffen. Die Festung schaffte es, sie zu vertreiben, aber nicht bevor sie mit Brandschiffen in den Hafen gelangten.\nDein Schiff wurde vor Anker erwischt und bis zur Wasserlinie niedergebrannt. Sie ist ein Totalverlust";
			link.l1 = "Mynheer, du machst wohl verdammt nochmal einen Scherz? Verdammt zur Hölle! Was soll ich jetzt tun?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Seien Sie nicht so verärgert Kapitän, ich habe auch gute Nachrichten. Um Ihre Empörung zu lindern, schenke ich Ihnen meinen Schönen Wind, die Xebec 'Meifeng'. Sie können das Schiff beliebig nutzen, innerhalb des Vernünftigen. Außerdem, treffen Sie mich morgen in der Residenz des Gouverneurs, Sie wurden für eine staatliche Auszeichnung mit dem Dank der Niederländischen Republik und Westindien Kompanie nominiert. Verlassen Sie die Stadt nicht, bis Sie sie erhalten haben, Kapitän.";
			link.l1 = "Das lindert meinen Verlust ein wenig. Ich fühle mich geehrt. Übrigens, Mynheer, wo ist Longway hin?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway ist plötzlich verschwunden, gleich nachdem ich ihm befohlen hatte, nach Dominica zu segeln. Ich habe den Verdacht, dass englische Agenten ihm auf den Fersen sind... oder vielleicht auch nicht. Ich ermittele.";
			link.l1 = "Ich verstehe. Seine Hilfe in Dominica wäre sehr willkommen gewesen. Fleetwood und seine 'Valkerie' waren ein furchterregendes Paar. Ich hoffe, dass Longway noch am Leben ist... Auf Wiedersehen, Mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Du bist nicht nur ein gewöhnlicher Clown, du bist der ganze Zirkus. Wir waren so nah am Finale und du hast es vermasselt... Ich werde dir 30.000 Pesos für Fleetwoods Beseitigung zahlen. Ich habe keine weiteren Missionen für dich und unsere Vereinbarung ist beendet. Raus hier.";
			link.l1 = "Wie du wünschst.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Ich habe schlechte Nachrichten für dich.\nWährend du weg warst, wurde Willemstad von englischen Freibeutern angegriffen. Das Fort konnte sie verjagen, aber nicht bevor sie mit Brandschiffen in den Hafen gelangten.\nDein Schiff wurde vor Anker erwischt und bis zur Wasserlinie abgebrannt. Es ist ein Totalverlust.";
			link.l1 = "Ich denke, ich kann mich dann einfach selbst ficken! Danke für nichts!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitän "+GetFullName(pchar)+"! Für die Beseitigung von Richard Fleetwood, einem gefährlichen Staatskriminellen, für die Aufdeckung der verräterischen englischen Verschwörung gegen die Republik, für Tapferkeit und Mut, werden Sie im Namen der Niederländischen Republik mit tausend goldenen Dublonen ausgezeichnet! \nSie erhalten auch dieses wertvolle Navigationstool - der Traum jedes Militärseemanns.";
			link.l1 = "Ich freue mich, der Republik zu dienen!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Herzlichen Glückwunsch noch einmal, mein Freund. Und bitte, besuchen Sie mich in einer Woche. Wir brauchen Sie für eine äußerst heikle Angelegenheit.";
			link.l1 = "Verstanden, Mynheer Rodenburg. Ich werde Sie in einer Woche besuchen.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Lassen Sie mich Ihnen eine Geschichte erzählen. Sie wird Ihnen helfen zu verstehen, wie heikel Ihre nächste Aufgabe ist. Vor einigen Monaten wurde eine Fluyt, die unter englischer Flagge nach Willemstad unterwegs war, vom verstorbenen Jacob van Berg angegriffen. Er eroberte das Schiff und versenkte es nicht weit von einer Insel, die auf keiner unserer Karten verzeichnet ist. Nur zwei der Passagiere auf der Fluyt überlebten. Ein Jude namens Solomon Shneur und seine Tochter Abigail. Alle anderen Passagiere kamen ums Leben, einschließlich des Rests ihrer Familie. Unsere beiden Juden erreichten die Insel, indem sie auf einigen Wrackteilen schwammen.\nSolomon schaffte es sogar, eine mit Familiengold gefüllte Truhe mitzuschleppen. Sehr sparsam von ihm. Ein anderer Charakter unserer Geschichte, Richard Fleetwood, segelte in der Nähe und hörte die Geräusche des Kampfes. Er kam zu spät, um van Berg zu erwischen, und die 'Mirage' floh. Fleetwood beschloss, die Insel auf Überlebende zu untersuchen.\nEr rettete Solomon und Abigail vor dem sicheren Tod auf dieser Wüsteninsel. Unglücklicherweise für den alten Juden hat Solomon kein Seemannsauge. Er verwechselte Richards 'Valkerie' mit Jacobs 'Mirage' und - aus Angst, der Pirat würde zurückkehren, um die Arbeit zu beenden - versteckte er sein Gold irgendwo auf der Insel. Als Ergebnis kamen er und seine Tochter hier ohne einen Pfennig an, abgesetzt von Fleetwood bei Blanca Lagoon, in der Nähe von Willemstad, ihrem ursprünglichen Ziel.\nSolomon hat mir diese Geschichte erzählt. Die Niederländische Republik unterstützt die freie Religionsausübung. Als Teil dieser Politik unterstützt die Kompanie die jüdische Gemeinschaft hier. Deshalb habe ich dafür gesorgt, dass sie ein Dach über dem Kopf haben und etwas zu essen und zu tragen haben. Ich habe ihren Ort oft besucht. Abigail ist eine... bemerkenswerte junge Frau. Aufrichtig und vertrauensvoll.\nIch werde Ihnen nicht lügen, Kapitän, ich will sie und ich beabsichtige, sie zu meiner Frau zu machen. Sie liebt mich im Gegenzug, aber etwas ist zwischen uns gekommen.";
			link.l1 = "Ihr Vater ist nicht gerade begeistert von einem goyim Schwiegersohn?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Der alte Salomon wäre im siebten Himmel, wenn ich Abigail heiraten würde, unbeschnittener Schwiegersohn oder nicht. Tatsächlich drängt er sie, meinen Antrag anzunehmen. Nein, nein, das geht über Jude und Heide hinaus. Ich bitte dich, mein Junge, dieses Problem für mich zu lösen. Sprich mit Abigail und finde heraus, was nicht stimmt\nDu bist ein Fremder, sie könnte dir Dinge erzählen, die sie vertrauten Leuten wegen ihrer bezaubernden Bescheidenheit nie erzählen würde. Shneurs Haus befindet sich rechts vom Büro der Gesellschaft, wenn du mit dem Rücken dazu stehst. Ich weiß, dass du ein Schmeichler bist\nAber denke daran: Richard Fleetwood war der wahre Kapitän des 'Geisterschiffs'... Behalte es im Hinterkopf, während du mit Abigail sprichst.";
			link.l1 = "Ha! Natürlich erinnere ich mich daran, Mynheer Rodenburg. Ist das nicht die offiziell anerkannte Tatsache? Dann werde ich keine Zeit verschwenden, ich werde sofort Ihren Liebsten besuchen.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Haben Sie wirklich die Insel gefunden, wo Salomon sein Gold versteckt hat? Das ist ausgezeichnet! Ich fing an zu denken, dass Sie jede Aufgabe bewältigen können... Haben Sie noch etwas in der Beute gefunden?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Nein, nichts anderes. Nur Geld.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "Es gab einen interessanten Gegenstand - einen Jadetotenkopf. Ich habe ihn Solomon gegeben, er sagte, es sei ein Familienerbstück. Er sagte auch, dass du vorhattest, es von ihm zu kaufen...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Gut dann. Es ist allerdings recht seltsam. Was auch immer... Ich bin Ihnen etwas schuldig, Herr, und ich werde es nie vergessen. Ich habe eine Belohnung für Sie vorbereitet - 50.000 Pesos und dieses Amulett. Es gehört jetzt Ihnen.";
			link.l1 = "Danke, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Ausgezeichnet! Ja, ich werde dieses Artefakt von Solomon kaufen, er braucht es nicht und ich habe einen sehr großzügigen Käufer dafür. Ich habe eine Belohnung für dich vorbereitet - 50.000 Pesos und dieses Amulett. Es gehört jetzt dir.";
			link.l1 = "Danke, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Ich habe im Moment keine Aufgabe, die eines Kapitäns wie Ihnen würdig ist. Aber verlassen Sie Curaçao nicht zu lange, bald werde ich Ihre Dienste wieder brauchen.";
			link.l1 = "Ich habe verstanden, Mynheer. Auf Wiedersehen!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, und das ist alles? Absolut absurd...wie sehr wie eine Frau. Hör mir zu, mein Junge, dieses Problem kann leicht gelöst werden. Ich weiß, wie viel Geld in Solomons Versteck war: 200.000 Pesos. Ich bin bereit, diese Summe für mein und Abigails Glück zu opfern. Ich gebe dir das Geld und du wirst Curacao für eine oder zwei Wochen verlassen. Dann kehrst du zu Solomon zurück und gibst ihm das Geld. Tu so, als hättest du das Versteck gefunden. Der Wolf wird gesättigt und das Schaf bleibt unberührt. Hier, nimm die benötigte Summe";
			link.l1 = "Ein guter und einfacher Plan. Lass es uns tun.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Segle auf das offene Meer hinaus und kehre in zehn Tagen zu mir zurück. Geh und mach etwas Nützliches. Suche nach Manga Rosa, stelle einige Materialien her, oder so etwas.";
			link.l1 = "Was auch immer Sie sagen, Mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Herrlich! Wieder einmal hast du die Arbeit perfekt erledigt. Ich bin dir zu Dank verpflichtet, Mynheer, und ich werde es nie vergessen. Ich habe eine Belohnung für dich vorbereitet - 50.000 Pesos und dieses Amulett. Es gehört jetzt dir.";
			link.l1 = "Danke, Mynheer Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Ja, genau so. Mein Freund, manchmal ist es schwer zu erkennen, wer dein Freund und wer dein Feind ist. Manchmal übersiehst du den Moment, in dem dein engster Vertrauter zu deinem Erzfeind wird. Unser gemeinsamer Bekannter aus St. John's, John Murdock - auch bekannt als Johan van Merden - ist ein ehemaliger Agent der Kompanie, der sich der englischen Marine verkauft hat.\nSeine neueste Mission ist es, einen der hellsten Sterne der Kompanie zu eliminieren... dich.";
			link.l1 = "Ich fühle mich geschmeichelt. Gut, dass du es mir gesagt hast, sonst hätte ich das nicht kommen sehen.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Genau, Kapitän. Er ist ein gerissener Hund. Finden Sie den Bastard und töten Sie ihn, bevor er zuschlägt. Segeln Sie nach Antigua und suchen Sie nach einem geheimen Eingang zu seiner Drogerie. Vor der Kirche gibt es eine Luke, die zu einem geheimen Tunnel führt. Benutzen Sie es.";
			link.l1 = "Ich werde mich darum kümmern.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Noch eine Sache, Kapitän. Sobald Johan tot ist, durchsuche seine Leiche, das Haus und den Keller. Er hat ein Archiv - ein dickes Hauptbuch, in dem er einige verdammt belastende Notizen während seiner Arbeit für die Gesellschaft niedergeschrieben hat. Diese Informationen werden uns alle zerstören, wenn unsere Feinde sie finden. \nFinde dieses verfluchte Archiv und bring es mir, ich werde extra dafür bezahlen. Jetzt geh. Gott beschütze dich, Kapitän "+pchar.name+", und versuche, in einem Stück zurückzukehren. Die Republik braucht dich!";
			link.l1 = "Ich verspreche Ihnen, Mynheer, in einem Stück zurückzukehren. Das ist sicherlich in meinem besten Interesse!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Ausgezeichnet, Kapitän! Ich bin froh, ich meine es wirklich. Haben Sie sein Archiv gefunden?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Ja, hier ist es. Es gab keine anderen Dokumente auf dem Leichnam des Chemikers oder in seinen Truhen.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Nein. Ich habe überall gesucht, aber nichts gefunden.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "Das ist sicherlich schade, aber ich bin damit einverstanden. Ich bin sicher, dass Johan nicht genug Zeit hatte, es den Engländern zu geben, sonst hätten wir schon Schlingen um unsere Hälse... Es ist wahrscheinlich, dass er es in irgendeinem geheimen Versteck versteckt hat... lasst es dort für immer bleiben! Ich gratuliere Ihnen, Kapitän, zum erfolgreichen Abschluss unserer Mission!";
			link.l1 = "Dankbarkeit!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Hervorragend! Jetzt ist es sicher, wo es hingehört. Du hast erneut bewiesen, dass du der Beste bist... Gib mir das Buch... Es gibt eine Belohnung für das Archiv - dieses feine Musket. Es hat mir mit großer Auszeichnung gedient und jetzt gehört es dir!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Was haben Sie vor, Kapitän? Mehrere Seiten fehlen - Seiten, die für mich sehr wichtig sind. Dachten Sie, ich würde es nicht bemerken, damit Sie sie gegen mich verwenden könnten? Oder hofften Sie, dadurch mehr zu bekommen? Ich fürchte, ich muss Sie in beiden Punkten enttäuschen.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Vertrauenswürdig) Ich entschuldige mich. Mein einziger Fehler war, dass ich das Archiv nicht vorher selbst überprüft habe.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Würde ich wirklich die Seiten herausreißen und dann das Archiv mit einem gleichgültigen Blick übergeben?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "Gier, Dummheit und Unverschämtheit treiben Menschen manchmal zu den wahnsinnigsten Taten, Kapitän.";
			link.l1 = "Keiner von diesen Dreien hat mich motiviert, das versichere ich Ihnen.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Also sagen Sie, van Merden hat diese Seiten entfernt und sie anderswo versteckt?";
			link.l1 = "Genau. Ich könnte zurückgehen und nach ihnen suchen - die ganze Apotheke auf den Kopf stellen, oder sogar ganz St. John's - wenn du es für notwendig hältst.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Keine Notwendigkeit, Herr. Das Meiste von dem, was wichtig ist, ist sowieso hier, und ohne die fehlenden Seiten stellt der Rest keine Bedrohung für mich dar.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Also, es ist eher ein Mangel an Fürsorge oder Neugier als Unaufrichtigkeit oder geheime Agenda? Glaubst du, es war schon so, als du es gefunden hast?";
			link.l1 = "Höchstwahrscheinlich, Mynheer Rodenburg. Vielleicht hat van Merden diese Seiten zuvor herausgerissen. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Vielleicht ist es zum Besten. Ohne diese Seiten stellt das übrige Archiv für mich keine Bedrohung dar - besonders in unwissenden Händen.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Es gibt eine Belohnung für das Archiv - dieses feine Musket. Es hat mir mit großer Auszeichnung gedient und jetzt gehört es dir!";
			link.l1 = "Danke!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Wir haben gut gearbeitet, Sie und ich, Kapitän. Es ist keine Übertreibung zu sagen, dass nichts davon ohne Sie geschehen wäre. Sie werden unglaubliche Karrierehöhen erreichen, wenn Sie weiterhin der Republik dienen, vielleicht sogar geadelt werden.";
			link.l1 = "Ich denke, das ist Auf Wiedersehen, Mynheer Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "Es ist Auf Wiedersehen, "+pchar.name+". Ich habe hier alles erreicht, was ich wollte, also kehre ich in einer Woche nach Amsterdam zurück. Meine neue Frau Abigail und mein Schwiegervater Solomon werden mich begleiten. Peter Stuyvesant hat bereits einen neuen Vize-Direktor für das Unternehmen gefunden, also sprechen Sie mit ihm, wenn Sie etwas brauchen\nFür Ihren Dienst schenke ich Ihnen die Meifeng. Sie gehört jetzt Ihnen, Kapitän, Sie haben sie verdient.";
			link.l1 = "Danke, Mynheer Rodenburg. Ich habe mich ziemlich an die Meifeng gewöhnt und habe bereits begonnen, sie als meine eigene zu betrachten.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "Und jetzt muss ich dich bitten, mich zu verlassen, mein Junge. Ich habe noch viel zu tun, bevor wir in See stechen... Besuche mich eines Tages in Amsterdam! Wir werden ein Getränk teilen und uns an die guten alten Zeiten erinnern...";
			link.l1 = "Ja, Mynheer. Ich hoffe, dass Sie alle in Ihrem neuen Leben glücklich und erfolgreich sind! Auf Wiedersehen!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Ja, Mynheer. Ich hoffe, dass Sie alle in Ihrem neuen Leben glücklich und wohlhabend sind!\n(durch zusammengebissene Zähne) ... Ich hoffe, wir sehen uns nicht wieder, du arroganter Tölpel. Warte nur, bis du die Freuden entdeckst, mit einer 'zurückhaltenden' jüdischen Furie verheiratet zu sein.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Gott im Himmel! Fleetwoods Hund! Du magst diesen Tag gewinnen, aber Lucas Rodenburg wird sein Leben teuer verkaufen.";
			link.l1 = "Ich glaube nicht. Du wirst mir dein Leben umsonst überlassen, du niederländischer Geizhals.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Aus der Tiefe der Hölle werde ich dir ins Maul scheißen! Ich habe gerade den Laderaum in Brand gesetzt und das Feuer wird sich bald auf das Pulvermagazin ausbreiten! Unsere Schiffe sind in engem Gefecht verkeilt, so dass es keine Hoffnung auf Flucht gibt! Du wirst verbrennen oder die Haie füttern!";
			link.l1 = "Verdammt! Männer, zieht euch zurück, wir müssen uns zurückziehen!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Ich gehe nicht, bis deine Seele deinen Körper verlässt. Halte still, das wird wehtun.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Warum bist du hier, du Bastard? Hier, um mich zu verspotten? Vielleicht wirst du mir endlich sagen, welchen Platz du in diesem Spiel hast. Du warst es, der die Brigantine gefangen genommen hat, richtig? War das von Anfang an dein Plan?";
			link.l1 = "Ich bin hier, um Ihnen einige Grüße zu übermitteln, Lucas Rodenburg. Die besten Grüße von John Merdock, den Sie verraten haben. Sie waren meine Aufgabe und ich habe sie erledigt. Auf Wiedersehen für jetzt.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! Also war er der Mann hinter all dem! Dieser alte Schurke! Aber das Spiel ist noch nicht vorbei. Jacob van Berg kommt auf dich zu und du wirst nicht entkommen! Du und dein Schiff sind verloren, du erbärmlicher Seebettler!";
			link.l1 = "Spare deine Stimme für das Henkersgericht, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
