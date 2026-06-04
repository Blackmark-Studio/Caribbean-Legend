// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Was? Was wollen Sie?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Ich wollte den Anführer des Clans treffen.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, "+GetFullName(pchar)+"! Willst du etwas?";
				link.l5 = "Wollte dich nur begrüßen. Bis dann!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jetzt kennst du mich. Mein Name ist Donald Greenspen und mach mich oder meine Männer nicht wütend. Und versuche nicht, die 'San Gabriel' zu besuchen, bis du ein Passwort hast. Der Laden ist frei zu besuchen, jeder muss handeln. Irgendwelche Fragen?";
			link.l2 = "Nein, ich habe es. Bis dann.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Welches Anliegen hast du bei mir?";
			link.l1 = "Ein sehr unangenehmer, Donald. Letzte Nacht gab es ein Attentat auf Stevens Leben. Kämpfer deines Clans haben daran teilgenommen.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Ich weiß nichts darüber. Warum denkst du, dass es meine Männer waren?";
			link.l1 = "Weil ich dort war. Wir können den Unterschied zwischen deinen Männern, Piraten und Rivados erkennen. Die Gruppe wurde von Mary Casper und Chad Kapper geführt. Brauchst du mehr Beweise?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Ich kann Ihnen nur versichern, dass ich und meine Männer damit nichts zu tun haben.";
			link.l1 = "Sie müssen den Admiral davon überzeugen und es wird nicht einfach sein. Dodson ist sehr wütend auf alle Narwale nach dem Angriff. Er wird euch den Krieg erklären - er wird aufhören, euch mit Proviant zu versorgen und eure Männer erschießen, wann immer sich eine Gelegenheit bietet. Und das sind nicht nur Worte.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Ich hoffe, dass der Admiral versteht, was er vorhat. Zweifelt er daran, dass meine Männer auch schießen können?";
			link.l1 = "Ich denke, das tut er. Er ist bereit, die 'San Augustine' in eine Festung zu verwandeln und zu kämpfen, bis ihr alle verhungert. Außerdem wird Dodson mit den Rivados sprechen und ihnen eine Zusammenarbeit anbieten. Ihr habt keine Chance gegen den Admiral und die Rivados zusammen.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Verdammt! Aber wir sind nicht Teil dieses Versuchs! Warum muss der ganze Clan für die Taten dieses dummen Mädchens Mary und einer Bande Abschaum aus meiner Mannschaft bezahlen?\nAußerdem, lasst uns logisch reden, indem er Marlow getötet hat, hat Dodson selbst Mary und meine Soldaten provoziert. Genau das passiert, wenn man solche Gemeinheiten begeht.";
			link.l1 = "Sie verstehen überhaupt nichts. Sie wurden getäuscht. Warum sind Sie so sicher, dass Dodson Alan getötet hat? Tatsächlich denkt er, dass Sie das getan haben, um seine Position einzunehmen...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Es ist mir egal, was er denkt. Alle Beweise sind gegen ihn. Nur er und seine Männer hatten Zugang zum Gefängnis. Alan war in seinen Händen. Rote Mary hat mir viel erzählt. Bevor Alan ermordet wurde, hat Dodson persönlich das Gefängnis besucht und das macht er nicht oft.";
			link.l1 = "Hast du seinen Tod gesehen?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Unsinn! Natürlich habe ich nicht.";
			link.l1 = "Und Chimiset hat. Ja-ja, der Rivados-Zauberer, der neben Alan gesessen hatte. Er wurde auch dort kürzlich ermordet. Ich war am Tag vor seinem Tod im Gefängnis und habe mit ihm gesprochen. Milrow wurde von Chad Kapper, dem Bootsmann von Shark, getötet.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Ist es wahr?";
			link.l1 = "Denken Sie darüber nach: Chimiset kümmerte sich nicht um Ihre Beziehung zum Admiral. Er hatte keinen Grund zu lügen. Der alte Zauberer hatte Angst vor Chad, er vermutete, dass er der Nächste sein würde. Er hatte Recht, Chad hatte ihn umgebracht, sobald er erfuhr, dass der Admiral ihn freilassen würde.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Aber warum wollte Kapper Alan's Tod?";
			link.l1 = "Verdammt, verstehst du wirklich nicht? Ich habe dir gesagt, dass Kapper mit der Roten Mary zusammengearbeitet hat. Er wollte Sharks Position einnehmen und hat einen schlauen Plan dafür gemacht. Alan Milrow zu töten und Gerüchte über Sharks Beteiligung an seinem Tod zu verbreiten, machte den Narwal-Clan feindselig gegenüber dem Admiral...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "Das dumme Mädchen Mary vertraute ihm und stand auf der Seite des wahren Mörders ihres Freundes. Sie hatten ein paar Narwale dazu überredet, sich ihnen anzuschließen, für Mary muss das einfach gewesen sein. Dann haben sie einen Angriff auf den Admiral in Fazios Kabine organisiert, der gezwungen war, eine Einladung an den Admiral zu schreiben...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Ich habe einen Brief von Fazio, der alles erklärt. Chimiset wurde von Chad als gefährlicher Zeuge getötet. Er hat mit den Narwalen zusammengearbeitet und Rivados wäre wirklich froh, das während ihres Gesprächs mit Shark zu hören. Mit diesem Brief werden wir Black Eddie leicht beweisen, dass Chad einer von deiner Art geworden ist.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Du hast alle Asse, was machst du dann hier? Du willst etwas von mir, oder?";
			link.l1 = "Ich tue es. Weil ich glaube, dass es alles Chads Plan war und du nicht beteiligt bist. Chad hat Mary betrogen, sie rief ihre Freunde aus deinem Clan um ihr zu helfen, das ist eine ganze Geschichte. Zumindest habe ich keine Beweise gegen dich oder irgendeinen anderen Narwal gefunden...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "Aber das bedeutet nicht, dass es keine anderen Verschwörer mehr gibt. Ich möchte, dass du nach ihnen suchst. Dann können wir vielleicht die Dinge ohne ein Gemetzel klären.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "Ich habe dir bereits gesagt, dass niemand sonst von meinen Männern daran beteiligt war. Nach Marlows Tod hat Mary sich im Grunde genommen vom Clan zurückgezogen und sich in ihrer Kabine eingeschlossen. Eigentlich habe ich keine Ahnung, wie sie es geschafft hat, andere zur Teilnahme zu bewegen, aber es scheint, dass sie Erfolg hatte. Ich schwöre, dass weder ich noch jemand anders aus meinem Clan gegen den Admiral vorgehen.\nWir haben in letzter Zeit zu viele Männer verloren, also wollen wir uns jetzt nicht in ein chaotisches Geschäft einmischen. Ich habe keine Angst vor einem Angriff des Admirals, auch nicht zusammen mit den Rivados. Die Narwale sind wahre Krieger und das werden wir in unserer letzten Schlacht beweisen. Aber das wäre sinnlos\nWir haben uns bereits entschieden, Frieden mit dem Admiral zu halten. Mit den Rivados verhandeln wir nicht. Ich bin bereit, mich persönlich beim Admiral zu entschuldigen, um Vergebung für meine Verdächtigungen aufgrund von Milrows Tod und für den Angriff auf sein Leben zu bitten. Ich werde auf der Bibel schwören, um meine Aufrichtigkeit zu beweisen. Seid ihr und Dodson damit einverstanden?";
			link.l1 = "Ich bin es. Sind Sie sicher, dass von Ihren Männern keine Tricks zu erwarten sind?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Absolut. Ich werde meinen Clan über den wahren Mörder von Alan Milrow informieren. Die Beziehung meiner Männer zum Admiral wird sich sofort ändern, das versichere ich Ihnen. Sagen Sie mir, wird danach ein Gemetzel nötig sein?";
			link.l1 = "Nein, das wird es nicht. Ich bin hier, um es zu verhindern. Ich vertraue dir, Donald, und ich werde versuchen, Shark zu überzeugen. Ich habe noch ein paar Argumente übrig... Auf Wiedersehen, Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Haben Sie schon mit dem Admiral gesprochen? Irgendwelche Ergebnisse?";
			link.l1 = "Ich bin beschäftigt. Wir sehen uns später...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Haben Sie schon mit dem Admiral gesprochen? Irgendwelche Ergebnisse?";
			link.l1 = "Ja, das habe ich. Deine Entschuldigungen sind angenommen, die Anschuldigungen deines Clans sind vom Tisch. Es gibt sogar mehr, Shark bietet dir an, ihn zu besuchen, um die Bedingungen für eine zukünftige friedliche Vereinbarung zwischen Narwalen und Piraten zu besprechen.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Ehrlich gesagt, ich habe nicht erwartet... Das ist eine großartige Neuigkeit. Vielleicht können wir sogar die Preise für die Versorgung unseres Clans und eine neue Politik in Bezug auf die Rivados überdenken.";
			link.l1 = "Das betrifft nur Sie und den Admiral.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Ja, natürlich. Sie haben dem Narwal-Clan einen großen Dienst erwiesen, indem Sie das sinnlose Blutvergießen und vielleicht sogar die völlige Vernichtung meiner Männer verhindert haben. Nehmen Sie dieses Turmgewehr als Zeichen meiner Dankbarkeit, Sie werden keine andere Waffe dieser Art finden\nAußerdem dürfen Sie unsere eingeschränkten Bereiche besuchen, genau wie jedes Clanmitglied.";
			link.l1 = "Danke! Lebewohl jetzt, ich habe viele Dinge zu tun.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower mousqueton");
			PlaySound("interface\important_item.wav");
			dialog.text = "Viel Glück. Komme zu mir, wenn du Fragen hast.";
			link.l1 = "Verstanden. Bis dann!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "He! "+GetFullName(pchar)+"! Du bist... nein, das ist unmöglich! Bist du am Leben?!";
				link.l1 = "Gerüchte über meinen Tod waren ein bisschen falsch, Donald. Ha-ha, ich freue mich, dich zu sehen!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, mein Freund "+GetFullName(pchar)+"! Brauchst du etwas?";
			link.l1 = "Nein, das tue ich nicht. Ich wollte dich nur begrüßen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Welches Anliegen haben Sie bei mir?";
			link.l1 = "Ein sehr unangenehmer, Donald. Es gab ein Attentat auf Stevens Leben. Kämpfer deines Clans haben teilgenommen.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Ich weiß nicht, was Sie meinen. Warum denken Sie, dass meine Männer daran beteiligt waren?";
			link.l1 = "Denn ich persönlich habe einige von ihnen zusammen mit Chad Kapper, dem Bootsmann des Admirals, der für dieses ganze Durcheinander verantwortlich ist, getötet. Er konnte es nicht alleine schaffen, also haben deine Männer ihm sehr geholfen. Der Admiral weiß das und er ist sehr, sehr wütend.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Meine Männer? Wer genau, kannst du sie nennen?";
			link.l1 = "Sie haben sich nicht vorgestellt. Sie haben einfach nur geschossen und gefochten. Deine Leute sind rücksichtslos. Sie können sogar einen von ihren eigenen angreifen. Zur Hölle mit mir oder mit dem Admiral, aber ein Mädchen zu töten zu versuchen?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Über wen redest du?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Wen meine ich? Ich spreche von dem Angriff auf die Rote Mary. Zwei Narwale versuchten, sie zu töten. Durch reinen Zufall kam ich in einem kritischen Moment in ihre Kabine. Sie hätten sie getötet, wenn ich später gekommen wäre. Ich habe nicht nach ihren Namen gefragt, es tut mir leid, ich hatte keine Zeit, mit ihnen zu reden, aber Mary sagte, dass sie Narwale waren.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Wovon rede ich? Ich rede vom Angriff auf die Rote Mary und den beiden Narwalen, die sie getötet haben.";
				link.l1.go ="negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Was? Warum hat sie es mir nicht gesagt?! Ich hätte sofort gehandelt!";
			link.l1 = "Sie hatte sogar Angst, kürzlich ihre Kabine zu verlassen. Sie hatte vor nicht allzu langer Zeit einen Streit mit Ihnen, also warum sollte sie zu Ihnen laufen und um Ihre Hilfe bitten?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Ich habe nicht mit ihr gestritten! Sie verlangte Unmögliches von mir, wir hatten ein heftiges Gespräch und ich schickte sie weg. Aber das bedeutet nicht, dass ich...";
			link.l1 = "Gut, was auch immer. Schließlich sind jetzt alle Probleme gelöst. Aber es gibt Bastarde unter deinen Männern, das ist eine Tatsache.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Was? Wurde sie von Narwalen getötet? Warum?";
			link.l1 = "Auf Befehl von Chad Kapper, Donald. Sie wusste zu viel und wollte Chad nicht helfen. Und nun ist das arme Mädchen tot!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Ich schwöre, ich wusste nichts davon!";
			link.l1 = "Sicher, du hast nicht... Aber lass uns über den Admiral sprechen. Chad Kapper hatte den Versuch organisiert und deine Männer haben ihm geholfen. Sie versuchten Dodson zu vergiften und ich habe das kaum verhindert.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Ich habe nichts dergleichen bestellt. Dodson weiß, dass ich die Politik des verstorbenen Alan nicht unterstütze und ich denke, dass ein magerer Kompromiss besser ist als eine fette Klage.";
			link.l1 = "Sie müssen den Admiral davon überzeugen und das wird nicht einfach sein. Dodson ist sehr wütend auf alle Narwale nach dem Versuch. Er wird Ihnen den Krieg erklären.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Ich hoffe, dass dieser Admiral seine Handlungen versteht. Zweifelt er daran, dass meine Männer zurückschießen können?";
			link.l1 = "Er tut es. Er denkt, dein Clan ist eine Banditenbande und muss vernichtet werden, bevor ihr anfangt, alle zu töten. Außerdem haben wir starke Verbindungen zu den Rivados. Ich kann einfach mit Black Eddie sprechen und ihm ein Bündnis anbieten. Ihr werdet nicht gegen uns alle bestehen.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Call Red Mary if you don't believe me and ask her! She will confirm.";
			else sTemp = "I have a letter from Chad to Mary which proves everything.";
			dialog.text = "Verdammt! Warum muss der gesamte Clan für die Handlungen einiger Idioten bezahlen? Denk nicht, dass ich Angst habe. Wir sind Krieger und das werden wir auch in unserer letzten Schlacht beweisen. Aber ich will Gerechtigkeit. Eigentlich ist der Admiral verantwortlich für den Tod von Alan Milrow im Gefängnis.";
			link.l1 = "Wie kannst du der Anführer sein, Donald... Du weißt weder etwas über Mary noch über Alan. Chad Kapper hat ihn getötet. "+sTemp+"Er hat das getan, um die Narwale dem Admiral gegenüber feindselig zu machen und einige von ihnen auf seine Seite zu ziehen.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Ich verstehe. Gut. Lassen wir auf eine andere Weise sprechen. Du bist hier für einen bestimmten Zweck, richtig? Was willst du?";
			link.l1 = "Ich will kein blutiges Chaos auf der Insel. Ich will nicht, dass Menschen sterben. Die Idee, alle Narwale zu eliminieren, mag ich nicht, obwohl ich Ihnen versichere, dass Rivados und wir das können. Ich denke auch, dass der ganze Clan nicht für die Handlungen einiger Bastarde verantwortlich gemacht werden sollte...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "Aber meine Stimme wird nicht ausreichen - Sie sollten offiziell dem Admiral versichern, dass der Versuch nicht von Ihnen genehmigt wurde und Ihr Clan nicht plant, Dodson zu töten.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Was kann ich tun? Ich bin bereit, mich für den Versuch und meine Verdächtigungen über Marlows Tod zu entschuldigen. Ich kann ihm versichern, dass die Narwale nichts gegen ihn planen und ich werde auf der heiligen Bibel schwören. Wirst du und Dodson das ausreichend finden?";
			link.l1 = "Ich werde es tun. Ich bin sicher, dass es auch für Dodson funktionieren wird, wenn Sie ihn persönlich besuchen. Aber zuerst werde ich ihm von Ihren Absichten erzählen und dann werde ich Sie erneut mit Ergebnissen besuchen.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Gut. Ich werde warten.";
			link.l1 = "Ich komme bald zurück...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Haben Sie schon mit dem Admiral gesprochen? Irgendwelche Ergebnisse?";
			link.l1 = "Ja, das habe ich. Wenn Sie ihm einen offiziellen Besuch abstatten, dann ist das Problem gelöst.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Ehrlich gesagt, ich habe nicht erwartet... Das ist eine großartige Nachricht.";
			link.l1 = "Ja, wissen Sie, ich bin auch froh.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Sie haben dem Narwal-Clan einen großen Dienst erwiesen, indem Sie ein sinnloses Massaker und vielleicht sogar die völlige Ausrottung meines Volkes verhindert haben. Ich überreiche Ihnen dieses Turmmusket - Sie werden keine andere Waffe wie diese finden. Sie dürfen auch unsere Schiffe ohne Einschränkungen besuchen.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Danke. Ein sehr wertvolles Geschenk. Ja, Donald, noch eine Sache: Versöhne dich mit der Roten Mary. Sie hat ein heißes Temperament, aber sie ist auch aufrichtig und ehrlich. Der Streit mit dir hat sie vom Klan getrennt und es hat sie fast das Leben gekostet.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Danke. Ein sehr wertvolles Geschenk. Und ich bin wirklich froh, dass es so gut ausgegangen ist.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Sag ihr, dass ich sie bitte, mir zu vergeben, dass ich sie verletzt habe und für die beiden Abschaum, die es gewagt haben, sie anzugreifen. Ihr beide seid... Freunde, habe ich recht?";
			link.l1 = "Du hast recht, Donald. Ich werde es ihr sagen. Und ich bin wirklich froh, dass alles so gut ausgegangen ist.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("You have received a tower musket");
			PlaySound("interface\important_item.wav");
			dialog.text = "Viel Glück. Sieh mich an, wenn du Fragen hast.";
			link.l1 = "Gut. Auf Wiedersehen!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("They say that you are a friend of Donald, Greenspen, the leader of Narwhals. Well, Rivados hate you now...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are Narwhal now. Or do you serve under admiral's command? I don't get it...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I've heard that you have made peace between admiral and Narwhals. Hm, Rivados must be insane about that...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("So Chad Kapper was a murderer of Alan Milrow! That is surprising!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Take care of Red Mary cause you are lucky to be with her - she is so reckless! She always gets in trouble...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du da, ah? Dieb!","Schau dir das an! Kaum war ich in Gedanken versunken, hast du dich entschieden, meine Truhe zu überprüfen!","Entschieden, meine Kisten zu überprüfen? Das wirst du nicht ungestraft davonkommen!");
			link.l1 = "Scheiße!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Kisten zu durchsuchen? Du wirst damit nicht durchkommen!";
			link.l1 = "Dummes Mädchen!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Sie macht mich nervös.","Weißt du, hier wird es nicht toleriert, mit einer Klinge herumzulaufen. Nimm es weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumläuft. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert niederzuhalten.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, deine Klinge zu senken.");
				link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, beim Laufen mit einer Waffe. Ich kann nervös werden...","Ich mag es nicht, wenn Männer mit gezogener Waffe vor mir herlaufen. Es ängstigt mich...");
				link.l1 = RandPhraseSimple("Habe es verstanden.","Ich nehme es weg.");
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
