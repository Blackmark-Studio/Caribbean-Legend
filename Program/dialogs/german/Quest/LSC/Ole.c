// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was möchtest du?";
			link.l1 = "Nichts.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oups... Hallo, Onkel. Hast du eine weiße Perle? Gib mir die weiße Perle...";
			link.l1 = "Hm. Guten Tag. Bist du... der weiße Junge?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Perle! Weiße Perle für den weißen Jungen! Hast du eine weiße Perle, Onkel?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, ich habe keine Perlen, aber ich kann dir diese Perle geben. Sie ist weiß und genau wie die Perle. Ist das in Ordnung für dich?";
				link.l1.go = "store_2";
			}
			link.l2 = "Nein, ich habe keine Perlen, weder weiße noch rote. Ich bin kein Mädchen oder Indianer, um Perlen zu tragen. Sag mir ...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Perle! Weiße Perle! Keine Perle - kein Gespräch. Schlechter Onkel... Gib mir eine Perle!";
			link.l1 = "Verdammt! So ein verrückter Kerl! Das Schlangenauge und Chimiset hatten recht - er ist ein schwacher Kopf... Welche Art von Perle braucht er?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Gib eine Perle, Onkel. Guter Onkel... Weiße Perle!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hier, nimm deine Perle. Ist das, was du willst?";
				link.l1.go = "store_2";
			}
			link.l2 = "Ach, verdammt...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ja, ja! Es ist so! Onkel hat eine Perle gegeben! Danke, guter Mann! Jetzt hat Ole eine weitere Perle. Bald werde ich Mama sehen...";
			link.l1 = "Ich freue mich für dich. Nun, können wir jetzt sprechen?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Sicher, guter Mann. Bist du ein guter Mann, Onkel? Wir werden Freunde sein. Ole wird sich freuen zu reden. Wie ist dein Name?";
			link.l1 = "Mein Name ist "+pchar.name+". Ole, ein Mann hat mir von dir erzählt und er ist nicht mehr hier. Er sagte, dass du ihm geholfen hast und du kannst mir helfen.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "Onkel gab Ole eine Perle - er ist ein guter Onkel. Ole hilft gerne guten Menschen. Es gibt nicht viele gute Menschen - böse Onkel sind überall. Ich werde dir sicher helfen. Ich helfe gerne.";
			link.l1 = "Schön! Nun, wir sind jetzt Freunde. Ole, sag mal, erinnerst du dich an einen Mann mit roter Haut und einem prächtigen Federhut? Er hat mir erzählt, dass du ihn vor langer Zeit gerettet hast.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Ich erinnere mich an diesen Onkel. Er ist ein guter Mann. Ich habe ihn gerettet. Ich habe ihn zur Statue gebracht. Und vor kurzem habe ich einen weiteren guten Mann aus dem Laderaum mit Essen gerettet. Ich habe ihn vor den bösen Onkeln des Admirals gerettet. Sie hätten ihn getötet. Ich wollte ihn auch zur Statue bringen, aber er hat abgelehnt. Völlig.";
			link.l1 = "Aus dem Laderaum? Heh, ich vermute, ich weiß, wen du meinst... Und ich kenne diesen Onkel. Sag mir, Ole, wer ist der Mann, den du gerettet hast?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "Sein Name ist Onkel Nathan. Er ist krank, sehr-sehr krank. Er konnte kaum gehen, als Ole ihn fand.";
			link.l1 = "Sicher... Es ist seltsam, dass er es überhaupt schaffen konnte.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Nein, das ist nicht seltsam. Ich habe ihn gefunden und ihm etwas Feuerrum gegeben. Ich bin in das Loch geschwommen, weil es auf diesem Schiff Essen gibt. Schlechte Männer verschließen die Tür, aber ich öffne sie immer. He-he-he... Dämliche schlechte Männer. Sie locken Krabben an, das weiß ich. Schlechte Männer\nIch bin dorthin gegangen und habe Nathan gefunden. Es ging ihm nicht gut. Ich hatte Feuerrum - ich gab ihm etwas zu trinken, also ging es ihm besser. Dann gab ich ihm die Tinktur, ich habe immer eine dabei, für den Fall, dass eine gruselige Krabbe Ole beißt. Der gute Onkel Chimiset hat mir gesagt, dass ich das tun soll...";
			link.l1 = "Hast du ihm ein Gegengift und Rum gegeben? Heh, du bist nicht so ein Narr wie sie alle denken. Gut gemacht, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Böse Onkel halten Ole für einen Narren und ärgern ihn: Ole, der Narr... Ole ist kein Narr, er muss nur alle weißen Perlen sammeln, sonst schickt ihn seine Mutter fort. Gibst du mir später eine weitere Perle?";
			link.l1 = "Hm... Sicher, Ole, wir sind Freunde. Sag mir, wie wolltest du Hawk... Onkel Nathan zur Statue schicken. Onkel Chimiset hat mir erzählt, dass sie mit dem Schiff versunken ist...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "Statue liegt am Grund. Ole weiß. Aber es ist nicht tief und guter Onkel Henrik kann Onkel Nathan dorthin schicken. Onkel Henrik weiß, wie man unter Wasser geht. Aber es gibt viele gruselige Krabben. Ole hat Angst vor ihnen. Sie beißen schmerzhaft.";
			link.l1 = "Onkel Henrik? Wer ist er?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Onkel Henrik lebt unter den bösen Onkeln Narwale. Jeder kennt ihn. Er kann unter Wasser laufen und er bringt den Onkeln Narwale bei, wie man dort taucht. Onkel Henrik ist freundlich, er gab Ole eine weiße Perle.";
			link.l1 = "Und wie lassen dich die Narwale rein? Oder ist ihr Territorium für dich offen?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... Böse Onkel lassen Ole nicht rein, aber Ole kann nachts in jedes Zimmer ihrer Schiffe eindringen. Sie sind groß und laut, aber Ole ist leise und vorsichtig. Und ich habe Onkel Henrik getroffen, als ich um das Schiff herumgeschwommen bin, von dem aus Onkel Henrik taucht. Onkel Henrik hat Ole eine weiße Perle gegeben und jetzt sind wir Freunde.";
			link.l1 = "Interessant... Ich möchte auch ein Freund von Onkel Henrik sein.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Du willst tauchen und zur Statue gehen? Sie ist dort, im Wrack des alten Schiffes. Dort gibt es viele große und beängstigende Krabben. Hast du keine Angst vor ihnen? Sie können beißen.";
			link.l1 = "Nein, ich fürchte sie nicht. Ich habe bereits einen getötet, also sollten sie besser Angst vor mir haben.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Ach, "+pchar.name+" ist sehr mutig! Dann solltest du zu Onkel Henrik gehen, er wird dir beibringen, wie man auf dem Grund läuft und du wirst dort jede Krabbe töten. Du wirst dort auch eine weitere große Perle für Ole finden. richtig?";
			link.l1 = "Sicher, das werde ich. Aber zuerst muss ich Onkel Henrik finden.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "Und warum ihn finden? Er lebt auf dem Schiff namens 'San Gabriel', in der Werkstatt. Aber die bösen Onkel Narwale können dich vielleicht nicht willkommen heißen.";
			link.l1 = "Ich werde mich selbst um die bösen Onkel kümmern. Und die letzte Frage, wo ist Onkel Nathan jetzt? Ich habe ihn gesucht und er ist einer der Gründe, warum ich hier bin.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Ich verstecke Onkel Nathan in meinem Heiligtum auf der 'Fernanda'. Es ist weit weg und niemand lebt dort. Jeder denkt, dass es bald sinken wird, aber Ole weiß das Gegenteil. Ich habe Onkel Nathan gerettet und ihn dorthin gebracht\nEr ist immer noch sehr krank und trinkt die ganze Zeit Feuerrum. Er kann kaum laufen und nichts schwerer als fünf Pfund heben. Mir tut Onkel Nathan leid, ich bringe ihm Feuerrum aus Truhen und Essen aus dem Frachtraum der bösen Männer des Admirals. Ich koche ihm auch Ratten, die ich fange. Sehr leckere Ratten!";
			link.l1 = "Leckere Ratten? Ich verstehe. Also ist Nathan auf dem Schiff namens... wie haben Sie gesagt - der 'Fernanda'? Ich kenne sie nicht...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Onkel "+pchar.name+", Ich habe dir gerade gesagt, dass es nicht weit von hier ist. Du musst schwimmen, um zu ihr zu gelangen. Es gibt eine Tür an ihrem Heck, aber Onkel Nathan öffnet sie nicht. Ole hat ihm gesagt, dass er es nicht tun soll. Aber wenn du ein Freund von Onkel Nathan bist, werde ich dir sagen, wie man sie öffnet. Klopf so an die Tür: klopf-klopf... klopf-klopf. Dann wird er sie öffnen.";
			link.l1 = "Ich werde das in Erinnerung behalten. Danke, Ole! Du hast mir wirklich geholfen! Ich weiß nicht, wie ich dir ordentlich danken soll.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Bring mir noch eine weiße Perle. Wenn du sie natürlich findest.";
			link.l1 = "Ach, ja! Weiße Perlen! Gut. Bis dann, Ole!";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ach, Onkel "+pchar.name+"! Froh dich zu sehen! Wie geht es dir?";
			link.l1 = "Danke, Ole, mir geht es gut. Ich freue mich auch, dich zu sehen.";
			link.l1.go = "exit";
			link.l2 = "Hör zu, Ole, du hast gesagt, dass die Piraten des Admirals die Tür zum Laderaum schließen und du öffnest sie immer wieder... Alle Kisten dort sind geschlossen und du hast gesagt, dass du Rum für Onkel Nathan aus ihnen nimmst. Wie machst du das?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole hat einen Satz feiner Schlüssel. Sie öffnen jede Tür oder Truhe. Nun, nicht alle. Einige können nicht geöffnet werden, aber die meisten schon. Ole hat sie in der Kabine des bösen Onkels Jurgen gefunden. Er arbeitet jeden Tag mit seinem Hammer in der Nähe seines Ofens. Er stellt Schlösser und Schlüssel her. Und er macht auch große und furchterregende Musketen für die bösen Narwale.";
			link.l1 = "Ich verstehe. Ole, kannst du mir diese Schlüssel verkaufen? Ich kann dafür bezahlen...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "Gut, Onkel "+pchar.name+", Ich werde dir die Schlüssel verkaufen. Ich werde nur den für mich behalten. Er öffnet den Raum des Admirals. Dort gibt es viel Essen und Rum für Onkel Nathan. Es sind sowieso keine Perlen und Rum mehr in den Truhen übrig.";
			link.l1 = "Wie viel möchtest du dafür haben?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Erzähl mir zuerst, Onkel "+pchar.name+", hast du ein großes Schiff?";
			link.l1 = "Ja, das habe ich. Aber sie ist nicht hier, sie ist im äußeren Ring. Aber ich werde die Insel bald verlassen und mit meinem großen Schiff hierher zurückkehren, für Onkel Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Für Onkel Nathan? Oh, das ist wunderbar! Hör zu, versprich mir, mich auf deinem großen Schiff von hier wegzubringen und lass mich so lange mit dir segeln, wie ich brauche. Ich kann nützlich sein. Ich kann Ratten fangen und kochen... Gib mir auch fünf weiße Perlen. Und ich gebe dir die Schlüssel.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Sicher! Hier sind deine Perlen. Nimm sie.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Ratten fangen und kochen? Heh! Eine interessante Fähigkeit. Sicher, Ole, wir haben einen Deal. Ich bringe dir fünf Perlen und mein Wort.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ach, Onkel "+pchar.name+"! Froh dich zu sehen! Wie geht es dir?";
			link.l1 = "Danke, Ole, mir geht's gut. Ich freue mich auch, dich zu sehen.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Ich habe dir fünf weiße Perlen für deine Schlüssel gebracht.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Perlen! Weiße Perlen! Onkel "+pchar.name+" hat Perlen an Ole gegeben! Bald werde ich dich sehen, Mama!... Onkel "+pchar.name+", versprichst du, dass du mich hier wegbringst, wenn du zurückkommst?";
			link.l1 = "Ich tue es, Ole. Ich habe noch keine Ratten gegessen. Ich werde dich mitnehmen.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Danke, danke, guter Onkel "+pchar.name+"! Nimm deine Schlüssel. Es ist einfach, sie zu benutzen, stecke sie einfach einzeln ein und versuche es. Einer von ihnen wird schließlich ein Schloss öffnen, das du brauchst. Wenn es das nicht tut, dann ist das Schloss zu knifflig und du wirst definitiv einen speziellen Schlüssel brauchen.";
			link.l1 = "Ich verstehe. Ich nehme an, ich werde es handhaben.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Warte, Onkel "+pchar.name+"! Ich habe noch einen Schlüssel. Er ist hübsch und klug. Der böse Onkel Jurgen macht keine Schlüssel wie diesen. Ich weiß nicht, was er öffnet, aber vielleicht findest du es heraus. Sieh mal, es ist ein sehr hübscher Schlüssel, du hast sicher noch nie so etwas gesehen.";
			link.l1 = "Zeig mir... Ja, der Schlüssel ist sehr interessant. Aber was nützt er, wenn du nicht weißt, was damit geöffnet werden kann?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Onkel "+pchar.name+", , du bist sehr merkwürdig. Was bringt's? Wenn es den Schlüssel gibt, dann gibt es irgendwo das Schloss. Wenn es das Schloss gibt, dann gibt es irgendwo die Münze. Ich habe den Schlüssel auf der Insel gefunden. Das bedeutet, dass das Schloss auch hier ist. Daran besteht kein Zweifel. Es ist ein kluger Schlüssel und nur sehr wertvolle Gegenstände werden mit einem solchen Schlüssel verschlossen. Ole weiß es.";
			link.l1 = "Ehrlich gesagt, du bist lustig, Ole. Gut, ich kaufe es. Willst du Perlen dafür?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Ja, Ole will fünf Perlen. Wirst du sie geben, Onkel "+pchar.name+"?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Hier, nimm deine Perlen.";
				link.l1.go = "key";
			}
			link.l2 = "Ich habe sie nicht, aber ich werde dir auf jeden Fall Perlen bringen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Perlen! Weiße Perlen für den weißen Jungen! Für seine Mamma! Hier, Onkel "+pchar.name+", nimm den Schlüssel. Und du wirst das Schloss finden, Ole weiß. Du bist mutig, du fürchtest dich nicht einmal vor gruseligen Krabben.";
			link.l1 = "Ach, bring mich nicht zum Lachen, Ole! Danke für den Schlüssel. Wir sehen uns!";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ach, Onkel "+pchar.name+"! Froh, dich zu sehen! Wie geht es dir?";
			link.l1 = "Danke, Ole, mir geht es gut. Ich freue mich auch, dich zu sehen.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Ich habe dir fünf weiße Perlen für deinen Schlüssel gebracht.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ach, Onkel "+pchar.name+"! Froh dich zu sehen! Wie geht es dir?";
			link.l1 = "Danke, Ole, mir geht's gut. Ich freue mich auch, dich zu sehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, Onkel "+pchar.name+", du bist zurück! Du bist zurück auf dem großen Schiff! Nimmst du mich von hier mit? Onkel "+pchar.name+", du hast es mir versprochen, erinnerst du dich?";
			link.l1 = "Sicher, ich tue, Ole. Willkommen an Bord! Ich vermute, dass die Ratten in Schwierigkeiten sind, ha-ha!";
			link.l1.go = "return_1";
			link.l2 = "Wirklich? Und wann habe ich dir das versprochen? Ich erinnere mich nicht an solche Versprechen...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Danke, Onkel! Ole wird nützlich sein, du wirst sehen! Oh, vielleicht werde ich Mama sehen? Ich bin jetzt auf dem Weg!";
			link.l1 = "Mach nicht so'n Stress, Ole. Du kannst deine Sachen packen. Ich werde nicht sofort segeln.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Du hast es mir versprochen, das hast du! Du hast versprochen, Ole von hier wegzubringen! Böser Onkel! Du hast Ole betrogen! Schlechter Onkel!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Onkel, Onkel... Ich brauche noch eine weiße Perle. Bitte, gib Ole eine weiße Perle!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Ich wusste, dass du danach fragen wirst. Hier, nimm deine Perle. Zufrieden?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Oh, und was für ein Ärger... Ich habe keine Perlen mehr, Ole, ich habe keine!";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Danke dir! Guter, guter Onkel "+pchar.name+"! Ole hat noch eine Perle und es sind nicht viele Perlen übrig! Und ich werde zur Mutter gehen...";
			link.l1 = "Oh, und warum bist du so merkwürdig...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = int(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Danke für eine Perle, guter Onkel "+pchar.name+"!";
			link.l1 = "Du bist willkommen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Keine Perle? Aber wie ist das möglich, Onkel "+pchar.name+"?! Nur noch ein paar Perlen übrig... Ich muss sie sammeln. In diesem Fall werde ich landen. Ich werde nach Perlen suchen...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Und wohin willst du gehen? Was wirst du alleine tun? Nein, ich möchte nicht für dein Schicksal verantwortlich sein. Warte, ich überprüfe meine Taschen... Hier! Nimm deine Perle und bleib bei mir. Zufrieden?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Es ist dein Recht, Ole. Wenn es dir langweilig ist, mit mir zu segeln, dann werde ich dich nicht aufhalten. Wir hatten einen Deal. Du hast diese Raten jedoch gut eingefangen...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Auf Wiedersehen, Onkel "+pchar.name+". Ole braucht weiße Perlen oder er wird nie zu seiner Mutter zurückkehren...";
			link.l1 = "Oh, es tut mir so leid für dich, aber was kann ich tun? Geh, Ole. Viel Glück.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Onkel "+pchar.name+"! Ich brauche noch eine weiße Perle. Die letzte. Bitte, gib sie Ole!";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Ich wusste, dass du danach fragen würdest. Hier, nimm deine Perle. Zufrieden?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Oh, und was für ein Ärger... Ich habe keine Perlen mehr, Ole, das habe ich nicht!";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Danke, danke, guter Onkel "+pchar.name+"! Jetzt hat Ole alle Perlen. Ja, alle! Jetzt kann Ole sie zu Mama bringen und sie wird Ole nicht weg schicken...";
			link.l1 = "Hör zu, wer ist diese Mutter, von der du immer redest? Und erklären Sie mir endlich, warum Sie diese Perlen brauchen... weiße Perlen? Und was bedeutet es - du hast sie alle?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Guter Onkel "+pchar.name+" hat Ole geholfen, Perlen für seine Mama zu sammeln... Ole war klein, als er Mamas Halskette aus weißen Perlen zerriss. Sie fielen alle ins Wasser. Mama war so wütend auf Ole und er kann nicht nach Hause zurückkehren, bis er alle verlorenen Perlen gesammelt hat\nIch erinnere mich, wie viele es von ihnen gab. Fünfmal zehn Perlen. Jetzt hat Ole sie alle. Onkel "+pchar.name+", bitte, bring mich nach Hause! Ich möchte Mama glücklich machen, die Perlen zurückgeben. Bring mich nach Hause!";
			link.l1 = "Jesus, was für eine unglaubliche Geschichte... Du bist als Kind auf die Insel gekommen. Wurdest du von deiner vertrieben, weil du die Perlenkette deiner Mutter zerrissen hast? Gruselig...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Bring mich zu meiner Mutter, guter Onkel "+pchar.name+". Ich möchte sie sehen. Sie wird sich freuen, Perlen zu sehen.";
			link.l1 = "Ich würde gerne, aber weißt du, wo dein Zuhause ist? Wo wohnt deine Mutter?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Sie lebt auf der Insel, im Haus mit dem roten Dach.";
			link.l1 = "Wirklich! Wissen Sie überhaupt, wie viele Inseln es hier gibt und wie viele Häuser mit einem roten Dach darauf? Wie heißt diese Insel? Gib mir Details...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Ich kenne seinen Namen nicht. Ich weiß, dass es eine Insel war, Mama hat Papa gesagt, dass wir auf der Insel waren! Und wir haben im Haus mit dem roten Dach gewohnt. Hübsches Haus, ein großes. Bring mich zu Mama, Onkel "+pchar.name+". Bitte...";
			link.l1 = "Oh, gut. Wir werden auf jeder Insel nach einem solchen Haus suchen und nach deiner Mutter fragen. Wie heißt sie?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Ihr Name? Du bist so seltsam, Onkel "+pchar.name+". Mutter's Name ist Mutter. Ist der Name deiner Mutter anders?";
			link.l1 = "Oh, Gott, bitte, schick mir etwas Geduld... In Ordnung, Ole. Wir werden versuchen, dein Zuhause zu finden. Jetzt geh zum Schiff.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Danke dir, Onkel "+pchar.name+". Du bist sehr, sehr nett und gut! Bald wird Ole Mama sehen!";
			link.l1 = "Oh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mutter... Mutter, Mama! Ich bin zurück!";
			link.l1 = "Sohn...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Mama, ich habe dir weiße Perlen gebracht! Ich habe sie alle gesammelt! Du wirst wieder eine Halskette haben. Bist du immer noch böse auf mich?";
			link.l1 = "Gott...(weint) Ole! Sohn, warum? Warum bist du weggegangen? Mir sind diese Perlen egal!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Mama, hier... nimm sie. Ich habe sie lange gesammelt. Gute Onkel haben mir geholfen, besonders Onkel "+sld.name+". Er hat mich auf sein großes Schiff genommen, half mir, Perlen zu sammeln und hat mich nach Hause gebracht...";
			link.l1 = "Ole... Du bist wirklich erwachsen geworden, aber du bist immer noch ein Kind... Lass mich dich umarmen, Sohn! Es tut mir leid, bitte verzeih mir wegen dieser verdammten Halskette! Ich werde dich nie wieder alleine lassen, niemals! Wir werden zusammen leben und ich werde mich um dich kümmern... Ich werde büßen, das verspreche ich!...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Mama, du hast mir gefehlt... Ich möchte bei dir bleiben. Bist du immer noch wütend auf mich? Warum weinst du?";
			link.l1 = "(weinend) Nein, nein... Es tut mir so leid, bitte verzeih mir, Sohn!...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Onkel "+pchar.name+"! Es ist so gut, dass du gekommen bist! Danke, dass du mich zu meiner Mutter gebracht hast. Es ist so schön, hier bei ihr zu sein... Ist es nicht toll, zu Hause zu sein, nicht wahr, Onkel "+pchar.name+"?";
			link.l1 = "Ja. Ole. Das ist es. Ich bin froh, dass du glücklich bist.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest deine Waffe weglegen. Sie macht mich nervös.","Sie wissen, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nehmen Sie es weg.","Hör zu, spiel keinen mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.","Hör zu, ich bin Bürger dieser Stadt und ich bitte dich, dein Schwert niederzuhalten.");
				link.l1 = LinkRandPhrase("Gut.","Gut.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habe es.","Ich nehme es weg.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
