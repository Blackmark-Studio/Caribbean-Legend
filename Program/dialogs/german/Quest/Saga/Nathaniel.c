// Натаниэль Хоук - пиратский барон Марун-Тауна
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
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "diffindoor":
			PlaySound("Voice\English\saga\Nataniel Hawk-02.wav");
			dialog.text = "Ah... wer bist du, verdammt?.. Khe... (schwerer Husten mit Heiserkeit) Verdammte Schwäche...";
			link.l1 = "Grüße, Nathaniel. Du bist doch Nathaniel Hawk, nicht wahr?";
			link.l1.go = "diffindoor_1";
		break;
		
		case "diffindoor_1":
			dialog.text = "Ja, das bin ich, wenn ich mich noch so nennen darf. Ich war einst Nathaniel Hawk, aber jetzt bin ich nur noch ein trauriger Haufen Scheiße. Verdammt sei diese Statue! Sie hat mir das ganze Leben ausgesaugt.";
			link.l1 = "Ich kenne dieses Gefühl...";
			link.l1.go = "diffindoor_2";
		break;
		
		case "diffindoor_2":
			dialog.text = "Wie könntest du, Junge, wenn du nicht einmal begreifst, wovon ich spreche? A-kha... Weißt du, wie es sich anfühlt, zu einem halbtoten, alten Mann zu werden, obwohl ich noch eine Minute davor gesund und stark war?\nIch habe viel gesehen, ich dachte, dieser alte indische Tempel, den ich in meiner Jugend besuchte, hätte meine Fähigkeit überrascht zu werden getötet, aber das... warum habe ich es nicht kommen sehen! Diese verdammte Statue sah genauso aus wie das alte Idol, das die Tür zum Tempel öffnete!";
			link.l1 = "Gut, Nathan, lass uns reden. Lass mich mich vorstellen, ich bin "+GetFullName(pchar)+". Zuerst, ich verstehe dich sehr gut, weil ich auf die gleiche Weise hierher gekommen bin, wie du - mit dem Kukulcan-Portal.";
			link.l1.go = "diffindoor_3";
		break;
		
		case "diffindoor_3":
			dialog.text = "Wirklich?! Warum siehst du dann so gut aus? Oder hat dieser... Kukulcan nur mir geschadet?";
			link.l1 = "Snake Eye, der Miskito-Schamane, der dir geholfen hat zu entkommen, hat mir einen sehr starken Trank gegeben. Ich habe ihn getrunken, sobald ich in der San Augustine aufgewacht bin. Es hat mich vollständig geheilt. Ich bin mir sicher, dass Snake Eye auch dir helfen kann. Wir müssen dich nur zu ihm bringen.";
			link.l1.go = "diffindoor_4";
		break;
		
		case "diffindoor_4":
			dialog.text = "Ah, dieser Indianer! Ein Trank? Und warum hat er mir nicht auch einen gegeben?";
			link.l1 = "Er sagte, es gäbe keine Zeit. Du wurdest verfolgt und das Einzige, was er tun konnte, war dir den Weg zur Flucht zu zeigen - das Portal.";
			link.l1.go = "diffindoor_5";
		break;
		
		case "diffindoor_5":
			PlaySound("Voice\English\saga\Nataniel Hawk-01.wav");
			dialog.text = "Flucht? Oh... Siehst du meinen aktuellen Zustand nicht? Ich kann nicht mal ein Säbel halten. Wie kannst du das eine Flucht nennen? Gott sei Dank, gibt es noch gute Menschen in dieser Welt. Ole, Gott segne ihn... Kennst du Ole?";
			link.l1 = "Ja. Tatsächlich hat er mir von dir erzählt, er hat mir erzählt, wie er dich mit Ratten gefüttert hat und wie du weiter trinkst, Flasche für Flasche...";
			link.l1.go = "diffindoor_6";
		break;
		
		case "diffindoor_6":
			dialog.text = "Ich werde schneller sterben als eine angezündete Kerze, wenn ich keinen Rum trinke. Es ist das einzige, was mich am Leben hält. Rum...";
			link.l1 = "Fühlst du dich immer noch so schlecht? Wie nach der Teleportation?";
			link.l1.go = "diffindoor_7";
		break;
		
		case "diffindoor_7":
			dialog.text = "Nun, ich fühle mich nicht ganz gleich... Aber auch nicht wirklich besser. Kumpel, sag mir, warum musstest du den alten Nathan sehen? Warum zum Teufel bist du hierher gekommen, auf diesen alten, verrotteten Kutter? Um mit mir zu plaudern?";
			link.l1 = "Tatsächlich, ja. Du wirst es mir nicht glauben, aber der Grund, warum ich all die Mühe mit der Teleportation auf mich genommen habe, war dich zu finden. Ich arbeite für die Bruderschaft der Küste und vertrete Jan Svenson.";
			link.l1.go = "diffindoor_8";
		break;
		
		case "diffindoor_8":
			dialog.text = "Verdammt... der Forest Devil? Argh... Bist du hier, um mich zu erledigen? Tatsächlich aber denke ich eher nicht? Du redest zu viel für einen Attentäter. Bitte - quäle mich nicht. Wenn du beauftragt wurdest, etwas aus mir herauszubekommen - Ich werde dir alles selbst erzählen, ich habe nichts zu verbergen.";
			link.l1 = "Was meinst du? A-ah, ich verstehe. Du, genau wie Danielle, denkst, dass Svenson derjenige war, der diesen Hinterhalt auf dein Leben im Urwald arrangiert hat. Ich kann dir versichern, dass Jan es nicht getan hat. Im Gegenteil, er steht auf deiner Seite und macht sich große Sorgen um dein Verschwinden.";
			link.l1.go = "diffindoor_9";
		break;
		
		case "diffindoor_9":
			dialog.text = "Wirklich? Das freut mich verdammt zu hören. Und ich habe schon gedacht... aber wer hat das getan? Mein Trupp wurde in Minuten zerstört. Sie haben auf uns gewartet. Sie hatten sogar Schiffskanonen! Sie haben die Hälfte meiner Männer mit Kartätschenkugeln niedergemäht und uns dann mit ihren Musketen fertig gemacht...";
			link.l1 = "Ehrlich gesagt, ich kenne die Einzelheiten nicht, aber ich bin sicher, dass Jackman hinter all dem steckt. Zu viele Zufälle, zuerst Blaze, dann du... Jackman will die Macht ergreifen und beseitigt jeden, der sich ihm in den Weg stellt. Er regiert jetzt Maroon Town an deiner Stelle.";
			link.l1.go = "diffindoor_10";
		break;
		
		case "diffindoor_10":
			dialog.text = "Jackman? Bastard! Eh...die Bruderschaft ist in den letzten Jahren gespalten worden, alles war vorher anders. Zachariah ist mit seinen religiösen Angelegenheiten verrückt geworden, Tyrex scheißt auf alles und Barbazon interessiert sich nur für Dublonen. Vor zwanzig Jahren war alles anders...";
			link.l1 = "Wie haben sie dich gefangen genommen? Erzähl mir mehr.";
			link.l1.go = "diffindoor_11";
		break;
		
		case "diffindoor_11":
			dialog.text = "Es gibt nichts Interessantes zu erzählen! Wie ich schon sagte, diese Banditen haben das Ganze geplant. Sie handelten ordentlich, sie waren koordiniert und folgten eindeutig jemandes Befehlen. Sie hätten mich hundertmal töten können, aber sie taten es nicht. Sie wollten mich lebendig. Sie brachten mich zu einer verlassenen Mine und sperrten mich in eine der Hütten. 'Bis der Boss kommt', sagten sie.\nIch dachte, dass Svenson der Boss war, aber es scheint, dass Jackman das Sagen hat. Ich weiß nicht, was er von mir hätte wollen können, aber ich bin sicher, ich hätte nicht lange gelebt, nachdem ich mit ihm gesprochen hätte.";
			link.l1 = "Ich habe daran keinen Zweifel. Svenson ist sicher, dass Jackman Blaze Sharp getötet hat... Wie konntest du entkommen?";
			link.l1.go = "diffindoor_12";
		break;
		
		case "diffindoor_12":
			dialog.text = "Dieser indische Snake Eye hat es irgendwie geschafft, in die Mine zu schleichen. Soweit ich verstehe, mögen die Miskito keine Banditen. Wie auch immer, aus irgendeinem Grund hat Snake Eye meine Flucht arrangiert. Er grub einen Tunnel zu mir, kam hinein, schnitt meine Seile durch und wir rannten in den Dschungel.\nEr wollte mich zu seinem Dorf bringen, zu den Miskito. Aber es sieht so aus, als ob Jackman mich wirklich wollte, da eine große Jagd organisiert wurde. Sie waren uns auf den Fersen. Snake Eye tat sein Bestes, um sie zu täuschen, aber sie schafften es immer, unsere Spur zu finden. Sie hatten gute Pfadfinder, kein Zweifel.\nWir waren nahe an Snake Eye's Dorf, als sie uns endlich fanden. Zu diesem Zeitpunkt war mein Magen seit zwei Tagen leer und ich war völlig verschwendet, da ich auch mein Bein stark verletzt hatte. Es war Mitternacht und ich erinnere mich noch, wie hell der Stern über der Statue war... Snake Eye sagte, dass meine einzige Chance darin bestand, zum Idol zu gelangen und es zu berühren.\nIch dachte, der Mann sei verrückt, aber du weißt ja, was man über das Ergreifen von Strohhalmen sagt. Ich humpelte zur Statue, berührte sie... und dann begannen verrückte Dinge zu passieren!";
			link.l1 = "Du musst nicht weiter erzählen, ich weiß, was danach passiert ist.";
			link.l1.go = "diffindoor_13";
		break;
		
		case "diffindoor_13":
			dialog.text = "Ich hatte mich im nassen Laderaum eines gestrandeten Schiffes wiedergefunden. Ich war halb tot. Konnte nicht laufen, nur krabbeln. Mein Zustand verschlechterte sich von Minute zu Minute. Ole tauchte gerade rechtzeitig auf. Er zwang mir eine karibische Mischung auf, die schmeckte wie Dreck, eine Mischung aus Antidot und Heil-Essenz. Dann gab er mir Rum.\nIch fühlte mich sofort besser. Dann fand er ein altes Holzstück und brachte mich hierher. Ich lebe seit einiger Zeit hier, weiß nicht genau wie lange, ich habe den Überblick über die Zeit verloren.";
			link.l1 = "Alles wird gut, Nathan. Svenson und ich haben große Pläne und deine Rolle darin ist sehr bedeutend. Du musst zu deiner Position in Maroon Town zurückkehren und wir werden uns um diesen Abschaum Jackman kümmern.";
			link.l1.go = "diffindoor_14";
		break;
		
		case "diffindoor_14":
			dialog.text = "Maroon Town? Und wie genau stellst du dir das vor? Schau mich an, ich bin ein mit Rum getränktes Wrack! Wertlos... Nein, die Jahre meiner Autorität über Maroon Town sind für immer vorbei. Ich bin in diesem verfluchten Schiffsfriedhof gefangen. Wie lange werde ich durchhalten? Einen Monat, zwei, ein Jahr?\nUnd dann werde ich auf diesen verfaulten Planken liegen und Ole wird das, was von Nathaniel Hawk übrig ist, ins Meer werfen. Das Schlimmste ist, dass ich meine Dannie nie wieder sehen werde. Eh, es ist vorbei, Kumpel.";
			link.l1 = "Sei nicht so pessimistisch. Ich werde dich hier rausbringen.";
			link.l1.go = "diffindoor_15";
		break;
		
		case "diffindoor_15":
			dialog.text = "Wie wirst du mich hier rausbringen? Und wie werden wir diesen Ort verlassen? Es gibt keine Schiffe. Willst du ein Floß bauen?";
			link.l1 = "Nein. Ich werde diesen Ort genau so verlassen, wie ich hierher gekommen bin. Ich weiß, wo die Statue ist... nun, ungefähr. Ich werde sie finden und dann komme ich zurück um euch, dich und Shark Dodson, abzuholen. Danach bringen wir dich zu Snake Eye. Er wird dich heilen.";
			link.l1.go = "diffindoor_16";
		break;
		
		case "diffindoor_16":
			dialog.text = "Was hast du gesagt? Shark Dodson? Ist Steve auch hier? So ein merkwürdiger Ort...";
			link.l1 = "Ja, er ist hier. Er ist sozusagen der 'Gouverneur' dieser Insel. Ich habe ihn nach dir gefragt, aber er weiß nichts.";
			link.l1.go = "diffindoor_17";
		break;
		
		case "diffindoor_17":
			dialog.text = "Und er sollte es auch nicht. Ich will nicht, dass er mich in diesem Zustand sieht. Du hast gesagt, dass der Schamane mich heilen wird... Ich kann es kaum glauben. Du hast auch Dannie erwähnt... Hast du sie gesehen?";
			link.l1 = "Ja. Sie hat mich selbst in Blueweld gefunden. Sie hat mein Gespräch mit Svenson belauscht und verstanden, dass Jan nicht vorhatte, dich zu töten und dass er gegen Jackman arbeitet. Sie hat sich meinem Schiff als Offizierin angeschlossen, um mir zu helfen, dich zu finden.";
			link.l1.go = "diffindoor_18";
		break;
		
		case "diffindoor_18":
			dialog.text = "Eh, meine liebe Dannie! Sie hat sich nicht verändert... so ungestüm wie in ihrer Jugend... Du kannst dir nicht vorstellen, wie sehr ich sie jetzt sehen und umarmen möchte! Ich habe viel nachgedacht, während ich hier lag. Siehst du, Kumpel, man beginnt die Dinge in einem anderen Licht zu sehen, wenn man dem Tod nahe ist. Ich habe so wenig Zeit mit meiner Frau verbracht!\nSeeräuber, offizielle Geschäfte der Brüder, die Herrschaft über Maroon Town. Und sie hat mich immer in allem unterstützt: war wochenlang allein, hatte Streitigkeiten mit anderen Piraten, während ich weg war, kommandierte unser Schiff... Meine Dannie ist die beste Frau der Welt! Und ich... ich hätte ihr öfter sagen sollen, dass ich sie liebe!\nIch erinnere mich an den Tag, an dem wir beschlossen, zusammen zu sein! Tatsächlich war das der Tag, an dem ich zum ersten Mal auf übernatürliche Dinge traf und kämpfte. Alles geschah wegen dieses verfluchten Idols, das genau wie die Statuen aussah. Du hast nichts dagegen, eine Geschichte zu hören? Sie ist ziemlich interessant.";
			link.l1 = "Überhaupt nicht! Erzähl es mir!";
			link.l1.go = "story";
			link.l2 = "Nathan, wir haben keine Zeit für angenehme Erinnerungen. Erzähl mir später davon, wenn wir im Miskito-Dorf mit einer Flasche Wein sitzen werden.";
			link.l2.go = "diffindoor_19";
		break;
		
		case "story":
			dialog.text = "Es war vor fünfundzwanzig Jahren... Ich war jung, leidenschaftlich und unruhig. Die Karibik war mein Spielplatz. Ich kannte Dannie schon damals. Ich mochte sie, wirklich, und das Gefühl war gegenseitig. Aber wir stritten oft, zankten und neckten uns gegenseitig. Dumme Jugend... Ich glaube, wir waren damals eine große Unterhaltung für die angesehenen Seeleute!\nWie auch immer, irgendwie wurden Dannie und ich in die gleiche Geschichte verwickelt. Wir hatten eine Karte von Khael Roa gefunden und man sagte uns, dass es DER Ort war, um indisches Gold zu finden. Wir hatten auch ein seltsam aussehendes goldenes Idol gefunden, eine kleinere Kopie des oberen Teils der Statuen.\nDas Idol war gefährlich, es saugte die Lebenskraft aus denen, die es trugen. Aber wir benötigten diesen verfluchten Gegenstand, um in die Schatzkammer im Tempel zu gelangen. Das einzige Problem war, dass wir keine Ahnung hatten, wie man es richtig benutzt. Dannie und ich segelten zur Insel. Dort war ein alter Tempel, überwuchert von Gras und Bäumen. Als wir eintraten, befanden wir uns in einem riesigen Labyrinth.\nWir schafften es, den richtigen Weg zu finden und erreichten den zentralen Teil des Labyrinths. Wir dachten, es wäre eine Sackgasse, aber als die Verzweiflung anfing, uns zu besiegen, sahen wir eine seltsame Plattform mit einer kleinen Fassung und einem Bild darin. Ich steckte das Idol in die Fassung und...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "idol";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_1";
		break;
		
		case "story_1":
			dialog.text = "Die Steinplattform senkte sich einige Zoll nach unten und eine der Wände entpuppte sich als geheimer Durchgang. Das Idol blieb in der Plattform stecken, es gelang mir nicht, es wieder herauszuziehen. Schließlich erreichten wir eine riesige Halle. Was für ein wunderschöner Anblick! \nDie prächtigste Struktur, die ich je gesehen habe. Schnitzereien an den Wänden, riesige Statuen... Wir durchsuchten die ganze Halle, fanden aber keine Spur von Schätzen.";
			link.l1 = "Heh, das passiert uns Leuten ziemlich oft. Viel Mühe und am Ende kein Ergebnis...";
			link.l1.go = "story_2";
		break;
		
		case "story_2":
			dialog.text = "Es war nicht umsonst. Schließlich betraten wir einen Thronsaal mit einer riesigen Vogelstatue am Ende. In der Nähe der Statue war ein mystisches Licht, es sah genau so aus wie das Licht über dem Idol um Mitternacht. Wir gingen näher und sahen eine wunderschöne fliegende Kugel. Ich schwöre, ich erzähle dir die reine Wahrheit!\nEs war echt, aber gleichzeitig fühlte es sich so an, als ob es das nicht war. Während ich nachdachte, berührte Dannie - oh, diese rücksichtslose Teufelin, die Kugel. Sie begann noch heller zu leuchten und verwandelte sich schließlich in einen kleinen Gegenstand in ihren Händen...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "temple";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_3";
		break;
		
		case "story_3":
			dialog.text = "Es schien, als hätten wir eine Sakrileg begangen. Der Tempel erwachte zum Leben: Alles um uns herum begann sich zu bewegen, die Wände bebten und alles bröckelte. Es war, als hätten wir alle indischen Dämonen geweckt und sie warfen all ihren Zorn auf uns zurück...";
			link.l1 = "Wahnsinn!";
			link.l1.go = "story_4";
		break;
		
		case "story_4":
			dialog.text = "Es ist schwer zu glauben, ich weiß. Aber...";
			link.l1 = "Ich hätte dich vor einem halben Jahr noch als Lügner bezeichnet. Aber ich lebe schon lange genug in der Karibik, um zu wissen, dass ich keinen Grund habe, dir zu misstrauen. Mach weiter. Wie hast du überlebt?";
			link.l1.go = "story_5";
		break;
		
		case "story_5":
			dialog.text = "Wir rannten aus dem Tempel und hatten das Glück, rechtzeitig auf unser Schiff zu kommen. Ich befahl, den Anker zu lichten, wir wollten so schnell wie möglich von diesem Ort segeln.";
			link.l1 = "Heh! Also, am Ende hast du nur ein seltsames Artefakt anstelle von Schätzen gefunden? Was für ein schöner und gleichwertiger Ersatz, he-he... Und hast du herausgefunden, wie man es benutzt? Oder war es nutzlos?";
			link.l1.go = "story_6";
		break;
		
		case "story_6":
			dialog.text = "Warte einen Moment. Die Geschichte ist noch nicht vorbei. Dannie hatte das Artefakt und sobald wir uns entschieden, in die Kabine zu gehen, um es zu studieren, wurde der Himmel dunkel und ein Schiff tauchte auf. Oh Gott! Es war...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "blackpearl";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_7";
		break;
		
		// вот тут делаем развилку, в зависимости прошёл ли игрок Калеуче
		case "story_7":
			dialog.text = "... Van der Decken selbst!!";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Van der Decken? Hm...";
				link.l1.go = "story_8_1";
			}
			else
			{
				link.l1 = "Und wer ist er?";
				link.l1.go = "story_8";
			}
		break;
		
		case "story_8":
			dialog.text = "Hast du noch nie vom Fliegenden Holländer gehört?";
			link.l1 = "Wer hat noch nicht vom Fliegenden Holländer gehört! Ich habe bereits einen Holländer getroffen und seinen Kapitän auf den Grund des Meeres geschickt. Er war nur ein gewöhnlicher Pirat, der sein Schiff mit Maskeradenmüll wie Algen und zerrissenen Segeln schmückte.";
			link.l1.go = "story_9";
		break;
		
		case "story_8_1":
			dialog.text = "Ja, aber das war Van der Decken selbst, der Kapitän des Fliegenden Holländers!";
			link.l1 = "Interessant. Bitte, fahre fort. Wie habt ihr es geschafft durchzukommen?";
			link.l1.go = "story_11";
		break;
		
		case "story_9":
			dialog.text = "Eh-heh, Freund... Du hast irgendeinen Spaßvogel versenkt, aber ich spreche von der echten Fliegenden Holländerin. Ein riesiges Kriegsschiff. Gott bewahre dich davor, ihr jemals auf offener See zu begegnen. Ihr Kapitän Van der Decken und seine Mannschaft wurden einst verflucht, für immer ruhelos über das Meer zu segeln.\nIch erinnere mich an ihre zerrissenen schwarzen Segel, die Mannschaft aus toten Männern, die auf Deck standen mit gezogenen Klingen, und der Kapitän selbst - ein gruseliges Skelett mit einem schwarzen Dreispitz... Jesus...";
			link.l1 = "Sagst du die Wahrheit?";
			link.l1.go = "story_10";
		break;
		
		case "story_10":
			dialog.text = "Ich kann bei der Bibel schwören, dass ich nicht lüge... Ein Treffen mit dem 'Fliegenden Holländer' bedeutet nur den sicheren Tod. Sie ist mächtig, sehr mächtig, eine Salve ihrer Kanonen kann selbst eine schwere Fregatte und ihre Besatzung versenken... aber noch schlimmer, wie soll man gegen die Untoten kämpfen?";
			link.l1 = "Aber du hast diesen Alptraum überlebt!";
			link.l1.go = "story_11";
		break;
		
		case "story_11":
			dialog.text = "Es ist alles dank meiner lieben Dannie und dem indischen Artefakt, das wir aus dem Tempel genommen haben. Ich hatte befohlen, uns auf den Kampf vorzubereiten, aber ich wusste, dass es das Ende der Linie war. Der 'Fliegende Holländer' segelte auf uns zu und ich sah ihre schreckliche Mannschaft und Van der Decken selbst an Deck. Das Schiff begann, ihre Kanonen auf uns zu richten, aber...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "artefact";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_12";
		break;
		
		case "story_12":
			dialog.text = "Dannie hob das Artefakt hoch und ließ es fliegen. Ich hatte keine Ahnung, warum sie das getan haben könnte. Sie sprach etwas von ihrer weiblichen Intuition... Das Artefakt verwandelte sich zurück in eine leuchtende Kugel und explodierte, wodurch das Geisterschiff schwer beschädigt und seine Besatzung demoralisiert wurde. Ich befahl, das Feuer auf den Holländer zu eröffnen.\nDie erste Salve ließ sie erschüttern. Wir griffen erneut an und schossen ein zweites Mal auf ihren verrotteten Rumpf, gerade bevor sie sich von dem Einfluss des Artefakts erholen konnten und das Feuer erwiderten...";
			link.l1 = "Also, du musstest sowieso gegen sie kämpfen?";
			link.l1.go = "story_13";
		break;
		
		case "story_13":
			dialog.text = "In der Tat. Und ich schwöre, es war der härteste Kampf meines Lebens. Ihr verdammter Trog konnte kaum über Wasser bleiben, und doch konnten sie die Hälfte meines Rumpfes zerstören, bevor wir sie in die Luft jagten, indem wir ihre verfluchte Pulverkammer sprengten.";
			link.l1 = "Hast du es versenkt? Hast du den Fliegenden Holländer versenkt?";
			link.l1.go = "story_14";
		break;
		
		case "story_14":
			dialog.text = "Ja, verdammt noch mal! Ich habe es getan!..";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "ending";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_15";
		break;
		
		case "story_15":
			dialog.text = "Dieses verfluchte Schiff ging unter. Die Sonne begann wieder zu scheinen und der Himmel wurde klar. Und wir begannen endlich, uns glücklich zu fühlen... oh, du kannst dir gar nicht vorstellen, wie glücklich wir waren. Wir hatten den Tod selbst besiegt. Momente wie diese bringen Menschen zusammen. Und wir taten, was wir schon lange vor dieser Begegnung hätten tun sollen - wir umarmten uns, küssten uns, sagten, dass wir uns liebten und schworen, für immer zusammen zu bleiben.";
			link.l1 = "Und ihr seid immer noch zusammen...";
			link.l1.go = "story_16";
		break;
		
		case "story_16":
			dialog.text = "Ja, das sind wir. Ich und Dannie haben geheiratet und ich habe es nie bereut. Du wirst keine bessere Ehefrau und Waffenschwester finden.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "So, jetzt weiß ich endlich, wer dieser geheimnisvolle Kapitän ist, der es geschafft hat, den 'Fliegenden Holländer' zu versenken... Du bist ein echter Held!";
				link.l1.go = "story_17_1";
			}
			else
			{
				link.l1 = "Also, ihr zwei seid echte Helden, was? Ihr habt es geschafft, das berühmte Geisterschiff zu versenken. Warte! Du hast gesagt, dass der 'Fliegende Holländer' noch fliegt... Wie kann das möglich sein, wenn er auf dem Meeresgrund liegt?";
				link.l1.go = "story_17";
			}
		break;
		
		case "story_17":
			dialog.text = "Eh, Kumpel, du weißt gar nichts... Du kannst Van der Decken versenken, aber du kannst ihn nicht töten. Der Fluch auf ihm und seiner Mannschaft ist zu stark, viel stärker als der Tod...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_17_1":
			dialog.text = "Ein Held mag ich sein, aber Van der Decken kann nicht getötet werden. Der Fluch, der über ihm, seiner Mannschaft und seinem Schiff hängt, ist stärker als der Tod...";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Natanstory = "VDDrepair";
			AddDialogExitQuest("Video_story");
			NextDiag.TempNode = "story_18";
		break;
		
		case "story_18":
			dialog.text = "Jedes Mal, wenn du das Schiff versenkst, repariert die Mannschaft ihr Schiff, bringt es wieder hoch und setzt ihre ewige Reise fort.";
			if (CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l1 = "Ich weiß, Nathaniel, ich weiß. Dennoch, der Fliegende Holländer wird niemanden mehr Ärger machen.";
				link.l1.go = "story_22";
			}
			else
			{
				link.l1 = "Nun, das klingt wie ein Märchen. Ein geteiltes und versenktes Schiff zu reparieren...";
				link.l1.go = "story_19";
			}
		break;
		
		case "story_19":
			dialog.text = "Die Leute haben das Schiff viele Male gesehen, nachdem wir es versenkt haben... Du entscheidest, ob du den Sichtungen glaubst.";
			link.l1 = "Und wo befindet sich diese Insel mit dem Tempel, von dem ihr das Artefakt habt?";
			link.l1.go = "story_20";
		break;
		
		case "story_20":
			dialog.text = "Er ist nicht kartiert und irgendwo im Osten der Karibik gelegen. Ich habe eine Karte der Insel in Maroon Town gelassen, aber wie du sehr gut weißt, kann ich jetzt nicht dorthin segeln. Und um ehrlich zu sein, ich will es nicht. Das einzige, an das ich mich erinnere, ist sein Name - Khael Roa...";
			link.l1 = "So eine interessante Geschichte. Ich würde gerne diese Insel finden!";
			link.l1.go = "story_21";
		break;
		
		case "story_21":
			dialog.text = "Oh, das empfehle ich nicht... Ich werde es sicherlich nicht noch einmal besuchen.";
			link.l1 = "Ich möchte es trotzdem besuchen... Gut, danke für deine interessante Geschichte! Jetzt weiß ich auch mehr über deine Frau. Ihr beide seid lebende Legenden!";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
			pchar.questTemp.NatanStory = "true";
		break;
		
		case "story_22":
			dialog.text = "Was willst du damit andeuten, Kamerad? Habe ich dir nicht gerade gesagt, dass er nicht getötet werden kann?";
			link.l1 = "Nathaniel, ich bin nach Khael Roa gesegelt. Und ich besuchte den Tempel der Chavins, wo du, Danielle und ein alter Mann vor einem Vierteljahrhundert gewesen waren. Das Artefakt, das du damals aus dem Tempel genommen hast, wurde 'Kugel der aufgehenden Sonne' genannt. Dieses Artefakt war es, das die Aufmerksamkeit des 'Fliegenden Holländers' auf dich zog. Sein Kapitän war ein Liebhaber von Chavins Artefakten.";
			link.l1.go = "story_23";
		break;
		
		case "story_23":
			dialog.text = "Du bist in Khael Roa gewesen? Aber das kann einfach nicht sein! Erzählst du mir die Wahrheit?";
			link.l1 = "Ich schwöre es. Als du mir von dem Labyrinth und der Statue des Riesenvogels erzählt hast, wusste ich sofort, wo dieser Ort war. Der karibische Schamane Tuttuathapak hat mir von deinen Abenteuern erzählt. Er war es, der mich zu dieser Insel führte. Sie liegt östlich von St. Christopher. Sie ist sehr klein, ringförmig. Ringsherum sind Felsen und innen eine kleine Bucht. Und es gibt nur einen überwachsenen Weg, der zu einem Tempel führt, der in Form einer Pyramide gebaut ist.";
			link.l1.go = "story_24";
		break;
		
		case "story_24":
			dialog.text = "Ja! Das ist Khael Roa. Aber warum bist du dorthin gegangen?";
			link.l1 = "Um den Fluch der Caleuche... nun, der 'Fliegenden Holländerin' zu entfernen. Eigentlich hieß sie 'Fliegendes Herz', und der Name ihres Kapitäns war 'Balthazar de Cordes'. Vor fünfzig Jahren wurde er von Yum Cimil, einem indischen Gott des Todes, verflucht. Ich habe den Jadetotenkopf von Yum Cimil, der vor einiger Zeit von Balthazar aus dem Tempel gestohlen wurde, genommen und ihn wieder auf den Sockel vor dieser Kondorstatue gestellt...";
			link.l1.go = "story_25";
		break;
		
		case "story_25":
			dialog.text = "";
			link.l1 = "...indem ich den Schädel zurückbrachte, habe ich den Fluch der Caleuche aufgehoben. Und da ich noch zwei andere Chavins-Amulette bei mir hatte, griff sie mich in der Nähe der Insel an, genau wie damals bei dir. Aber ohne den Fluch war Balthazar nicht mehr unsterblich, genau wie Tuttuathapak sagte. Also... der 'Fliegende Holländer' ist nicht mehr. Ich habe mich persönlich um sie gekümmert.";
			link.l1.go = "story_26";
		break;
		
		case "story_26":
			dialog.text = "Donner und Blitzen! Ich bin verblüfft! Du.. Du nimmst den alten Nathan nicht auf den Arm, oder? Nein, ich kann in deinen Augen sehen, dass du die Wahrheit sagst! Du bist ein echter Held!";
			link.l1 = "Ein Held oder nicht, aber ich habe meinen fairen Anteil an Abenteuern gesehen, genau wie du auch. Nun, sicherlich werden wir noch viele Male über die Vergangenheit sprechen, denn jetzt haben wir ein gemeinsames Thema.";
			link.l1.go = "diffindoor_19";
			DeleteAttribute(pchar, "questTemp.LSC.Natanstory");
		break;
		
		case "diffindoor_19":
			dialog.text = "Wirst du mich jetzt verlassen, Freund?";
			link.l1 = "Ja, Nathan. Bitte, halte durch bis zu meiner Rückkehr. Pass auf dich auf. Und am wichtigsten, bleib am Leben bis ich zurück bin und alles wird gut. Die Bruderschaft der Küste braucht dich, Danielle braucht dich.";
			link.l1.go = "diffindoor_20";
		break;
		
		case "diffindoor_20":
			dialog.text = "Ist Dannie jetzt in deiner Mannschaft? Ich bitte dich, pass auf sie auf. Sie hat sich seit ihrer Jugend kein bisschen verändert, sie ist immer noch ein Draufgänger und wird nicht zögern, durch die Hölle zu gehen. Sag ihr, dass ich sie sehr liebe...";
			link.l1 = "Sicher werde ich das tun. Wir werden gemeinsam für dich zurückkehren, das verspreche ich dir, Nathan. Halte durch und halte deinen Kopf hoch. Ole wird sich um dich kümmern. Bis bald!";
			link.l1.go = "diffindoor_21";
		break;
		
		case "diffindoor_21":
			DialogExit();
			LAi_SetGroundSitTypeNoGroup(npchar);
			NextDiag.CurrentNode = "diffindoor_wait";
			pchar.questTemp.LSC.NatanTalk = "true"; // атрибут - разговор с Натаном состоялся
			AddQuestRecord("BaronReturn", "10");
			npchar.greeting = "nathaniel_1";
		break;
		
		case "diffindoor_wait":
			dialog.text = "Ah, du bist es, "+pchar.name+". Hast du die Insel noch nicht verlassen?";
			link.l1 = "Mach dir keine Sorgen, Nathan, alles läuft nach Plan. Ruhe dich jetzt aus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "diffindoor_wait";
		break;
		
		case "danny":
			PlaySound("Voice\English\saga\Nataniel Hawk-03.wav");
			dialog.text = "Danielle!.. Dannie! Meine Dannie!..";
			link.l1 = "...";
			link.l1.go = "danny_1";
		break;
		
		case "danny_1": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Nathaniel"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_6";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			NextDiag.CurrentNode = "danny_2";
		break;
		
		case "danny_2":
			dialog.text = "Danke dir, mein Freund. Danke für alles und vor allem für meine Dannie...";
			link.l1 = "Gern geschehen, Nathan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "danny_2";
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = "Schau mal, wer gerade hereingeschneit ist! Es ist "+GetFullName(pchar)+"  selbst! Komm rein, komm rein, Freund! Wie geht es dir?";
			link.l1 = "Mir gehts gut. Und du, Nathan? Ich sehe, dass es keine Trübsal mehr gibt. Du siehst gut aus. Snake Eye hat wirklich gute Arbeit geleistet!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Ja, dein Schamane ist ein Wunderheiler. Ich fühle mich sogar besser als vor dieser verdammt Teleportation! Ich fühle mich, als wäre ich zehn Jahre jünger! "+pchar.name+", Ich schulde dir viel. Und ich bin beeindruckt: du hast einem völligen Fremden geholfen, bist durch das verfluchte Portal gegangen, hast mich aus den Händen des Todes gerissen, mich zu meiner Frau zurückgebracht!\nUnd noch mehr! Du hast uns unser Schiff und Zuhause zurückgebracht. Du bist jetzt unser bester Freund. Für immer. Wenn du jemals etwas brauchst - du weißt, wen du fragen musst! Maroon Town wird dir immer Schutz, Unterstützung und eine Zuflucht bieten, falls du es brauchst.\nDas ganze Dorf wird für dich kämpfen, wenn du in Gefahr bist. In friedlichen Zeiten findest du hier Freundschaft, den besten Rum, ein weiches Bett und einen schönen Ort zum Ausruhen. Dannie und ich werden dafür sorgen.";
			link.l1 = "Danke, Baron! Ich bin aufrichtig froh, dich in guter Gesundheit zu sehen und... mit Dannie.";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			dialog.text = "Ich habe deinen Besuch erwartet, "+pchar.name+", und ich habe ein Geschenk vorbereitet - eine seltene und mächtige Waffe. Vielleicht musst du eines Tages zahlreiche Feinde mit einem Schuss niederstrecken und dieser Handmörser wird dir dabei helfen. 'Sclopetta' feuert spezielle Granaten ab, also habe ich auch Anweisungen vorbereitet, wie man sie herstellt. Hier, nimm es.";
			link.l1 = "Was für eine ausgezeichnete Waffe! Danke!";
			link.l1.go = "marun_town_3";
		break;
		
		case "marun_town_3":
			GiveItem2Character(pchar, "grape_mushket"); 
			GiveItem2Character(pchar, "recipe_grenade"); 
			Log_Info("Du hast einen Handmörser erhalten");
			Log_Info("Du hast eine Granatenanweisung erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Besuch uns öfter, "+pchar.name+"! Dannie und ich werden uns immer freuen, dich jederzeit zu sehen.";
			link.l1 = "Es wird mir ein Vergnügen sein. Erwartet mich bald!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "marun_town_4":
			dialog.text = "Ah, mein Freund "+GetFullName(pchar)+"! Komm rein, komm rein, Kapitän! Wie geht es dir? Brauchst du Hilfe?";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.NatanInfo"))
			{
				link.l2 = "Nathan, ich bin zu dir gekommen wegen einer sehr wichtigen Angelegenheit. Erinnerst du dich, als du mir auf der Insel der Verlassenen Schiffe erzählt hast, dass du und Dannie in einen indischen Tempel eingedrungen seid und die 'Fliegende Holländer' versenkt habt?";
				link.l2.go = "caleuche";
			}
			link.l1 = "Danke, mir geht es gut. Ich wollte euch beide nur sehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_4";
		break;
		
		case "caleuche":
			dialog.text = "Natürlich, tue ich es.";
			link.l1 = "Ich muss unbedingt zu dieser Insel mit dem Tempel gelangen. Du sagtest, du hättest eine Karte davon. Kannst du mir die Koordinaten geben?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Oh, Freund, das ist ein sehr gefährliches Unternehmen, weißt du... der Tempel von Khael Roa ist verflucht. Wenn du nur wüsstest, wer seine Korridore bewohnt...";
			link.l1 = "Im Moment ist es von Monstern bewohnt, die viel furchterregender sind als die, die du damals gesehen hast. Und ich werde trotzdem dorthin gehen.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Ich werde es mir nie verzeihen, wenn du dort umkommst. "+pchar.name+", Ich bitte dich: Vergiss dieses Unternehmen! Außerdem ist es dort, wo der 'Fliegende Holländer' am häufigsten gesehen wird...";
			link.l1 = "Ich bin ihm bereits begegnet und ich weiß, wie ich ihm entkommen kann. Nathan, bitte gib mir die Koordinaten von Khael Roa und erzähl mir alles, was du über diesen Tempel weißt, abgesehen davon, dass er von untoten Indianern bewohnt wird.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Oh, na gut... Ich kann dich nicht abweisen, aber... du hast keine Ahnung, was ich und Dannie dort erlebt haben! Khael Roa liegt östlich von Antigua. Ich habe seine Karte genau gefunden, als ich nach Maroon Town zurückkam, sie befindet sich bei... (schaut nach) den Koordinaten: 19 Grad 32' Nord, 62 Grad 25' West.";
			link.l1 = "Ich notiere seine Lage in meinem Tagebuch... Danke, Nathan!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Du kannst mir später danken. Nun zu den Details. Die Insel Khael Roa ist ein Ring aus Felsen mit einer Bucht im Inneren. Suche den Durchgang zwischen den Felsen - dort ist es ziemlich tief. In der Bucht solltet ihr den Anker werfen und am Strand von Bord gehen. Halte Ausschau nach einem alten Pfad, der tiefer in die Insel hineinführt - dort gibt es nur einen. Er führt dich zu einer indianischen Pyramide - das ist der Tempel, den du suchst.\nDie Insel selbst ist ruhig, aber im Tempel wimmelt es von Abscheulichkeiten aller Art. Der Eingang befindet sich an der Spitze der Pyramide. Im Inneren gibt es drei Gänge; du solltet den mittleren nehmen. Dann gehst du den Korridor hinunter und findet eine Plattform mit vier Eingängen oder Ausgängen. Hier wurde ich zum ersten Mal von den Tempelwesen angegriffen, du solltest also vorsichtig sein.\nDann kommt ein Labyrinth. Es ist sehr komplex, und ich kann mich beim besten Willen nicht mehr an den richtigen Weg erinnern. In dem Labyrinth gibt es eine Vielzahl von üblen Kreaturen. Du musst sie alle töten und dann zu einer Halle mit zwei Eingängen, sechs Säulen und einer Plattform mit neun Steinplatten gehen. Dies ist die Vorhalle des Heiligtums. Die Steinwand ist verschlossen, und ich habe keine Ahnung, wie du sie öffnen kannst. Es gibt eine Art Mechanismus, aber ich schwöre bei Gott, ich habe keine Ahnung, wie er funktioniert! Ich habe ein Idol als Schlüssel benutzt. Ich steckte ihn in die zentrale Platte, und die Tür öffnete sich. Aber du hast kein solches Idol, also musst du herausfinden, wie dieser Mechanismus funktioniert.";
			link.l1 = "In Ordnung, ich werde mein Bestes geben, um es herauszufinden. Was ist mit dem Heiligtum?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Das Heiligtum ist eine riesige Halle mit einer sehr hohen Decke und großen Steintreppen. Du kannst sie nicht benutzen - sie sind zu alt und zum größten Teil zerfallen. Aber die Erbauer des Tempels, so scheint es, waren auch große Zauberer. Es gibt Portale, wie die von Kukulcan, und sie werden dich von einem Ort zum anderen bringen.\nDu wirst sie leicht erkennen - sie sehen aus wie farbige Wirbel. Es wird zwei Portale im ersten Stock geben, aber eines davon ist eine Falle, also sei vorsichtig! Das richtige Portal bringt dich in den zweiten Stock. Dort musst du ein weiteres Portal finden, um noch höher zu gelangen, und dann direkt ins Herz des Tempels!\nDort, bei der großen Vogelstatue, wurde dieses magische Artefakt platziert, das ich und Dannie mit uns genommen hatten. Und ich habe dir bereits erzählt, was danach passiert ist.";
			link.l1 = "Ich werde mir merken, was du mir gerade erzählt hast. Danke, Nathaniel. Du hast mir sehr geholfen.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Pass auf, "+pchar.name+". Das Labyrinth und die Hallen des Tempels sind voller Gefahren. Nur ein falscher Schritt und du wirst sicher für immer dort bleiben.";
			link.l1 = "Vorwarnung ist Vorbeugung, Freund. Ich wurde gewarnt, das bedeutet, ich bin gewappnet. Ich muss jetzt gehen. Wir sehen uns!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Viel Glück, "+pchar.name+"!";
			link.l1 = "Danke!";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NatanStory");
			DeleteAttribute(pchar, "questTemp.Caleuche.NatanInfo");
			AddQuestRecord("Caleuche", "35");
			NextDiag.CurrentNode = "marun_town_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
