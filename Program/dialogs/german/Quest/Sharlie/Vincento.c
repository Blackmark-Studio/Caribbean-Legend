// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Endlich sehe ich den berühmten französischen Kapitän "+GetFullName(pchar)+" in persona. Ich habe viel von deinen Heldentaten gehört. Du bist ein tapferer Soldat und, wie ich hoffe, ein loyaler und treuer Sohn unserer Mutter, der Heiligen Römisch Katholischen Kirche. Setz dich, mein Sohn. Es besteht keine Notwendigkeit, wegen mir zu stehen. Dominus vobiscum! ";
				link.l1 = "Et cum spiritu tuo, Eure Exzellenz. Mein Weg hierher war lang und beschwerlich... Per aspera ad astra und so weiter...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Ja, ich kann in deinen Augen sehen, dass du Neuigkeiten für mich hast. Du hast meine ungeteilte Aufmerksamkeit.";
				link.l1 = "Eure Exzellenz, ich habe Ihren vermissten Sekretär gefunden...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Hast du mir Neuigkeiten aus San Jose gebracht, mein Sohn?";
				link.l1 = "Ja, Eure Exzellenz. Ich habe herausgefunden, was mit unserem gemeinsamen Bekannten Miguel Dichoso und seiner verlorenen Fregatte passiert ist. Sobald sein Schiff den Atlantik auf dem Weg nach Spanien erreichte, wurde es sofort von einer entgegengesetzten Sturmböe erfasst und zurück in die Karibik gewirbelt.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Friede sei mit dir, mein Sohn... Was kann ich für dich tun?";
				link.l1 = TimeGreeting()+", Eure Exzellenz. Haben Sie Neuigkeiten bezüglich unserer Vereinbarung?";
				link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Gibt es etwas, was du wolltest, mein Sohn?";
			link.l1 = "Nein, nichts, Vater.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "Ich stimme zu, Eure Exzellenz. Ich habe die Aufgaben, die Sie mir gestellt haben, abgeschlossen. Sie haben bereits den feigen Piraten, der die kostbaren Gefäße von der Kirche gestohlen hat. Jetzt gebe ich alles zurück, was genommen wurde: das Ostensorium, das Kreuz und das Weihrauchfass. Nehmen Sie sie für die Pfarrei von Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Ich danke Ihnen von ganzem Herzen für Ihren treuen Dienst an der Heiligen Mutter Kirche und der Pfarrei Santiago, mein Sohn. Ihre Werke werden nicht unbelohnt bleiben. Die Pfarrangehörigen haben eine Gabe für den mutigen Krieger gesammelt, der ihre gestohlenen Gegenstände zurückgebracht hat, und ich gebe sie gerne in ihrem Namen an Sie weiter. 'Der Arbeiter ist seines Lohnes würdig.'";
			link.l1 = "Danke, Eure Exzellenz. Was für eine angenehme Überraschung!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Treuer Dienst an der Mutterkirche wird immer treu belohnt, "+pchar.name+". Ich hoffe meinerseits, dass Sie ein engagierter Krieger für die Verteidigung und den Schutz des Christentums bleiben, denn über uns schwebt eine tödliche Bedrohung wie das mythische Schwert des Damokles.";
			link.l1 = "Was könnte das sein, Eure Exzellenz?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Vielleicht bist du dazu bestimmt, unser Champion in der bevorstehenden Schlacht gegen die dunklen Mächte und Fürstentümer dieser Welt zu sein, mein Sohn, denn es gibt viele Zeichen und Vorzeichen, dass etwas Böses naht.";
			link.l1 = "Zeichen und Omen?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Viele, mein Sohn... Eines davon ist deine Begierde, das verlorene indische Gold des heidnischen Tayasal zu suchen, denn das, was in ihrem Hort konserviert ist, stellt genau die Gefahr für die ganze christliche Welt dar.";
			link.l1 = "Könnten Sie mich ein wenig über dieses Gold aufklären, ehrwürdiger Vater? Die Geschichte seines Verschwindens habe ich bereits gehört, aber von welcher Art von Bedrohung sprechen Sie?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Hör genau zu, mein Sohn, und wisse, dass alles, was du nun hörst, nur für deine Ohren bestimmt ist. Lange bevor Miguel Dichoso jenen heidnischen Schatz aus der alten indischen Stadt nahm, befragte ich einen gefangenen Mann der Itza-Indianer zu unserer Mission in der Karibik. Die Itza sind Nachkommen der Mayas, eines mächtigen Reiches, das Jahrhunderte bevor Cristobal Colon und seine Männer erstmals Fuß in die Neue Welt setzten, verloren ging. Das Maya-Reich beherrschte die umliegenden Stämme mit eiserner Faust, mit unsagbarer Macht, die ihnen durch höllische Geschäfte mit Dämonen verliehen wurde. Dunkle Magie, erkauft mit dem Blut von Generationen menschlicher Opfer. \nDieser Itza-Mann wusste von Tayasal, einer verlorenen Maya-Stadt und dem unglaublichen Übel, das noch immer darin versiegelt ist. Er erzählte uns alles, was er wusste. Sollten diese Siegel geöffnet werden, wären die Folgen apokalyptisch. Von diesem Moment an habe ich alles in meiner Macht Stehende getan, um dieses furchtbare Übel daran zu hindern, geweckt zu werden. Ich schrieb verzweifelt an das Escorial und Rom und bat um Hilfe.\nSie hörten zu und entsandten Don Ramon de Mendoza y Riba, der seine Basis auf Providence errichtete und begann, nach Tayasal zu suchen. Das ist, als ich entdeckte, dass der gute Don Mendosa... andere Motivationen hatte, die verlorene Stadt zu finden. Anstatt das Ende der Welt zu verhindern, suchte er Mammon statt Christus zu dienen.\nDas ist der Grund, warum Gott ihn verließ und den Engel des Todes in sein Lager schickte. Alle seine Handlungen waren vergeblich und führten nur zu sinnlosen Toden von spanischen Soldaten und gläubigen indischen Konvertiten. Ich schrieb an das Escorial und bat darum, Ramon de Mendoza wegen Unfähigkeit zu entlassen, und sie stimmten zu, ihm seine Pflichten zu entheben, aber...";
			link.l1 = "Miguel Dichoso ist gekommen.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Genau. Dieser vom Teufel gesandte Abenteurer fand Tayasal zusammen mit den Schätzen der alten Mayas. Allerdings war die Freude von Don Mendosa nur von kurzer Dauer. All diese Schätze verschwanden zusammen mit Dichoso auf dem Weg zurück nach Spanien. Es ist wahrscheinlich, dass Miguel zusammen mit all den Goldbarren und Ornamenten eine alte Quelle des Teufels mit sich nahm, die erschreckende Maske eines alten Maya-Dämonengottes namens Kukulcan.";
			link.l1 = sTemp+"Aber welches Übel sprechen Sie, Eure Exzellenz? Wie wissen Sie davon?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "Es ist ein Übel, das allen getauften Christen der Karibik, der Neuen Welt und möglicherweise auch der Alten Welt den Tod bringt. Das Ende wird kommen wie ein Dieb in der Nacht, und niemand wird überhaupt realisieren, was passiert ist. Und es gibt schon überall Anzeichen dafür!";
			link.l1 = "Welche Omen? Ich verstehe nicht...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Mein Sohn, bist du wirklich so blind, dass du sie nicht einmal bemerkst? Sie geschehen seit fünfundzwanzig Jahren, fast ohne Unterbrechung!";
			link.l1 = "Ich möchte bescheiden erwähnen, Eure Exzellenz, dass der Verlauf meines Lebens genau auf diese Zeitspanne bemessen ist, ganz zu schweigen davon, dass ich den Großteil meines Lebens in Europa verbracht habe. Meine Unwissenheit sollte ein wenig entschuldigt werden.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Ich verstehe, "+pchar.name+". Nun, haben Sie nicht bemerkt, dass seltsame Dinge passiert sind, sobald Sie aus Europa hier in der Karibik angekommen sind? Finden Sie es nicht seltsam, dass Hexerei, schwarze Magie und andere Rituale hier viel mehr Kraft haben als zu Hause? Heidnische Amulette, verzaubert von indischen Schamanen, besitzen eine echte Macht, die jeder Mann nur durch Halten erleben kann.\nSelbst unsere christlichen Alchemisten - möge Gott ihnen ihren Irrtum zeigen! - haben die Kunst des Herstellens verzauberter Gegenstände gemeistert. Sie merken nicht, dass sie dem Teufel selbst dienen, indem sie das tun. Fühlen Sie nicht die unnatürliche Präsenz von etwas Höllischem, das gerade außerhalb Ihres peripheren Sehvermögens lauert?";
			link.l1 = "Du hast recht, Vater. Zuerst hat mich das überrascht, aber jetzt denke ich, dass ich mich daran gewöhnt habe... Es ist schließlich die Neue Welt!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Aber es war nicht immer so. Die Dunkelheit, von der ich spreche, kam vor etwa fünfundzwanzig Jahren hierher und gewinnt mit jedem Tag mehr und mehr Macht. Das bedeutet nur eins: 'Es' ist bereits gekommen, 'Es' ist unter uns, und 'Es' ist am Werk...";
			link.l1 = "Wer meinst du? Wer ist dieses geheimnisvolle 'es'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "Der eingeschworene Feind der Christen, der die Zerstörung der Kirche und des gesamten Christentums begehrt.";
			link.l1 = "...Sprichst du vom Antichristen?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Ob es 'der' Antichrist oder nur 'ein' Antichrist ist, wage ich nicht zu sagen. Es spielt keine Rolle, welchen Namen dieses Biest trägt, wenn es sich in grotesker Parodie unserer Erlösers Inkarnation in sterbliches Fleisch kleidet. Wichtig ist, was es tun wird. Ich bin hier, um es zu stoppen, und du wirst mir helfen. Aber wir sind ein wenig abgeschweift. Du bist ein Mann der Tat. Du würdest wahrscheinlich lieber zur Sache kommen und die Theologie überspringen, richtig?";
			link.l1 = "Ganz im Gegenteil, ich habe von Euch, Eure Exzellenz, viele neue und wichtige Dinge erfahren. Ich bin bereit, weiter zuzuhören.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Du bist zuvorkommend und gut erzogen, mein Sohn. Das ist gut. Nun zurück zu dem Grund, aus dem du dich mit mir beraten hast. Unser gemeinsames Ziel ist es, die Schätze von Tayasal zu finden, die Dichoso genommen hat. Wahrscheinlich werden wir unter diesen Schätzen eine Waffe finden, die wir in der kommenden Schlacht gegen den Teufel einsetzen können.";
			link.l1 = "Aber kann es sein, dass Dichoso bereits die Karibik verlassen hat und nun auf einem Haufen Gold in Spanien sitzt?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Nein. Ich habe Beweise, dass diese Schätze noch hier in der Karibik sind. Du musst noch nicht von meinen Quellen wissen, du musst mir vertrauen. Außerdem glaube ich, dass Dichoso den Baron belogen hat.\nSeine Geschichte über die Ruinen von Tayasal stimmt nicht mit dem überein, was mir mein Itza-Indianer unter Befragung erzählt hat. Ganz zu schweigen davon, dass es ein wenig zu praktisch war, dass Dichoso der einzige Überlebende des Moskito-Hinterhalts war.";
			link.l1 = "Ich nehme an, dass Don Mendosa das auch glaubt, da er Saint-Pierre überfallen hat, um Dichoso zu finden?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Die Handlungen des Barons sollten dich nicht beunruhigen, mein Sohn. Er wird nur von der Gier nach Gold und persönlichem Gewinn angetrieben. Seine Gier wird ihm einen Mühlstein um den Hals legen, während um ihn herum gute christliche Männer und Frauen mit den Mächten der Hölle beschäftigt sind.";
			link.l1 = "Haben Sie irgendwelche Hinweise, wo wir nach Dichoso und dem Schatz suchen sollten?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Ich denke jede Minute daran, mein Sohn, aber ich habe nichts Konkretes zu sagen. Aber es gibt hier einen Mann, der uns helfen wird, einen Naturphilosophen aus Genua. Ich habe ihn hierher gebracht, um Dinge aus der Neuen Welt zu kategorisieren, die der Kirchenmission nützlich sein könnten. Er war Zeuge der Vernehmung des Itza-Indianers und nach meiner besten Einschätzung schockierten und pervers angezogen die Dinge, die er gehört hatte. \nDer Teufel nutzte seine Neugier wie einen geköderten Wolfsfisch und besaß ihn, Körper und Seele. Der Herr hatte ihm große Fähigkeiten mit Medizin und Alchemie gegeben, aber unser Genuese erlag der Versuchung der schwarzen Magie und Zauberei. Er sprach mehrmals ohne meine Erlaubnis mit meinem gefangenen Itza, dann verschwand er. Wir müssen ihn finden und seine Seele retten.";
			link.l1 = "Ich nehme an, dass ich ihn finden soll?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Ja, mein Sohn. Er ist der erste Schritt, um den Schatz und die Waffe zu finden, die wir gegen die bösen Kräfte einsetzen können, die uns bedrohen.";
			link.l1 = "Wer ist dieser Genuese?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Sein Name ist Gino Gvineili. Dreißig Jahre alt, mehr oder weniger. Ein begabter Arzt und Alchemist. Wie ich schon sagte, studiert er jetzt schwarze Magie. Nach meinen besten Informationen versteckt er sich irgendwo in den englischen Kolonien in der Karibik.\nFinden Sie Gino Gvineili, mein Sohn. Wenn Sie es geschafft haben, den Piraten zu finden, der unsere Kirchenschiffe gestohlen hat, dann werden Sie es auch schaffen, meinen entlaufenen Sekretär zu finden und ihn hierher zu bringen. Ich werde für die Fürsprache des heiligen Antonius in Ihrem Namen beten.";
			link.l1 = "Ich verstehe, Eure Exzellenz. Ich werde keine weitere Minute verschwenden. Bis später!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ich war mir völlig sicher, dass du das sagen würdest, "+pchar.name+". Nun wird mein Glaube noch mehr gestärkt durch meine Gewissheit, dass du mir von der Hand der Göttlichen Vorsehung selbst gesandt wurdest. Wo ist mein elender, verschwenderischer Sohn?";
			link.l1 = "Ich fürchte, Sie werden nicht mögen, was Sie gleich hören werden, aber ich habe keine Wahl. Ihr Sekretär ist tot.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Möge Gott seine Seele retten und ihm seine Sünden vergeben... Wie ist es passiert, mein Sohn?";
			link.l1 = "Ich habe Gino auf Antigua gefunden. Er versteckte sich dort in einem der alten Gebäude, das unter dem Labor errichtet wurde. Er stimmte nicht zu, ruhig mit mir zu kommen. Nachdem er deinen Namen gehört und gesehen hatte, dass ich bereit war, Gewalt anzuwenden, nahm er ein Fläschchen mit klarer Flüssigkeit aus den Falten seines langen Gewandes und trank es in einem Augenblick...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "Und dann passierte etwas Schreckliches: er wurde rot, dann dunkelblau. Er fiel auf den Boden, zuckte krampfhaft und starb innerhalb einer Minute in furchtbaren Schmerzen. Ein starker Mandelduft erfüllte den Raum.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Du armer Narr... Er verbrachte sogar die letzte Minute seines Lebens in Sünde, indem er Selbstmord beging. Was für ein tragischer Verlust. Ich werde für seine Seele beten...";
			link.l1 = "Nach seinem Tod durchsuchte ich seine Wohnung und fand dort dieses Folio. Könnte es vielleicht von Interesse für dich sein oder uns bei unseren Suchen helfen? Hier sind einige seltsame und esoterische Notizen...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "Das ist der arme Ginos Almanach. Er hat dort Notizen über all seine Erkundungen geschrieben. Gib ihn mir, mein Sohn, ich werde studieren, was darin geschrieben steht. Vielleicht finden wir einen Hinweis.\nObwohl du mir Gino Gvineili nicht zurückgebracht hast, bin ich zufrieden mit deinen Bemühungen, mein Sohn. Jetzt habe ich einige Neuigkeiten für dich.";
			link.l1 = "Sie haben meine Aufmerksamkeit, Vater.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Ich habe Informationen erworben, dass die Insel Trinidad der letzte Ort war, an dem Dichosos Fregatte gesehen wurde. Ich kenne auch eine ungefähre Zeit - Anfang April 1654.\nGeh nach Trinidad und versuche, alles über das Schicksal der Fregatte herauszufinden: wohin sie steuerte, welche Pläne der Kapitän hatte, alles, was du finden kannst. Ich verstehe, dass es eine lange Zeit gewesen ist und die Erinnerung der Menschen Grenzen hat, aber ein ertrinkender Mann wird sich an jeden Strohhalm klammern.";
			link.l1 = "Ich werde alles in meiner Macht Stehende tun.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Lass mich deinen Passierschein sehen. Ich werde die Erlaubnis hinzufügen, dass du die Kolonie San Jose besuchen darfst.";
			link.l1 = "Hier.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Dort... das wird alles sein. Vergiss nicht, die spanische Flagge auf deinem Schiff zu hissen. Tritt vor und empfange Gottes Segen, mein Sohn!";
			link.l1 = "Einen Moment, Eure Gnaden. Darf ich Ihnen eine Frage stellen?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Ja, natürlich. Was möchten Sie wissen?";
			link.l1 = "Während unseres letzten Treffens sprachen Sie von einem Itza-Indianer, der Sie über Tayasal informiert hatte. Ich habe viel darüber nachgedacht... Sagen Sie, hatte dieser Mann etwas bei sich? Gegenstände irgendeiner Art, Schriften oder so etwas? Das könnte sich als nützlich erweisen.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Keine besonderen Gegenstände, mein Sohn. Ein Lendenschurz, primitiver Schmuck, eine Bambuspfeife mit einigen Kräutern und ein Stück grobes Leder, das als Knebel verwendet wurde.\nAll das wurde an Don Ramon de Mendoza y Riba geschickt. Aber ich versichere Ihnen, es gab nichts von Interesse.";
			link.l1 = "Ich verstehe. Danke Vater. Bis zum nächsten Mal!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Möge der Allmächtige dich segnen und behüten... Was ist mit Miguel Dichoso passiert? Hast du es herausgefunden?";
			link.l1 = "Ach, das tat ich nicht. Das Letzte, was die Zeugen mir sagen konnten, war, dass die Santa Quiteria von Sturmböen in Richtung Martinique getrieben wurde. Es ist nicht sicher bekannt, ob das Schiff gerettet wurde oder ob es zugrunde ging. Aber ich habe den Verdacht, dass Miguel Dichoso lebend herauskam.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Was hat dich dazu bewogen, mein Sohn?";
			link.l1 = "Der Schlüssel ist, dass die Fregatte irgendwo in Richtung Martinique versteckt war. Und sehr kürzlich hat ein galanter Caballero namens Diego de Montoya, einer von Don Ramon de Mendosas Männern selbst, Saint-Pierre mit dem Ziel angegriffen, Miguel Dichoso zu finden, der angeblich dort versteckt war.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Also, der Baron denkt, Dichoso hat sich bei den Franzosen versteckt...";
			link.l1 = "Ich kenne Saint-Pierre und Gouverneur Jacques Dyel du Parquet gut, Eure Exzellenz. Niemand kannte dort einen Spanier namens Miguel Dichoso. Können Sie mir sagen, wie ich Diego de Montoya finden kann? Ich würde gerne mit ihm über Dichoso sprechen.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Bist du sicher, dass er bereit wäre, mit dir zu sprechen, mein Sohn? Ich glaube nicht, dass er das tun würde, es sei denn, du unterhältst dich mit Schwert und Pistole.";
			link.l1 = "Kann es sein, dass Ihr Name ihn zugänglicher macht?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+". Ich bezweifle, dass Don Mendozas geschworener Mann bereit wäre, eine Vereinbarung mit Ihnen zu treffen. Ihm den Befehl zu geben, zu einer Anhörung bei mir in San Diego zu erscheinen, könnte eine Option sein, aber ich bin mir nicht so sicher, ob Diego auch vollkommen aufrichtig zu mir wäre.";
			link.l1 = "Welche Aktion sollen wir jetzt unternehmen, Vater?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Verlasse mich für eine kurze Weile, mein Sohn. Ich muss das, was du mir erzählt hast, verarbeiten und auch alle Fakten zusammenstellen, die ich bereits aus meinen verschiedenen Quellen kenne. Danach werde ich dir sagen, was unser nächster Schritt ist. Schau später vorbei.";
			link.l1 = "Ja, Eure Gnaden. Wird gemacht. Ich werde regelmäßig nachsehen...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Gott segne dich, mein Sohn... Was kann ich für dich tun?";
			link.l1 = "Haben Sie Neuigkeiten, Eure Exzellenz?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Nicht im Moment, mein Sohn. Verzweifle jedoch nicht. Meine Leute und ich arbeiten daran. Komm später vorbei.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Ja, mein Sohn. Ich habe einige Informationen über Miguel Dichoso. Es war nicht umsonst, dass ich glaubte, Dichoso sei noch am Leben und in der Karibik. Es sieht so aus, als ob Don Diego de Montoya recht hatte. Wir haben Beweise von einem Mann erhalten, der Miguel Dichoso an seinem Gesicht erkannte, dass der vermisste Herr im April 1654 nach dem Verschwinden der Santa Quiteria in der Piratensiedlung von Le Francois auf Martinique gesehen wurde...";
			link.l1 = "Also, ist die Fregatte vor der Küste von Martinique gestrandet?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Verlangsamen Sie, mein Sohn. Wir haben derzeit keine Informationen über ein Schiffswrack auf Martinique zu dieser Zeit. Und eine Fregatte ist kein Lugger. Ihre Zerstörung hätte sicherlich einige Aufmerksamkeit erregt und eine massive Bergungsmöglichkeit für lokale Aasfresser geschaffen.";
			link.l1 = "Sollte es sich lohnen, die Küste und Strände abzusuchen, um zu finden, was von dem Schiff übrig ist?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Mein Sohn, Don Diego de Montoya hat das bereits ohne Erfolg versucht. Bleib dran. Meine Quellen in Providence berichten, dass der Baron sicher ist, dass die Santa Quiteria immer noch unter einem anderen Namen durch die Karibik segelt.\nDeshalb jagt er Miguel Dichoso so verzweifelt. Seinen Worten zufolge wurde die Santa Quiteria nicht weit von Isla Tesoro gesichtet und sie wurde kürzlich unter der englischen Flagge von einem Militärgeschwader begleitet.";
			link.l1 = "Was? Das ist unglaublich. Sie sagten, dass es unmöglich wäre, einem Sturm von solchem Ausmaß standzuhalten... Und nun hat die Santa Quiteria nicht nur überlebt, sondern segelt jetzt unter der englischen Flagge? Die beiden Tatsachen passen nicht zusammen. Was veranlasste den Baron zu der Entscheidung, dass es die Santa Quiteria war? Ist sie wirklich so ein einzigartiges Schiff?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh ja. Diese Fregatte wurde nach den neuesten Techniken in Europa gebaut. Sie ist für ihre Klasse sehr gut bewaffnet, und ihre Geschwindigkeit ermöglicht es ihr, alles zu überholen, was sie möglicherweise übertrifft. Das hat meine Quelle mir gesagt.";
			link.l1 = "Und wie wird sie jetzt genannt, wenn nicht Santa Quiteria?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Das weiß ich leider nicht... Gehe zu Isla Tesoro, "+pchar.name+", und versuche, etwas über Dichosos Fregatte herauszufinden. Vielleicht können wir auf diese Weise auch ihren ehemaligen Kapitän finden, zwei Vögel mit einem Stein. Oder zwei Ratten mit einer Falle.";
			link.l1 = "Betrachten Sie es als erledigt, Eure Exzellenz!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Ich bin froh, dass du dich entschieden hast, mich zu sehen, mein Sohn.";
			link.l1 = "Hallo, Eure Exzellenz. Nach dem Treffen mit Don Alonso de Maldonado hätte ich nicht gedacht, dass ich Sie jemals wiedersehen würde.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado hat meinen direkten Befehl gebrochen. Ich hatte ihm strengstens verboten, sich dir entgegenzustellen, mein Sohn, ich wusste, wie es für ihn enden würde. Und was ich vorausgesehen habe, ist eingetreten. Seine Mission war es, dich nach Tayasal zu begleiten, da er schon einmal dort gewesen war.\nDarüber hinaus sollte seine Staffel und eine Kompanie spanischer Soldaten dich gegen Itza oder Mosquito-Angriffe verteidigen. Alonso hat unwürdig gehandelt, getrieben von einem egoistischen Verlangen nach Rache, .\nEr hat nicht nur die Expedition nach Tayasal versagt und die ihm anvertrauten Soldaten und Schiffe dem Untergang geweiht, sondern auch in deinem Herzen Misstrauen und Groll gegen mich gesät. Ich versichere dir, mein Sohn, ich stehe voll und ganz auf deiner Seite. Wir müssen zusammen gegen diese gegenwärtige Dunkelheit stehen.";
			link.l1 = "Ich möchte das gerne glauben.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Sei versichert, "+pchar.name+". Ich, ein treuer und engagierter Diener unseres Herrn und Erlösers Jesus Christus und Repräsentant seiner Kirche, bin von einer Sache motiviert: das Ende der Welt zu verhindern, bis alle Seelen die Chance hatten, das Wort unseres gesegneten Herrn zu hören. Und das bedeutet, den diabolischen Agenten zu stoppen, der derzeit in den Händen eines dämonenbesessenen Indianers ruht. Ich vermutete dies sofort und bin jetzt völlig sicher. Du wurdest vom Herrn als Sein Champion im Kampf gegen Satan auserwählt.";
			link.l1 = "Aber warum sagst du das, Vater?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Sie haben es geschafft, etwas zu tun, was weder ich mit der Hilfe all meiner Agenten, noch Baron Mendosa und Don Diego, noch irgendjemand anderes geschafft hat. Sie haben es geschafft, die verfluchte Insel zu finden und das Artefakt von Kukulcan darauf zu suchen. Nicht wahr?";
			link.l1 = "Ja, ich habe Kukulcans Maske.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Und würdest du behaupten, all dies sei zufällig geschehen? Durch einen Zufall? 'Das Herz des Menschen plant seinen Weg, aber der Herr bestimmt seine Schritte.' Mein Sohn, der Allmächtige hat dich auf diesen Weg geführt! Er hat deine Hand im Kampf gestärkt, deine Füße auf den richtigen Weg gelenkt und dich in Zeiten der Gefahr beschützt! 'Siehe, das Schwert des Herrn fällt zum Gericht über Edom, über das Volk, das ich dem Untergang geweiht habe!'";
			link.l1 = "Ähem... Vater, aber die Mission ist im Grunde schon erfüllt. Ich habe die Maske. Bedeutet das nicht, dass Kukulcans besessene Hülle nicht in unsere Geschichte eintreten und sie ändern kann...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Du irrst dich, mein Sohn. Der Dämon kann durch dieses Tor gehen, ob er diese Maske hat oder nicht. Die Maske erleichtert ihm nur seine dunklen Taten. Das Einzige, was ihn aufhalten kann, ist die vollständige Zerstörung der höllischen Tore.";
			link.l1 = "Don Alonso hat mir das Gleiche gesagt...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "Und er hatte recht! Im Namen unseres Herrn Jesus Christus und seiner gesegneten Mutter rufe ich dich auf, das Kreuz gegen dieses Übel zu erheben, mein Sohn! Du kannst die große Mission, die dir auferlegt wurde, nicht ablehnen. Ich und das gesamte Christentum sind alle auf dich angewiesen, mein Sohn.";
			link.l1 = "Eure Exzellenz, das ist zu viel. Ich fühle mich wirklich... irgendwie unbehaglich...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Deine Bescheidenheit ist dir zu Ehren, mein Sohn, aber dies ist nicht die Zeit, das schüchterne Mädchen zu spielen. Sei nicht zaghaft oder ängstlich, denn der Herr, dein Gott, geht vor dir her, um dir den Sieg zu geben! Tritt in diese Schlacht ein um deiner Lieben willen, um aller Christen willen... und wenn nicht für sie, dann um deinetwillen, denn wenn dieser Dämon siegreich hervorgeht, wirst du zusammen mit allen anderen untergehen.";
			link.l1 = "Ich nehme an, du hast mich überzeugt, Vater. Ich hatte gezögert, wegen meiner Situation einen Kreuzzug nach Tayasal zu unternehmen, aber jetzt habe ich keine Zweifel mehr. Womit kannst du mir helfen?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Nur zwei Männer wussten, wie man nach Tayasal kommt: Alonso de Maldonado und Miguel Dichoso. Don Alonso ist tot. Und Dichoso... Mir wurde gesagt, dass er kürzlich in Sharptown auf Isla Tesoro gesehen wurde. Vielleicht ist er immer noch dort. Du musst Dichoso finden und ihn überzeugen, dein Führer zu sein.\nOb durch Gold oder Gewalt, du musst diesen Mann dazu bringen, dich nach Tayasal zu bringen. Dort wirst du die Pforten der Hölle finden und dort wirst du sie versiegeln.";
			link.l1 = "Und was ist mit den Männern?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "Die letzte Kompanie von Soldaten, die ich hatte, stand unter dem Befehl von Alonso de Maldonado. Ach, ich habe nicht die Möglichkeit, eine weitere Truppe spanischer Soldaten zu versammeln. Ich habe all mein Ansehen bei der örtlichen Garnison verspielt. Du wirst es mit Hilfe deiner eigenen Männer tun müssen, mein Sohn. Aber ich werde dir so gut ich kann bei allem anderen helfen.";
			link.l1 = "Welche Art von Hilfe?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Wir müssen jeden Vorteil nutzen, den wir in diesem Kampf haben, sowohl materiell als auch geistlich. Ich habe Vater Adrian gebeten, mich in fünf Tagen in dieser Kapelle zu treffen. Er wird heilige Amulette für dich mitbringen. Amulette, die den Kriegern Christi im Kampf helfen können. Er wird euch auch mit allen Arten von Tränken versorgen. Was mich betrifft, akzeptiere dieses Schwert, mein Sohn.\nDas ist ein altes Schwert der Tempelritter, eine mächtige Waffe unserer Vorfahren. Noch scharf und strahlend mit dem Segen der Kirche. Nur die größten Ritter hatten die Ehre, es zu führen. Nimm es, besitze es mit Stolz und zerschmettere die Feinde unseres Glaubens mit dem Namen Jesus Christus auf deinen Lippen!";
			link.l1 = "Danke dir! Dieses Schwert ist absolut fantastisch. Ich bin sprachlos...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Gott segne dich, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "So sei es!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Und nun geh, mein Sohn. Möge Gott über dich wachen, möge er dich niemals verlassen, weder auf deiner Suche, noch auf deinem Weg, noch im Kampf. Such nach Miguel Dichoso und mach dich mit seiner Hilfe auf den Weg nach Tayasal. Vergiss nicht Pater Adrian, er wird dich mit allen Amuletten und Heilmitteln ausstatten, die du benötigen könntest. Und jetzt ist es an der Zeit für mich, nach Santiago zurückzukehren. Auf Wiedersehen, mein Sohn. Vaya con Dios.";
			link.l1 = "Auf Wiedersehen, Vater Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
