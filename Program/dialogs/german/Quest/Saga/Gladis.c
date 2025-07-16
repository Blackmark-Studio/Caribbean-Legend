// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ach, Kapitän! Wissen Sie, ich habe Helen alles erzählt. Sie können sich nicht vorstellen, was für eine Last mir von der Seele genommen wurde!";
				link.l1 = "Sie haben alles richtig gemacht, Miss McArthur. Das Mädchen muss die Wahrheit wissen. Und ich bin wegen ihr hier.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Grüße, "+pchar.name+"! Ich bin froh dich zu sehen! Möchtest du etwas Rum?";
				link.l1 = "Danke, Miss McArthur, aber ich bin gerade zu beschäftigt.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Was möchten Sie, Mister?";
			link.l1 = "Sind Sie Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Ich bin es. Ich erinnere mich nicht an dich, junger Mann. Würdest du mir also erklären, was du von mir willst?";
			link.l1 = "Ich interessiere mich für die Geschichte des Verschwindens Ihrer Tochter, Frau McArthur. Was hat Sie glauben lassen, dass sie verschwunden ist? Ich habe gehört, dass Helen eine sehr geschickte Crew hatte...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ach, ich bin absolut sicher! Schau, der Todestag meines verstorbenen Mannes war vor fünf Tagen. Helen liebte ihren Vater und sie würde dieses Datum nie verpassen. Sie war nur für ein paar Tage weg, um eine Ladung rotes Holz von den freundlichen Miskito-Leuten zu erhalten.\nDie Indianer respektieren und fürchten unseren Schirmherrn Jan Svenson, sie würden ihr nie Schaden zufügen. Mister Svenson hat bereits mit ihnen gesprochen. Das Holz wurde am selben Tag geladen. Niemand hat Helen seitdem gesehen.";
			link.l1 = "Vielleicht haben die Piraten sie angegriffen?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Unsinn! Sie müssen bereits wissen, dass Mister Svenson einer der fünf Piratenbarone und Mitglied des Rates der Brüder der Küste ist. Keine Piraten dürfen hier ohne seine Erlaubnis jagen. Es könnte allerdings ein Neuling sein...";
			link.l1 = "Und was ist mit den Spaniern? Könnte sie auf eine spanische Patrouille gestoßen sein?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Ich verstehe nicht viel von Politik, aber man sagt, dass die hiesigen Gold- und Silberminen völlig ausgebeutet sind, kaum noch Schätze übrig, für die es sich lohnt, das Leben edler Hidalgos zu riskieren. Daher sind sie hier selten zu Gast. Außerdem sind die Indianer ihnen gegenüber feindlich gesinnt.\nEin zufälliges Treffen mit einer spanischen Patrouille hätte für Helen nicht schlecht enden können, sie hat aus ihrer Sicht nichts Illegales getan. 'Regenbogen' flog unter niederländischer Flagge und alle Helen's Papiere waren in Ordnung, einschließlich einer Handelslizenz.";
			link.l1 = "Gab es vor ihrer letzten Reise etwas Besonderes? Vielleicht ein seltsames Ereignis, das Sie verpasst haben?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ach nein! Gott sei Dank führen wir hier ein friedliches Leben. Allerdings hat Helen vor ein paar Wochen einen Brief von einem weiteren unerwünschten Verehrer erhalten, der um ein Date bat. Sie ist ein hübsches Mädchen, aber kein reiches. \nAlso hat sie viele Verehrer, obwohl sie keinen von ihnen mag und sie will nicht heiraten. Sie hat bereits auf diese Weise viele Leute getäuscht. So leichtfertig, genau wie ihre Mutter es war!";
			link.l1 = "Sie sehen nicht aus wie diese Art von Frau, Miss McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Was? Ach, egal, ich bin am Boden zerstört. Was habe ich gesagt? Ach ja, der Brief. Nun, dieser Brief wurde von Jimmy Higgins geschrieben. Er ist einer von Jackmans Leuten und lebt in Maroon Town. Er besucht unsere Stadt ziemlich oft. Jackman ist auch ein Piratenbaron, aber Mister Svenson mag ihn nicht, ich weiß nicht warum.";
			link.l1 = "Und Helen?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Oh, sie lachte laut. Sie hatte einen Tag zuvor einen Heiratsantrag vom Kapitän einer englischen Korvette erhalten und selbst ihn abgelehnt. Und jetzt dieser gewöhnliche Bootsmann von einer alten Piratenkiste... Keine Chance, die Tochter von Sean McArthur verlangt einen eindrucksvolleren Ehemann!";
			link.l1 = "Und wie hieß dieser englische Kapitän?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Oh, wie sollte ich das wissen? Echte Herren sind hier seltene Gäste. Es tut mir leid, ich wollte Sie nicht beleidigen. Fragen Sie diesen Higgins. Er muss sich an seinen Namen erinnern. Jimmy versuchte, mit diesem Kapitän um Helen zu duellieren. Seine Kumpels haben es kaum geschafft, ihn davon abzuhalten. Aber beide haben Blueweld ein paar Tage bevor Helen absegelte, verlassen.";
			link.l1 = "Nun, danke für deine Geschichte. Ich werde versuchen, deine Geliebte zu finden. Wenn ich etwas erfahre, werde ich es dir oder Mister Svenson erzählen. Ich hoffe, deine Tochter lebend und in einem Stück zu finden.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Gehen Sie sie suchen? Gott sei mit Ihnen, möge er Sie führen und Ihre Hand stärken! Ich werde für Sie beten! Nennen Sie mir Ihren Namen, ehrenwerter Mann?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". Ich hoffe, bald mit guten Nachrichten zurückzukehren, Miss McArthur. Auf Wiedersehen!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Erkundungsmodus: Questdauer verdoppelt");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Haben Sie irgendwelche neuen Informationen über meine arme Tochter, "+pchar.name+"?";
			link.l1 = "Es tut mir leid, Fräulein McArthur, ich habe bisher nichts Neues zu berichten, aber verzweifeln Sie nicht. Ich werde meine Suche fortsetzen. Das Fehlen von schlechten Nachrichten ist auch eine gute Nachricht an sich.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Sie waren zu spät, Kapitän. Der Körper meiner armen Tochter wurde an den Ufern von Antigua gefunden. Oh Herr, wie sie sie sogar vor ihrem Tod gefoltert haben! Ich habe es nicht geschafft, mein schönes Mädchen zu bewahren...";
			link.l1 = "Es tut mir leid. Es gab nichts, was ich hätte tun können...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ach, junger Mann, bitte, lass mich allein mit meiner Trauer...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Ich weiß gar nicht, wie ich Ihnen danken soll, Kapitän, dass Sie meine Tochter gerettet haben. Sie hat mir alles erzählt und ich bewundere Ihre Tapferkeit und Ehre. Hier, nehmen Sie diese goldenen Dublonen. Es ist nicht viel, aber ich biete sie in aller Aufrichtigkeit an. Und denken Sie nicht einmal daran, abzulehnen!";
			link.l1 = "Gut, Gladys, das werde ich nicht tun. Aber ich habe Ihre Tochter nicht für Münzen gerettet und ich hoffe, Sie wissen das.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Behalte dieses Geld für dich, Gladys. Du brauchst es mehr als ich.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Ich bin froh, dass ich Ihnen irgendwie für Ihre ehrenhafte Tat danken konnte. Die Türen meines Hauses stehen Ihnen immer offen. Helen und ich würden uns freuen, Sie jederzeit zu sehen.";
			link.l1 = "Danke, Miss McArthur. Ich werde Sie und Helen besuchen, wenn sich die Gelegenheit bietet.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ach, bitte... Ich wollte mich nur für Ihre ehrenhafte Tat bedanken. Wissen Sie, dass die Türen meines Hauses Ihnen immer offen stehen. Helen und ich werden uns freuen, Sie jederzeit zu sehen.";
			link.l1 = "Danke, Miss McArthur. Ich werde Sie und Helen besuchen, wenn sich die Gelegenheit bietet.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Kapitän, Sie sind immer willkommen in unserem Hause! Sind Sie hier für Helen? Ich fürchte, sie hat sich in ihrem Zimmer eingeschlossen - muss von den letzten Tagen erschöpft sein. Machen Sie sich keine Sorgen, das passiert ihr manchmal.";
				link.l1 = "Wirklich? Bist du sicher, dass es ihr gut geht?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ach, Monsieur de Maure! Ich freue mich immer, den Retter meiner Tochter in meinem Haus zu sehen. Möchtest du Helen sehen? Sie ist oben in ihrem Zimmer. Nach dem Verlust der 'Regenbogen' und ihrer wunderbaren Rettung vermeidet sie es, auszugehen. Es ist das erste Mal, dass ich sie in einem solchen Zustand der Verwirrung gesehen habe...";
			link.l1 = "Danke, Miss McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ach, Monsieur de Maure! Ich bin immer froh, den Retter meiner Tochter in meinem Haus zu sehen. Möchten Sie Helen sehen?";
			link.l1 = "Nein. Ich möchte Ihnen einige Fragen stellen und hoffe wirklich auf Ihre Offenheit. Helens Sicherheit hängt davon ab. Ist Ihnen dieser Ring bekannt?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Herrgott! Das ist... der Ring ihres Vaters!";
			link.l1 = "Herr McArthur's?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Nein. Helen ist unsere Stieftochter, aber sie weiß das nicht, ihre Eltern starben, also habe ich mich entschieden, sie als mein Kind aufzunehmen. Sean hat sie adoptiert, aber selbst er wusste nicht, dass sie nicht meine Tochter ist.";
			link.l1 = "Also, wer sind ihre echten Eltern?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Ich weiß, dass ihr Vater ein Pirat namens 'Butcher' auf der Fregatte 'Neptune' war. Ich habe ihn nur zweimal gesehen. Und ihre Mutter war eine schöne junge Frau, rote Haare, gekleidet in Männerkleidung. Das ist ziemlich alles, was ich euch über sie erzählen kann, außer dass sie eine schlechte Mutter war.\nIch würde niemals so ein Baby in die Hände von Fremden geben. Beide sind tragisch gestorben. Und der versprochene Kurier hat sich zwanzig Jahre später gezeigt und es warst du. Hat Butcher dich geschickt? Lebt er noch?";
			link.l1 = "Beruhigen Sie sich, Fräulein Gladys! Es gibt keine Gründe zu vermuten, dass Butcher wiederbelebt ist, obwohl Sie die zweite Person sind, die diese Idee hatte. Ich habe kürzlich einen Mann getroffen, der Ihnen diesen Ring zeigen sollte...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "Ein einfacher Zwischenfall hatte ihn daran gehindert, dies rechtzeitig zu tun und er litt sein ganzes Leben lang, weil er den letzten Befehl seines Kapitäns nicht erfüllt hatte. Er starb vor nicht allzu langer Zeit und... nun, genug traurige Nachrichten. Sag mir, Gladys, hat Helens Mutter ihrem Kind nicht irgendein Andenken hinterlassen? Vielleicht eine Kleinigkeit?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Sie hinterließ mir ein seltsames Stück einer alten Karte. Scherzte, es sei ihr Erbe. Was kann dieses Stück Papier schon nützen? Ich glaube, es war nur ein schlechter Scherz. Sie war übererregt und ein wenig neben der Spur. Aber ich habe dieses 'Geschenk' aufbewahrt.\nWer weiß... Wenn du willst, kann ich es dir geben, wenn du versprichst, mir eines Tages die ganze Geschichte zu erzählen.";
			link.l1 = "Absolut, Miss McArthur. Ich werde diesen Fetzen eine Weile mit mir herumtragen. Ich muss mit Mister Svenson sprechen.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie haben uns wieder geholfen, Monsieur de Maure! Und ich habe keine Ahnung, wie ich Ihnen danken soll. Nehmen Sie zumindest die Pistole meines Mannes. Er war immer stolz darauf und sagte mir, dass sie sehr selten ist. Sie liegt schon lange hier. Lassen Sie es Ihnen dienen! Nehmen Sie es, nehmen Sie es!";
			link.l1 = "Danke, Gladys. Diese Pistole ist wirklich ausgezeichnet. Danke und auf Wiedersehen.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Lass diese Pistole Helen dienen. Ich habe genug Waffen.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Aber warum lehnst du ständig meine Geschenke ab? Du machst mich traurig...";
			link.l1 = "Ich denke, dass ich Sie jetzt glücklich machen kann. Ich werde das Gold zurückgeben, das der Kurier Ihnen für die würdige Aufbewahrung der Tochter von Kapitän Butcher liefern sollte. Sicher, diese Dublonen werden Ihre Liebe und Loyalität nicht vollständig zurückzahlen, aber sie gehören Ihnen sowieso. Sie können damit machen, was Sie wollen.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ach, Kapitän! Ich weiß nicht, was ich sagen soll... Ich könnte mir nicht vorstellen, dass solche... ehrenwerte Männer überhaupt existieren! Geh zu meiner Tochter und erzähl ihr die gute Nachricht!";
			link.l1 = "Ich bin auf dem Weg, Miss McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Meinst du das Ernst? Was meinst du damit?";
			link.l1 = "Gemäß der Forderung von Mister Svenson werde ich Helen als Offizierin auf meinem Schiff einstellen. Sie ist in großer Gefahr. Helen wird soliden Schutz benötigen, während Jan und ich diese Angelegenheit klären. Ich hoffe, dass ich einen solchen Schutz bieten kann.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ach, das ist so gut! Ich würde es nicht wagen, dich selbst darum zu bitten. Es wird der allerbeste Schutz für mein Mädchen sein. Helen wird so froh sein, wieder zu segeln!";
			link.l1 = "Danke für Ihr Kompliment, Miss McArthur. Und jetzt muss ich Ihre... Stieftochter sehen.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Oh, Gott! Mein kleines Mädchen!";
			link.l1 = "Gladys, weißt du nicht, wie man anklopft?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Oh, verzeiht mir, junge Leute! Ich gehe! Helen, erinnere dich an das, was ich dir gesagt habe!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Ich denke, diesmal hat sie sich einfach überarbeitet. Sie hat mir alles erzählt, Kapitän! Danke, dass Sie ihr gestern bei der Auswahl eines neuen Schiffes geholfen haben!";
			link.l1 = "Hä? Hm, bitte schön. Auf Wiedersehen, Frau MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
