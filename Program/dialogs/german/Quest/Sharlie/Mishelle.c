// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Willkommen, Charles der Reisende! Ich habe alles darüber gehört, wie du diese Piraten an der Ostküste von Martinique besiegt hast. Jetzt bin ich absolut sicher, dass ich mich nicht in dir getäuscht habe, Bruder.";
				link.l1 = "Söhne von Hündinnen haben mich in eine Falle gelockt. Aber sie haben uns unterschätzt. Mein Navigator, meine Mannschaft und ich sind als Sieger hervorgegangen. Obwohl ich zugeben muss, lieber Bruder, am Anfang... sah es düster aus.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Grüße, Bruder! Ich schätze deinen aufrichtigen Eifer, mich hier rauszuholen, aber du bist noch nicht bereit für den nächsten Schritt. Mein Plan erfordert einen erfahrenen Kapitän. Erkunde weiterhin die Karibik, verdiene Preise und lerne! Wenn du bereit bist, werden wir fortfahren.";
						link.l1 = "Nun, was auch immer du sagst, Bruder. Du sitzt hier drin, nicht ich.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Schön dich zu sehen, Bruder. Vergiss deine Verpflichtungen gegenüber anderen nicht. Sobald du frei bist, werde ich auf dich warten - ich habe Ideen für unseren nächsten Schritt!";
						link.l1 = "Habe es verstanden, Bruder. Ich werde Zeit für meine Verpflichtungen brauchen, aber ich komme bald zurück!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Charles der Navigator! Habe von deinen Abenteuern gehört! Du bist fast bereit für die nächste Phase meines Plans. Komm zurück, sobald du etwas mehr Erfahrung gesammelt hast.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Grüße, Bruder! Ich schätze dein aufrichtiges Bestreben, mich hier rauszuholen, aber du bist noch nicht bereit für den nächsten Schritt. Mein Plan erfordert einen erfahrenen Kapitän. Erkunde weiterhin die Karibik, verdiene Preise und lerne! Wenn du bereit bist, gehen wir weiter.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Gut dich zu sehen, Bruder! Habe gehört, du machst Fortschritte! Aber du bist noch nicht bereit für den nächsten Schritt meines Plans. Mach weiter so und komm zurück, wenn du bereit bist.";
						}
					}
					link.l1 = "Nun, was auch immer du sagst, Bruder. Du sitzt hier drin, nicht ich.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Ich denke nicht so, Bruder. Vielleicht hast du dich bereits in diesem Käfig niedergelassen, aber ich beabsichtige nicht, hier lange zu bleiben - unser Vater kann nicht ewig warten. Spuck es aus.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Guten Nachmittag, Charles. Dein Anblick erfreut mein Herz: Du veränderst dich definitiv in einer guten Weise.";
					link.l1 = "Ist das so? Und wie kommst du darauf?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Ich verstehe. Ich sehe, dass du Neuigkeiten für mich hast, Charles! Nun, was gibt's Neues? Hoffentlich nichts Schlimmes?";
				link.l1 = "Ich habe dem Rat gefolgt, den du mir das letzte Mal gegeben hast...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Endlich bist du hier... Was gibt's Neues, lieber Bruder?";
				link.l1 = "Ich habe dem Rat gefolgt, den du mir das letzte Mal gegeben hast...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Freut mich, dich zu sehen, Charles! Hast du Chevalier de Poincy gesehen? Wie ist das Treffen gelaufen?";
				link.l1 = "Ja, lieber Bruder. Wir haben uns getroffen. Und ich habe zwei Nachrichten für dich, gute und schlechte. Ich fange mit der guten an. Ich habe deine Schulden bei de Poincy beglichen. Die schlechte Nachricht ist, dass er dich nicht freilassen wird, bis ich dein Versprechen erfülle, die Dinge mit irgendeinem Ketzer zu klären...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Wie hast du es in La Vega gemacht, Bruder?";
				link.l1 = "Nichts zum Angeben, wirklich. Tyrex ist eine farbenfrohe Persönlichkeit, aber seine Geschäftspraktiken sind einfach nichts für mich.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Wie ist es dir in La Vega ergangen, Bruder? Ich habe Gerüchte gehört und um ganz ehrlich zu sein, bin ich nicht glücklich darüber... Charlie Prince.";
				link.l1 = "Ich glaube, ich weiß, worum es in diesen Gerüchten ging. Aber das liegt alles in der Vergangenheit. Ich arbeite nicht mehr mit Tyrex zusammen, dieser Job ist einfach zu schmutzig für meinen Geschmack.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Nun, Grüße... Freibeuter Charlie Prinz. Sag mir, Charles, wie konntest du so tief sinken? Ich kann es nicht glauben. Mein Bruder, der ein zartfühlendes Gesicht machte, als ich einmal das Plündern eines spanischen Handelsschiffes erwähnte, ist nun einer der meistgesuchten und gefährlichsten Piraten in dieser Region! Sogar ich, tief in der Scheiße sitzend, werde rot, jedes Mal wenn dein berüchtigter Name meine Ohren erreicht. Ich habe den Tag verflucht, an dem ich dich nach La Vega geschickt habe. Was für eine Schande! Ein französischer Edelmann hat sich den Piraten angeschlossen und ist in so kurzer Zeit der Schlimmste von allen geworden! Was nun, Bruder? Suchst du eine freie Stelle als Piratenbaron?";
				link.l1 = "Nein. Ich bin ein für alle Mal mit der Piraterie fertig.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Was sonst, Charles? Ich glaube, wir haben alles besprochen. Zeit ist Geld, lieber Bruder - mach schnell!";
			link.l1 = "Ja, ja, ich gehe schon...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Es freut mich, dich zu sehen, Bruder! Ich verstehe natürlich, dass es dir schwer fallen wird, es zu glauben, aber ich bin verdammt froh, dass du hier bist...";
			link.l1 = "Ha! Schau ihn dir an! Er ist glücklich! Also während du auf deinem hohen Ross mit deiner 'Ordnung' warst, war Charles die Schande der Familie, ein armseliger Künstler, lebte vom Geld der Kurtisanen und war ein Hof-'Ritter', hm? Aber jetzt, da du von deinen eigenen Kameraden hinter Gittern geklatscht bist, bist du 'höllisch glücklich', deinen nichtsnutzigen Bruder zu sehen!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, du...";
			link.l1 = "Ich bin noch nicht fertig! Warum hast du Frankreich nichts von dir berichtet?! Wurde dir das Recht auf Korrespondenz entzogen?! Unser Vater wurde vor Sorge um dich völlig krank! Und er bat mich, wenigstens etwas über dein Schicksal herauszufinden!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, in welchen Worten würde ich dem Vater erzählen, was mir passiert ist? Was würde ich ihm schreiben? Nein, Bruder, egal wie hart es ist, es ist besser, wenn unser Vater noch nichts weiß. Und es wäre nutzlos, an dich zu schreiben - du bist immer an verschiedenen Adressen in Paris... Wie hast du mich gefunden?..";
			link.l1 = "Auf Bitten meines Vaters ging ich nach Malta. Dort erhielt ich einige Informationen von Ihrem Freund, dem Chevalier de La Brignais. Er schrieb mir von Ihren Problemen und dass Sie wahrscheinlich irgendwo auf Martinique sind. Dann kehrte ich nach Frankreich zurück und besuchte den Vater. Und nach all dem ging ich in dieses Höllenloch in der sengenden Hitze, wo die Mücken einen buchstäblich tot kauen...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Hast du dem Vater von alldem erzählt?";
			link.l1 = "Nein. Und der Chevalier de La Brignais hat seine Briefe nicht beantwortet, aus Angst vor den traurigen Konsequenzen... Der Vater weiß immer noch nichts über dein Schicksal. Ich beschloss, dich zu finden und der Sache auf den Grund zu gehen. Nur damit du es weißt, ich kam nicht wegen dir nach Martinique, sondern wegen unserem armen Vater!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Wirklich? Charles, seit wann kümmerst du dich um deine Familie? Seien wir ehrlich, Bruder, jeder in Paris weiß, wer dein Vater ist. Du trägst vielleicht den Familiennamen de Maure, aber du willst nicht, dass der Name de Monper entehrt wird.\nDenn in diesem Fall könntest du deine Abstammung nicht mehr dazu benutzen, allen fiktive Geschichten von deinen heldenhaften Taten zu erzählen, nicht wahr? Die Türen der besten Häuser in Paris würden für dich geschlossen sein und sie würden dich nicht näher als eine Meile an den Louvre heranlassen.\nGlaubst du wirklich, dass deine Kurtisanen und Mätressen, deren Ehemänner du zum Hahnrei machst, während sie auf dem Schlachtfeld für unser Vaterland kämpfen, sich freuen würden, ihre Herren und Meister mit einem Bruder eines Staatsverbrechers wie mir zu betrügen? .\nIch vermute, du bist direkt vom Bett irgendeines verheirateten Mädchens hierher gekommen, oder? Charles, was ist los mit deinem Gesicht? Habe ich einen Nerv getroffen?";
			link.l1 = "Du... Du!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "In Ordnung, Bruder. Wir haben genug gestichelt. Ich gebe zu, dass ich nicht perfekt bin. Aber du bist auch kein Engel. Charles, dies ist wirklich nicht die Zeit zum Streiten. Wir haben beide das gleiche Ziel, die Ehre und Würde der Familie Monper zu retten ... egal, was unsere Motive sind. Bruder, lass uns zum ersten Mal in unserem Leben Feindseligkeit durch Frieden ersetzen. Abgemacht?";
			link.l1 = "Lass es uns versuchen... Aber kannst du mir erklären, wofür du angeklagt wirst?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Offiziell klingt es, als ginge es um die Ausgaben des Vereins. In Wirklichkeit ist es viel tiefer.";
			link.l1 = "Also, du hast das Geld deiner Organisation veruntreut? Nun, nun...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Ich habe dir gesagt, dass dies die offiziellen Anklagen waren. Ich habe nicht einen einzigen Louis d'or genommen. So ist es gelaufen... du siehst, ich kann dir nicht alles im Detail erklären, solange ich hinter Gittern bin. Ich habe nicht das moralische Recht, die Geheimnisse unserer Gesellschaft zu verbreiten.";
			link.l1 = "Bitte, versuche zu erklären, lieber Bruder. Ich habe ein Recht zu wissen, denkst du nicht?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Gut. Ich hatte Geld für eine sehr gefährliche und heikle Operation erhalten, die das politische Gleichgewicht in der Karibik verändern sollte. Ich handelte auf direkte Anweisung von Philippe de Poincy, dem Generalgouverneur der französischen Kolonien. Aber trotz all meiner Bemühungen scheiterte die Operation.\nDe Poincy hatte einen Wutanfall, weil all seine hochfliegenden Pläne scheiterten. Er hatte den Befehl zu meiner Verhaftung persönlich unterzeichnet und darauf geachtet, dass er ausgeführt wurde. Dann kam er hierher und erklärte, dass er mich des Veruntreuung und Hochverrats gegen den Orden anklagen würde, wenn meine Verwandten oder ich das für die Operation ausgegebene Geld nicht zurückzahlen würden.";
			link.l1 = "Hier ist eine feine Begrüßung. Wo ist es, dieses Geld, das soweit ich verstehe, unsere Familie für deine Dummheiten zahlen muss?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Es wurde für die Vorbereitung der Operation ausgegeben. Bestechungsgelder, Organisation von Expeditionen, Kauf aller Arten von Waren und Ausrüstung. Ich hatte ziemlich hohe Ausgaben. Wie ich schon sagte - Ich habe keinen Cent genommen.";
			link.l1 = "Und welche Summe wird gefordert?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Eine Million.";
			link.l1 = "Scheiße! Du machst Witze, oder?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Sehe ich aus, als ob ich zum Scherzen aufgelegt wäre? Nein, lieber Bruder, das ist die bittere Wahrheit. Wir müssen de Poincy eine Million Pesos liefern.";
			link.l1 = "Aber verdammt noch mal! Unsere Familie hat bei weitem nicht so viel Geld! Wir könnten nicht einmal in zwanzig Jahren so viel zusammenkratzen!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Wenn ich nicht hinter Gittern wäre und meine Verpflichtungen gegenüber der Gesellschaft beschränkt wären, würde ich es in sechs Monaten bis zu einem Jahr schaffen, höchstens anderthalb Jahre. Charles, das ist die Neue Welt. Alles ist hier anders. Ein motivierter, ehrgeiziger Mann kann hier ohne sein ganzes Leben dafür zu widmen, wie in Europa, ein Vermögen für sich selbst machen.";
			link.l1 = "Eine Million in einem halben Jahr?! Bist du verrückt? Wenn du so sicher bist, warum erzählst du dann nicht deinem de Poincy davon? Lass ihn dich freilassen. Leg dich ins Zeug...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Ach, red keinen Unsinn, Charles! Es gibt keine Möglichkeit, dass Poincy mich aus dieser Zelle lässt. Wenn es so einfach wäre, würde ich nicht um deine Hilfe bitten.";
			link.l1 = "Also bin ich derjenige, der das Geld für deine Freiheit auftreiben muss?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Nicht nur meine Freiheit. Oder hast du es vergessen? Sollen wir zu unserem Gespräch über Paläste, Bälle und Sex mit adeligen Huren zurückkehren? Ja, Charles, du bist derjenige, der es tun muss. Wenn du natürlich weiterhin dein ausschweifendes Leben in Paris fortsetzen möchtest wie zuvor. Das würdest du gerne tun, nicht wahr, Bruder?";
			link.l1 = "Aber verdammt noch mal, wo zum Teufel soll ich es herkriegen?! Kennen Sie hier in der Nähe einen alten Wald, in dem Louis d'Ors statt Blättern wachsen?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Die ganze Neue Welt stellt einen Hain von Geldbäumen dar, und doch sind die Menschen zu faul, ihre dummen Köpfe zu heben und ihre Hände zu den Ästen auszustrecken. Mach dir keine Sorgen, Charles, du wirst es gut machen. Ich kenne dich seit unserer Kindheit und ich würde nie meine Zeit verschwenden, unseren Vater zu überreden, dich hierher zu schicken, wenn ich dachte, du wärst dumm oder faul.\nTrotz deiner zuvor genannten Schwächen bist du mutig, ehrgeizig, klug, deine Zunge ist gut genug gehängt und du weißt, wie man einen Degen handhabt, was eine äußerst wichtige Fähigkeit ist, die man hier kennen muss...";
			link.l1 = "Vielen Dank. Hat mein lieber Bruder es wirklich für würdig befunden, mir Lob zu schenken? Und ich dachte, ich wäre nichts als ein elender Künstler, ein Höfling...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Hör auf mit dem Unsinn. Haben wir eine Abmachung oder nicht?";
			link.l1 = "Entschuldigung, Bruder. Es ist mir einfach rausgerutscht. Ich bin es einfach nicht gewohnt, solche Worte von dir zu hören. Es ist wie eine Straßenhure, die über die Rettung einer Seele predigt.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Lass uns weitermachen, Bruder. Wie ich schon sagte, du hast alles, was es braucht, um hier erfolgreich zu sein. Nicht nur das, du bist nicht allein. Ich werde dir mit Ratschlägen helfen, was zu tun ist und wie man es richtig macht. Hör auf mich und wir sind in bunten Farben. Glaub mir, du wirst niemanden finden, der meine Erfahrung ersetzen kann. Bist du bereit, das lächerliche Gerede zu beenden und endlich zum Punkt zu kommen?";
			link.l1 = "Ja, es sieht so aus, als würde ich hier eine Weile bleiben... In Ordnung. Ich höre zu, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Ja, Bruder, du wirst hier eine Weile bleiben. Es ist gut, dass du das jetzt erkennen kannst. Also, wenn eine Kurtisane in Paris auf deine Rückkehr wartet, schlage ich vor, du vergisst sie. Aber fühle dich deswegen nicht schlecht, die hiesigen Mädchen haben ihren eigenen Charme.\nAllerdings mögen sie echte Männer, stark und fordernd, sogar grob. Also, wenn du vorhast, ein Kolonialmädchen zu ficken, rechne nicht mit Poesie, Diskussionen über Gemälde oder Spaziergängen im Mondschein. Sie würden das nicht gutheißen.";
			link.l1 = "In Ordnung, Bruder. Hat dich ein Windstoß der Schwatzhaftigkeit getroffen? Kommen wir zur Sache. Ich bin bereit, deinen Rat anzuhören, aber nicht deine üblen Unterstellungen.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Hervorragend. Um irgendeinen Erfolg zu haben, müssen Sie ein Schiff besitzen. Die Karibik ist ein Archipel. Sie wissen das, oder? Das Leben ist mit dem Meer verflochten. Ein Mann mit seinem eigenen Schiff hat ein endloses Horizont des Verdienstpotenzials.";
			link.l1 = "Aber ich bin kein Seemann!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Dann ist es an der Zeit, einer zu werden. Du hast sowieso keine andere Wahl. Du hast doch nicht daran gedacht, ein Hafenbüroangestellter zu werden oder dich bei der Garnison zu melden, oder? Nein? Dann wirst du ein Kapitän sein.";
			link.l1 = "Welch eine Wendung in meiner Karriere! Und wo finde ich ein Schiff für mich?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "Es wartet eine ausgezeichnete Schaluppe in unserer örtlichen Werft. Sie ist nicht groß, aber es ist ein sehr gemütliches Boot, gerade richtig, um die ersten Schritte in der Arena eines Seemanns zu machen. Diese Schaluppe wurde nur für mich gebaut. Mit Hilfe meiner Freunde habe ich eine Anzahlung von fünftausend Pesos für das Schiff geleistet. Machen Sie sich auf den Weg zum Schiffsbauer und sagen Sie ihm, dass Michel de Monper Sie geschickt hat. Er wird verstehen, wofür Sie da sind.";
			link.l1 = "Das Schiff kostet nur fünftausend? Das ist irgendwie seltsam...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Bruder, hörst du mir zu? Fünftausend sind nur für die Anzahlung. Der Preis für den Schlepper liegt bei etwa zwanzigtausend Pesos. Also musst du den Rest des Geldes selbst verdienen. Außerdem brauchst du Geld, um eine Crew und einen Navigator einzustellen.";
			link.l1 = "Großartig! Und wie werde ich es bekommen?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Keine große Überraschung dabei. Verdiene es. Wie sonst? Geld kann man hier hinter jedem Busch finden, man muss nur wissen, wo man suchen muss und keine Widrigkeiten fürchten. Laufe um die verschiedenen Einrichtungen herum. Unterhalte dich mit den Einheimischen. Du wirst sicherlich irgendeine Art von Arbeit bekommen. Aber sei vorsichtig, es gibt hier viel mehr Betrüger als ehrliche Menschen. Wenn du kein ehrlicher Mann bist, könntest du versuchen, etwas Wertvolles aus den Häusern zu stehlen.";
			link.l1 = "Aber wir sind doch Adel, oder?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Titel bedeuten hier Scheiße. Arbeite, kämpfe, stehle genau wie alle anderen. Nachdem du ein Boot gekauft hast, stelle eine Crew ein. Am Anfang wirst du das Boot selbst nicht steuern können, also brauchst du einen Navigator. Du kannst all das mit dem Besitzer der Taverne besprechen, er wird dir helfen. Und sorge dafür, dass du dich natürlich nicht verirrst. Wenn du in See stichst, setze direkt Kurs auf Guadeloupe...";
			link.l1 = "Was ist das? Eine Stadt?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "Es ist eine Insel fast zwei Tage entfernt von hier. Versuche so schnell wie möglich eine Karte des Archipels zu bekommen und lerne sie wie das 'Vaterunser', damit du nicht wie ein Trottel aussiehst, der den Unterschied zwischen einer Stadt und einer Insel nicht kennt. Du wirst viel um das Archipel herumsegeln müssen, also bereite dich rechtzeitig vor.";
			link.l1 = "Hm. Gut. Also, was mache ich auf diesem, äh... Guadeloupe?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Finde dort einen Mann namens 'Fadey'. Er hat sein eigenes Haus nicht weit vom Pier entfernt. Sag ihm, du kennst mich und bitte ihn, seine Schulden zu begleichen - er hat in einem Kartenspiel ziemlich viel an mich verloren. Das Geld, das du erhältst, wird dir helfen, auf die Beine zu kommen. Nutze es, um die Dinge ins Rollen zu bringen.";
			link.l1 = "Was meinst du mit 'Dinge in Gang bringen'?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Ich meine, nutze dieses Geld, um noch mehr Geld zu verdienen und so weiter. Zum Beispiel durch Handel. Wir werden später auf dieses Gespräch zurückkommen. Jetzt solltest du dich um das Schiff kümmern, nach Guadeloupe segeln, diesen fetten Moskowiter finden und die Schuld aus ihm herausschlagen.\nNicht wörtlich natürlich, Fadey ist ein sehr angesehener Mann auf Guadeloupe und ein Freund des örtlichen Gouverneurs selbst. Also hat es keinen Sinn, sich zu streiten. Im Gegenteil, versuche, dich mit ihm anzufreunden. Komm zurück zu mir, sobald du das Geld hast. Verstanden, Bruder?";
			link.l1 = "Habe es. Oh, warum....Was habe ich getan, um diese Strafe zu verdienen...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Sei nicht traurig, Charles. Akzeptiere es als unvermeidliches Übel, oder...als eine gute Sache. Später wirst du dem Schicksal dankbar sein, dass dein Leben diese Wendung genommen hat. Du, Bruder, hast endlich die Gelegenheit, etwas zu tun, um zu beweisen, dass du ein echter Mann bist. Du könntest sogar ein anständiger Mensch werden...";
			link.l1 = "(START TUTORIAL) Wieder dieser Mist?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(TUTORIAL ÜBERSPRINGEN) Bruder, ich habe keine Zeit dafür. Ich möchte den langweiligen Teil überspringen und sofort auf hoher See loslegen. Je schneller ich ein Schiff habe, desto früher kommst du aus diesem Dreckloch heraus. Oder würdest du lieber länger hier bleiben?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Nein, nein. Versteh das nicht falsch... Also gut Charles, verschwende keine Zeit. Du weißt, was zu tun ist. Ich warte darauf, dass du als Kapitän deines eigenen Schiffes mit Fadeys Geld aus Guadeloupe kommst. Viel Glück, Bruder. Ich zähle auf dich.";
			link.l1 = "Ich werde versuchen, dich nicht zu enttäuschen. Also gut, Michel. Bis zum nächsten Mal!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! Dieser 'langweilige Teil' könnte eines Tages dein Leben retten... Wie auch immer. Es gibt jetzt einen einfachen Weg, an Geld zu kommen.\nGehe zur örtlichen Kirche und sprich mit Abt Benoit. Er ist ein alter Freund unseres Vaters. Erzähl ihm von der Situation, falle auf die Knie und bettele, dass er dir genug Münzen leiht, um ein Schiff zu kaufen.";
			link.l1 = "(TUTORIAL ÜBERSPRINGEN) Viel besser jetzt! Auf zum Abt.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(START TUTORIAL) Willst du, dass ich damit beginne, deine Schulden auf noch höhere Levels zu bringen? Denkst du, ich bin ein Idiot, Bruder? Ich sehe, du kannst mir dabei überhaupt nicht helfen. Dann liegt also alles bei mir.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Wer hätte das gedacht! Sieht aus, als hätte ich mich nicht in dir getäuscht, Bruder. Ich freue mich auf deine Rückkehr aus Guadeloupe als Kapitän deines eigenen Schiffes mit Fadeys Geld. Gott segne deine Reise!";
			link.l1 = "Bis dann. Viel Spaß hier drin.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Versuchst du zu sagen, dass das beängstigend war? Spann dich nicht so an, Bruder. Es ist absolut in Ordnung. Ich fühlte mich bei meiner ersten Seeschlacht auch nicht gerade wie ein Held. Unsinn. In ein oder zwei Monaten werden solche Begegnungen sich wie ein alltägliches Ereignis anfühlen... Hast du schon Fadey besucht?";
			link.l1 = "Ich habe... Aber bei dieser Art von Erfolg... Warum habe ich mich überhaupt bemüht?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Warum ist das so?";
			link.l1 = "Weil er auf dem Trockenen sitzt. Er wurde kürzlich beraubt und hat seine eigenen Geldprobleme. Er bot mir stattdessen einen Dolch aus seiner Sammlung an. Er sagte, dass er von Wert ist und dass sein Wert größer ist als der Betrag der gesamten Schuld. Also, ich habe es genommen...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? Auf den Felsen? Geldprobleme? Ha-ha-ha! Du bringst mich zum Lachen, lieber Bruder! Dieser verdammt Moskowiter hat dich sofort als Neuling erkannt und... ah dieser Mistkerl! Zeig mir das Messer, das dir der Alte für seine Schulden gegeben hat.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Hier hast du...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Ich habe es nicht bei mir. Für das bloße Auge ist es nur ein regulärer Dolch. Fadey hat mir gesagt, es wurde von einem indianischen Schamanen verzaubert und heißt die Klaue des Häuptlings.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Nun, lass uns sehen... Gott wird diesen molligen Bären richten. Solchen Schrott, Charles, könntest du in jedem örtlichen Laden kaufen. Er hat dich übers Ohr gehauen, hat deine Unerfahrenheit ausgenutzt... Hier, nimm dieses Stück Stahl zurück. Behalte es als Souvenir. Du kannst es über dein Bett in deiner Kabine hängen.";
			link.l1 = "Ficker! Ach, wen kümmert's... Ich gehe zurück, um ihn in Guadeloupe zu sehen und diesem fettigen Brandstifter einen Schüttler zu geben!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Verzaubert von einem Schamanen? Häuptlingsklaue? Ja... alles klar. Gott wird diesen molligen Bären richten. Solchen Schrott, Charles, könntest du in jedem örtlichen Geschäft kaufen. Er hat dich über's Ohr gehauen, hat deine mangelnde Erfahrung ausgenutzt... Er versuchte mir irgendwelche Märchen zu erzählen und ich habe ihn gleich wieder zurechtgewiesen. Also kannst du diese Klaue in deiner Kabine über deinem Bett als Souvenir aufhängen...Wenn du sie noch nicht in den Müll geworfen hast.";
			link.l1 = "Schwein! Ach, wen kümmert's... Ich werde zurück nach Guadeloupe gehen und diesem fettigen Schuft einen Schüttler geben!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Beruhige dich, lieber Bruder, entspann dich. Es besteht keine Notwendigkeit dazu, es sei denn, du möchtest ein paar Monate in einer Zelle des Basse-Terre Gefängnisses verbringen. Hast du vergessen, was ich dir gesagt habe? Dieser pralle Bär ist ein Freund von Claude Francois de Lyon, dem Gouverneur von Guadeloupe. Sobald ich diesen Ort verlasse, werde ich ein Gespräch mit ihm führen... von Herz zu Herz. Er geht nirgendwo hin.";
			link.l1 = "In Ordnung. Du solltest besser mit ihm umgehen... Sieht so aus, als würde ich ohne die versprochenen Startgelder bleiben?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Sieht so aus, Charles. Aber Kopf hoch. Wer ein Schiff und einen Kopf auf den Schultern hat, kann in der Karibik nichts falsch machen. Und du hast beides, oder?";
			link.l1 = "Was insinuieren Sie? Ich habe mit diesem Dolch Mist gebaut, also was soll ich...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Beruhige dich, lieber Bruder! Warum bist du plötzlich so nervös? Bleib ruhig, du wirst länger leben. Ich unterstelle nichts. Ich hatte diese Gedanken nicht einmal!";
			link.l1 = "Es tut mir leid, Michel. Es ist nur so, dass ich ein bisschen... nun, versuche auch mich zu verstehen!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Ich verstehe. Und ich möchte dir wirklich helfen! Also hör gut zu. Du musst etwas Erfahrung sammeln und zumindest ein wenig Geld sparen, bevor du dich ernsteren Angelegenheiten widmest. Sich ohne die nötige Vorbereitung in Abenteuer zu stürzen, ist reiner Selbstmord. Ich möchte nicht, dass du von diesem Ort gleich zermalmt wirst.";
			link.l1 = "Sehr inspirierend. Von welchen Abenteuern redest du, Michel? Aus irgendeinem Grund habe ich den Faden deines Geschwafels verloren.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Bruder, lass mich dich daran erinnern, dass ich, oder genauer gesagt, wir, de Poincy eine Million Pesos schulden. Glaubst du wirklich, dass du sie ehrlich verdienen kannst? Sicher, du könntest so viel handeln, es ist möglich, wenn dir das Glück hold ist, aber der Handel in der Karibik ist auch keine friedliche Tätigkeit.\nAbenteuer werden dich von selbst finden, auch wenn du nicht daran teilnehmen willst, die Sache ist - wirst du bereit sein, wenn der Moment kommt? Es ist besser, zuerst zuzuschlagen. Si vis pacem, para bellum, Charles...";
			link.l1 = "Nochmal mit den vornehmen Worten? Sprich Französisch, ich bitte dich ...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Es ist Latein, lieber Bruder. Ich sagte, 'Wenn du Frieden willst, bereite dich auf den Krieg vor'. Nimm diesen Satz als Führungsmentalität zur Tat. Du kannst ihn in dein Logbuch schreiben und ihn jeden Morgen nach dem Gebet erneut lesen. Es gibt viel, was du lernen musst und noch viel zu begreifen...";
			link.l1 = "Gut, das reicht. Ich habe genug von deinen wissenschaftlichen Abhandlungen. Kommen wir zur Sache.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "Ich bin präzise, du folgst nur noch nicht. Gut. Zuerst musst du dich mit dem Archipel vertraut machen und dich an dein neues Leben als Kapitän eines Schiffes gewöhnen. Du wirst hart arbeiten müssen, um dein Wohlergehen und den Lohn für deine Mannschaft zu sichern. Es gibt viele Möglichkeiten, Geld zu verdienen.\nFrachten und Passagiere an Bord zu nehmen ist das einfachste. Händler in Geschäften können dir Frachtverträge geben und Passagiere werden dich selbst auf der Straße ansprechen. Du solltest auch in Betracht ziehen, die Hafenämter zu überprüfen, ein Logger oder jedes schnelle Schiff wird dir erlauben, gutes Geld mit einem Kurierjob zu verdienen.\nHafenmeister werden dir sehr profitable Frachtverträge anbieten, sobald du dir ein größeres Schiff besorgt hast. Rede mit Leuten, prahle nicht mit deinem Stammbaum, sei freundlich und die Dinge werden gut laufen. Besuche Kolonialgouverneure, sie bieten oft gut bezahlte Arbeit an.\nDu könntest versuchen zu handeln, aber in diesem Fall solltest du einen anständigen Zahlmeister einstellen. Sei vorsichtig auf See, vermeide spanische Militäreskorten und Kriegsschiffe. Wenn du auf einen einzelnen spanischen Händler oder einen ungeschützten Konvoi triffst - du könntest versuchen, sie zu kapern.";
			link.l1 = "Was?! Michel, habe ich mein Gehör verloren? Schlägst du vor, dass ich das Leben eines Piraten aufnehme? Du, der Stolz der Gesellschaft, ein Diener Gottes und der Dreifaltigkeit, schlägst mir einen solchen Lebensstil vor?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... Ich rate dir, deine Pedanterie ein für alle Mal loszuwerden, sie wird hier nicht geschätzt. Und über den Orden... sei nicht naiv, Bruder. Vielleicht herrscht in Europa zwischen dem Louvre und dem Escorial eine Art Frieden, aber hier ist Krieg. Jeder spanische Freibeuter wird nicht zögern, dein Schiff zu plündern und dich und deine Mannschaft zum Trocknen an einen Rah zu hängen.\nDaher wird dir niemand Vorwürfe machen, wenn du ein Handelsschiff einer feindlichen Nation plünderst, das versichere ich dir. Und mit einem Kaperbrief bekommst du sogar offizielle Unterstützung von den Behörden...";
			link.l1 = "Ich beginne, deine Lebensgrundsätze zu verstehen. Genau wie ich die Methoden verstehe, mit denen du anscheinend in der Lage wärst, in einem halben Jahr 'eine Million zu verdienen'.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "Und du wirst diese Methoden nutzen müssen, Charles. Schließlich wird dies von den handelnden Behörden offen oder hinter verschlossenen Türen unterstützt. Selbst wenn du beim Handel bleibst, wirst du eines Tages gezwungen sein, gegen Piraten oder spanische Plünderer zu kämpfen, denn für sie bist du die Beute.\nEs liegt in deinem besten Interesse, deine bisherigen Lebensansichten zu vergessen. Vertraue mir, Bruder, du kannst eine Menge Dinge tun, nicht nur ohne dein Gesicht zu verlieren, sondern auch die Gunst der Behörden und die Liebe des Volkes zu verdienen.";
			link.l1 = "Du hörst nie auf, mich zu überraschen, Michel. Jetzt sagst du mir, ich soll ein Pirat werden. Was kommt als nächstes?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Übertreib das nicht, Charles. Es ist wirklich einfach: Jagen oder gejagt werden. Das ist die ganze Philosophie. Ich bevorzuge das Erste und möchte, dass du meinem Beispiel folgst. Und ich sage dir nicht, dass du ein Pirat werden sollst, sondern dass du militärische Maßnahmen gegen eine feindliche Nation ergreifst und nur dann, wenn es einen guten Grund dafür gibt.";
			link.l1 = "Ein Vorteil, meinst du?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Siehst du, du verstehst, Bruder. Aber genug der Worte. Zeit, dich zu prüfen. Komm nur zu mir, wenn du dich bereit fühlst. Verdiene etwas anständiges Geld, besorge dir ein besseres Schiff, lerne den Archipel kennen und verbessere deine Fähigkeiten.\nAber sei vorsichtig, wenn du die nächsten Monate in Tavernen und Bordellen verbringst und dabei nichts Nützliches lernst... komm dann nicht einmal zurück. Sind wir uns klar, Charles?";
			link.l1 = "Mach dir keine Sorgen. Ich bin nicht zum Vergnügen hier... Was kommt danach?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Später werde ich dir sagen, was du danach tun sollst. Ich habe bereits einen Plan zusammengestellt. Du hast eine strahlende Zukunft vor dir, Charles, wenn du meinen Ratschlägen und Empfehlungen genau folgst.";
			link.l1 = "Ich würde meine bescheidene Vergangenheit gegenüber einer so hellen, großen Zukunft bevorzugen...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Vertrau mir, Bruder, du wirst über deine wertlose Vergangenheit lachen und dem Schicksal dafür danken, dass es dich davor bewahrt hat. Sei optimistisch und positiv. Du wirst dieses Leben lieben. Du wirst schon sehen.\nAch, noch etwas: Besuche unseren gemeinsamen Freund Fadey und bitte ihn, dir einen Job zu besorgen. Der Bär hat gute Verbindungen, ich bin sicher, er wird etwas für dich finden. Zögere nicht, sonst verpasst du vielleicht eine Gelegenheit. Und bitte enttäusche mich nicht.";
			link.l1 = "Moralische Lehren wieder... Herr, wann wird das alles enden? In Ordnung, Michel... Kann ich jetzt gehen?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Warte. Ein paar weitere taktische Ratschläge. Wenn du irgendeine Nation kreuzt und zum Gesetzlosen wirst, besuche die örtliche Kirche und sprich mit Abt Benoit. Sag ihm, dass ich dich geschickt habe. Er hat Verbindungen sowohl in der Papisten- als auch in der Calvinistengesellschaft und hat mir bei solchen Angelegenheiten mehr als einmal sehr geholfen. Aber sei dir bewusst, dass es weder einfach noch billig ist, also versuche, Feinde zu vermeiden.\nWarte, noch eine Sache! Wir sind Adlige, aber es ist töricht, eine Abneigung gegen das Handwerk mit unseren eigenen Händen zu haben, besonders hier. Du kannst eine Menge nützliche Gegenstände herstellen, vorausgesetzt, du hast die benötigten Werkzeuge und Komponenten... Sag mir, Bruder, wie lädst du eine deiner Pistolen?";
			link.l1 = "Hm. Wie üblich, eine Kugel und eine Prise Schießpulver.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! Ich habe nichts anderes erwartet.";
			link.l1 = "Kennst du einen anderen Weg, lieber Bruder?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Natürlich. Aber es gibt nur wenige, die es aus Unwissenheit und schlichter Faulheit tun. Mit ein paar Stunden deiner Zeit könntest du Papierhülsen aus Schießpulver und Kugeln herstellen. Ihre Verwendung halbiert die Nachladezeit der Waffe. Beeindruckt?";
			link.l1 = "Hm. Ich denke schon. Es ist interessant.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Nimm diese Bastelanleitung für Papierschalen, studiere sie in deiner Freizeit und sei nicht zu faul, dein neues Wissen anzuwenden\Warte, Bruder. Vergiss nicht, unseren lieben Gouverneur zu besuchen.";
			link.l1 = "Gibt es einen Anlass?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Es ist immer gut, Kontakt zu Gouverneuren zu halten, besonders wenn sie deine Verwandten auf ihren Inseln gefangen halten.";
			link.l1 = "Erzähl mir von ihm.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Nicht jeder kann sich auf dem Thron von Martinique halten. Die Interessen des Ordens, der Krone, der Piraten... und ein Adliger sollte seine eigenen Interessen nicht vergessen. Wenn Parquet nicht so locker und von Sünde versucht wäre, könnte er sogar Poincy dazu bringen, ihn ernst zu nehmen.";
			link.l1 = "Und welchen Nutzen könnte ich für ihn haben?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Beamte haben immer Arbeit für freie Kapitäne. Sie zahlen allerdings spärlich und nur, wenn es öffentliche Interessen betrifft, nicht persönliche. Auf jeden Fall gibt es in der Karibik keinen besseren Weg, um Ehre zu erhöhen und nationale Beziehungen zu verbessern, als für die Gouverneure zu arbeiten. Nutze den Moment, besonders da Parquet gerade einige Schwierigkeiten hat. Welche Art von Schwierigkeiten?";
			link.l1 = "Welche Art von Ärger?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Es tut mir leid, Bruder. Die Interessen des Ordens sind beteiligt. Ich werde nur sagen, dass wir nicht die einzigen sind, die schnelle Wege brauchen, um reich zu werden.";
			link.l1 = "Du bist wieder mal rätselhaft... Nun, ich schaue vorbei, wenn ich Zeit habe.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Geh jetzt. Viel Glück, Bruder!";
			link.l1 = "Danke... Bis später, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - миниквест "Делюк"
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// при достижении уровня даём флаг на квест "Голландский Гамбит"
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			//маркер на контрабандиста по квесту "Деньги на деревьях"
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - Старт квеста "Травля крысы"
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			//маркер на торговца БасТера по квесту "Бесчестный конкурент"
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "Mach es auf deine Weise. Ich glaube an dich, Bruder. Wenn ich dich jetzt ansehe, weiß ich einfach, dass du dich zum Besseren veränderst.";
			link.l1 = "Das sagst du nicht. Wie denn?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Ich kann es sehen, lieber Bruder. Ich kann deinen Gang und den Ausdruck auf deinem Gesicht sehen. Endlich ist die Maske des eingebildeten jungen Burschen, die mich buchstäblich in den Wahnsinn getrieben hat, von dir geschmolzen. Dein neues Leben hat dir offensichtlich bereits Vorteile gebracht.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Ich kann nicht verstehen, Bruder, was ich aus deinen Worten machen soll, ob es Lob oder Beleidigungen sind. Aber ich sage dir die Wahrheit: Ich bin uninteressiert daran, was du von dort drüben über mich denkst. Ich habe die Million gesammelt, die notwendig ist, um deine Schulden zu begleichen, also wirst du bald wieder frei sein. Wo kann ich de Poincy finden?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Ich kann nicht verstehen, Bruder, was ich aus deinen Worten machen soll, ob es Lob oder Beleidigungen sind. Aber ich sag dir die Wahrheit: Es interessiert mich nicht, was du von dort drüben über mich denkst. Ich habe ein Meer, nicht einen Haufen, von Angelegenheiten zu erledigen und ich habe keine Zeit, mich hier mit dir in einen Streit zu verwickeln und Worte zu spalten. Hast du etwas Relevantes zu sagen? Wenn nicht, dann bin ich auf dem Weg...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "Du hast es geschafft, eine Million zusammenzubringen? Gute Arbeit, Charles, einfach tadellos! Aber Philippe de Poincy ist leider nicht mehr in seiner Residenz, er ist auf einer geheimen Expedition zu Angelegenheiten der Gesellschaft abgereist. Also wirst du ein wenig warten müssen, bevor du ihn besuchst.";
			link.l1 = "Verflucht seien du und deine geheimen Affären! Ich dachte, ich wäre damit fertig und könnte nach Hause gehen, und jetzt...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "Und jetzt hast du die Möglichkeit, viel mehr Geld zu verdienen und nicht nur das. Bruder, die Tatsache, dass du den vom alten Fuchs geforderten Betrag angesammelt hast, ist erstaunlich, aber ich wäre nicht so zuversichtlich und so ruhig... De Poincy, ist ziemlich der schlüpfrige Aal, und er hat ziemlich viel Interesse an deiner bescheidenen Person gezeigt, und...";
			link.l1 = "Und jetzt hast du Angst, dass eine Million für ihn nicht genug sein wird?! Oder hast du das letzte Mal etwas weggelassen?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Ich habe vor nichts Angst, aber ich muss Sie warnen, dass Poincy kein einfacher Mann ist. Während er weg ist, haben Sie die Möglichkeit, sich etwas Statur aufzubauen, damit Sie mit ihm wie ein Gleichgestellter sprechen können, nicht wie ein Lord und ein Diener. Daher rufe ich Sie nachdrücklich auf, meinen Plan zu befolgen, den ich Ihnen jetzt erklären werde.";
			link.l1 = "In Ordnung. Kein Grund, über verschüttete Milch zu weinen. Ich werde in diesem Dreckloch noch etwas länger aushalten. De Poincy wird nicht ewig herumsegeln. Bring mich auf den neuesten Stand deines Plans.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! Eine lobenswerte Antwort. Ich bin froh, Charles, dass du ein Mann geworden bist. Sei jedoch nicht so streng zu deinem Bruder. Zugegeben, ich habe etwas zu erzählen. Ich habe mich schon auf unser Wiedersehen gefreut und schon einen Plan für das, was du als nächstes tun wirst, entwickelt.";
			link.l1 = "Schön. Dann klär mich auf.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Schau. Sicher, Geld spielt eine große Rolle in der Karibik, genau wie überall sonst, aber Geld kann nicht alles lösen. Ein erfolgreicher Mann muss nicht nur eine schwere Geldbörse, sondern auch umfangreiche und verschiedene Verbindungen haben, und nicht zu Taugenichtsen, sondern zu Menschen, die in dieser Welt etwas bedeuten.\nEs spielt keine Rolle, welcher Nationalität oder Stand sie sind. Verbindungen öffnen Türen, die mit Geld allein nicht geöffnet werden können. Die Kombination von 'Geld plus Verbindungen' gibt einem Mann das wertvollste Ding der Welt - Macht.\nDu solltest überlegen, solche Verbindungen zu knüpfen und das wirst du nicht schaffen, indem du Frachtjobs machst, handelst, kleinere Piraterie betreibst oder sogar bei Gouverneuren gefallen suchst.";
			link.l1 = "Was schlagen Sie vor?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "Es gibt nicht so viele mächtige Organisationen in der Karibik. Eine davon ist die Niederländische Westindien-Kompanie. Du kannst dich ihnen anschließen. Ihr Hauptsitz ist in Willemstad auf Curacao. Die Kompanie stellt oft dritte Kapitäne ein und bietet den nützlichsten von ihnen spezielle Langzeitverträge an.\nWenn du Glück hast, kannst du dort eine anständige Karriere machen. Ich habe gehört, dass sie gerade ernsthafte Probleme haben - irgendein englischer Freibeuter hat sich gegen die Kompanie erhoben und versenkt ständig ihre Schiffe. Sie können nichts gegen ihn ausrichten, er ist ein Marineoffizier, das macht ihn zu hart für sie.\nMan sagt, dass er irgendwie mit dem britischen Militärgeheimdienst verbunden ist und das sind sehr ernsthafte Leute. Also, vielleicht wird es für dich sogar noch profitabler sein, die Seite dieses Kapitäns zu wählen, aber das Problem ist - ich kenne seinen Namen nicht, ich weiß nur, dass Antigua seine Operationsbasis ist.\nDu könntest dorthin segeln und dich umhören. Ich habe auch von einer merkwürdigen Organisation gehört, die ebenfalls an diesem englisch-niederländischen Konflikt beteiligt ist, aber ich weiß nicht, auf welcher Seite sie stehen. Alles, was ich weiß, ist, dass die Spuren nach Barbados, nach Bridgetown führen...";
			link.l1 = "Also schlagen Sie vor, dass ich mich für den Dienst bei den Holländern anmelde oder nach einem zwielichtigen Kapitän oder einer noch zwielichtigeren 'Organisation' suche?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "Die Wahl liegt bei dir. Auf jeden Fall wirst du keine anderen Möglichkeiten haben, schnell mit Leuten in Kontakt zu kommen, die über das Schicksal anderer in der Karibik entscheiden und bedeutende Macht besitzen. Ich hoffe, du hast nicht den Gedanken, dass zwei oder drei Gefallen für den Gouverneur dich direkt in die königliche Marine bringen werden.";
			link.l1 = "Weißt du, lieber Bruder. Ich hatte eigentlich nicht auf eine militärische Karriere in der französischen Marine gehofft. Gott bewahre, dass ich wie du ende, in einer Gefängniszelle feststeckend für eine Aufgabe, die ich nicht bewältigen konnte... In Ordnung, ich habe verstanden. Ich denke, ich werde das Generalhauptquartier der holländischen Firma ohne große Hindernisse finden, aber ich habe keine Ahnung, wie ich nach den restlichen Parteien suchen soll";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Was den englischen Freibeuter betrifft, so können Sie in St. John's, Antigua, herumfragen. Jemand wird Ihnen definitiv Auskunft geben können. Sagen Sie, dass Sie nach Arbeit mit der englischen Flotte suchen. Was 'die dritte Kraft' betrifft, so können Sie darüber mit den Leuten in Bridgetown sprechen. Dort muss sicherlich jemand mit dieser Organisation verbunden sein.";
			link.l1 = "Wird ihre Arbeit wenigstens entschädigt? Die Gesellschaft, dieser Freibeuter... Oder wird alles nur um der 'Verbindungen' willen sein?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, du überraschst mich. Die niederländische Westindien-Kompanie operiert mit Summen, die ein König beneiden würde. Der Freibeuter, von dem ich dir erzählt habe, hat so viele niederländische Schiffe geplündert, dass er bereits vor Reichtum überquellen muss. Und die Leute von der 'Organisation' haben nicht nur viel Geld. Sie haben einen Scheißhaufen Geld.\nFür sie zu arbeiten garantiert dir immer ein süßes Stück vom Kuchen. Leute wie sie spielen immer groß. Und wenn du schlau bist, kannst du immer dein eigenes Spiel spielen und noch mehr machen.";
			link.l1 = "In Ordnung. Ich werde es mir überlegen und entscheiden, was meine beste Option ist. Haben Sie noch weitere Anweisungen?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Ja. Du solltest lernen, wie man Navigationswerkzeuge verwendet. Leider können sich viele Navigator nur mit Kompass und Sternen orientieren und können die Koordinaten nicht abschätzen. Und das ist kritisch. \nAlso. Verwende eine Boussole, um die Breitengrade abzuschätzen. Es ist ein ziemlich seltenes Werkzeug und du wirst es nicht in Geschäften finden, aber du kannst es selbst herstellen, indem du zwei gängige Gegenstände verwendest - einen Kompass und einen Astrolab. Hier, nimm die Anleitung. \nDie Abschätzung der Längengrade ist ein bisschen schwieriger. Du wirst einen geeichten Chronometer benötigen. Du kannst einen aus einem gängigen Schiffchronometer herstellen, indem du ihn mit einer Sanduhr einstellst. Das Problem ist, dass ein solches Werkzeug nur einen Monat effizient funktioniert, bevor es durch Fehler zu unzulässig wird. \nEin Chronometer erfordert immer eine Rückstellung. Sanduhren können im Büro der Niederländischen Westindien-Kompanie gekauft werden. Ich habe dort auch Chronometer gekauft. Hier, nimm diese Anleitung.";
			link.l1 = "Danke. Ich werde sofort mit dem Lernen beginnen.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Versuche, all diese Werkzeuge so schnell wie möglich zu erwerben. Alle erfahrenen und respektierten Kapitäne arbeiten mit Breitengrad und Längengrad. Du wirst als Seefahrtneuling betrachtet, bis du weißt, was diese Zahlen bedeuten.\nNun, komm zurück und prahle, sobald du Erfolg in den Angelegenheiten hast, über die wir kürzlich gesprochen haben. Gott segne dich, Charles!";
			link.l1 = "Danke, lieber Bruder. Ich denke, es wird sicherlich nützlich sein!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "Und was hast du zum Prahlen?";
			link.l1 = "Nichts für jetzt. Ich habe alle drei Organisationen gefunden und versucht, mit ihnen zu arbeiten, aber wie eine Zigarre ist alles buchstäblich in Rauch aufgegangen. Es ist, als ob das Schicksal gegen mich verschworen wäre...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Also sind die Gerüchte wahr... Lieber Bruder, das Schicksal ist nicht gegen dich verschworen. Man nennt es einen stumpfen Verstand und krumme Hände. Du hast mich enttäuscht. Geh zurück nach Frankreich, hier gibt es nichts mehr für dich zu tun.";
			link.l1 = "Aber wie...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Es ist nicht mehr deine Angelegenheit. Ich werde es selbst regeln. Ich habe andere Menschen, die fähiger sind, mein Problem zu lösen. Ich hatte Angst, dass das Vertrauen in dich mich hier bis zum Ende meiner Tage festhalten würde. Wie auch immer. Geh weg, geh zurück zu deinen Kurtisanen.";
			link.l1 = "Gut, fahr zur Hölle...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Ich habe nichts mit dir zu besprechen. Geh.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "Und? Los geht's, lieber Bruder, zieh es nicht hinaus. Was sind die guten Neuigkeiten? Einige Gerüchte haben sich zu mir durchgemurmelt von deiner eifrigen Fleißigkeit, aber ich wollte alles von dir hören.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Ausgezeichnet! Gute Arbeit, Charles! Ich habe keine Minute an dir gezweifelt! Du wirst es weit bringen, lieber Bruder... Dich so zu beschäftigen und Beziehungen zu solch wichtigen Leuten zu knüpfen, das habe ich natürlich nicht erwartet. Herzlichen Glückwunsch!";
			}
			else
			{
				dialog.text = "Sei nicht verärgert, Charles. Wenn es nicht geklappt hat, kannst du nichts dagegen tun. Wir werden andere Mittel verwenden, um die Ergebnisse zu erzielen, die wir brauchen.";
			}
			link.l1 = "Was tun wir jetzt, Michel? Ist es Zeit, Chevalier de Poincy einen Besuch abzustatten? Ich fühle mich durchaus bereit für ein Gespräch mit ihm.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Hast du es bereits geschafft, die erforderliche Summe von einer Million Pesos zusammenzustellen?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Ja, ich besitze zurzeit die erforderliche Summe.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Nein, ich habe noch nicht so viel Geld.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Ausgezeichnet! Dann werde ich nicht mehr lange in dieser Kaserne sitzen... Mach dich auf den Weg nach Capsterville, es liegt auf Saint Christopher, und bitte um eine Audienz bei de Poincy. Er sollte im Gouverneurspalast sein, wo er wohnt. Darüber hinaus, urteile einfach basierend auf der Situation und denke daran: Poincy ist schlau, sehr schlau... Ich habe ein schlechtes Gefühl, dass dieser ganze Rummel nicht so einfach ablaufen wird. Geh, Bruder, und sei vorsichtig!";
			link.l1 = "Ich werde deine Vorsichtsmaßnahmen beachten, Michel. Mach dir keine Sorgen, ich bin auch nicht gestern geboren. Jetzt gehe ich zum alten Fuchs. Bis später!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Es hat keinen Sinn, mit de Poincy zu sprechen. Er wird dich nicht einmal hereinlassen. Sammle das Geld, mein Bruder, du bist schon recht erfahren, also wird es kein großes Problem sein. Segle nach Capsterville auf Saint Christopher, sobald du es hast.\n Der Chevalier muss in seinem Gouverneurspalast sein. Bitte um eine Audienz und sie werden dich hereinlassen. Dann sieh selbst und sei vorsichtig: Poincy ist schlau, sehr schlau... Etwas sagt mir, dass diese Geschichte nicht einfach so enden wird.";
			link.l1 = "Ich werde deine Vorsichtsmaßnahmen im Auge behalten, Michel. Mach dir keine Sorgen, ich bin auch nicht von gestern. Sobald ich das Geld zusammen habe, gehe ich direkt zum alten Fuchs. Bis später!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'une pipe! Genau das habe ich befürchtet. Poincy ist dir schon lange auf den Fersen, Charles. Deshalb hat er so ein Interesse an dir gezeigt! Du hast dir in der Karibik einen ziemlichen Ruf gemacht und deshalb hat er beschlossen, dich für Aufträge einzusetzen, die in die Hose gegangen sind...";
			link.l1 = "Ich habe das Gefühl, Michel, dass du es sehr wohl wusstest und du mich einfach nicht früher informieren wolltest. Es läuft alles zu glatt... Das Geld zuerst, jetzt deine Arbeit... Das passiert nicht zufällig.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, suche nicht nach einer geheimen Nachricht, wo keine ist. Wenn du Poincy nur das Geld gleich am ersten Tag gegeben hättest, als du hier ankamst... Nun, ich meine, sagen wir mal, wenn du es hättest. Der Chevalier hätte dich um nichts anderes gebeten. Aber jetzt, da er ein Interesse an dir gezeigt hat und gesehen hat, wie leicht du dich hier eingelebt hast und was du erreichen konntest, hat er beschlossen, deine Talente auszunutzen.";
			link.l1 = "Richtig... weil deine Talente ihm nicht mehr ausreichen, richtig? Merde! Na gut. Ich sehe, ich bin hier in einer Sackgasse. Wer ist dieser Ketzer? Wie kann ich ihn finden?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Es ist nicht nötig, ihn zu suchen! Er verlässt Tortuga nie und bleibt unter dem Schutz des Bastions, das er gebaut hat, und der Horden von loyalen Hugenotten, die als Soldaten in seiner Garnison dienen. Daher ist jeder Soldat ihm treu. Poincy meinte Francois Levasseur, den Gouverneur von Tortuga.\nDie Spanier können ihn immer noch nicht von dort verjagen und de Poincy glaubte ernsthaft, dass ich das alleine ohne Unterstützung der Marine schaffen könnte, nur weil ein Bürgerkrieg aufgrund der nahen Lage der Garnison Santo Domingo ein falscher politischer Fehltritt wäre.\nDer alte Schurke ist zu besorgt um seine saubere Karriere und eine kommende Pension, um alles so zu riskieren. Dennoch ist Levasseur zu weit gegangen und stellt eine Gefahr für die Krone dar.\nDe Poincy, der Levasseur selbst in seine jetzige Position berufen hat, betrachtet diesen furchterregenden Hugenotten als persönlichen Feind und ist bestrebt, ihn durch den Malteser Chevalier de Fontenay zu ersetzen, meinen unmittelbaren Vorgesetzten, unter dessen Kommando ich hier von Malta angekommen bin.";
			link.l1 = "Herrlich! Erst eine Million machen, dann den Gouverneur von Tortuga ermorden. Was wird mein nächster Auftrag sein? Eine Verschwörung im Escorial organisieren? Scheiße! Es überrascht mich nicht, dass du das vermasselt hast. Den Gouverneur auszulöschen ist nicht wie spanische Händler zu kneifen. Ich hoffe, du hattest irgendeinen Plan, als du schworst, die Kastanien aus dem Feuer zu ziehen?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Um ganz ehrlich zu sein, hatte ich keinen Plan, da ich ohnehin den Dienst verlassen wollte und im Falle des Erfolges meines riskanten Unternehmens zu unserem Familiengut zurückkehren wollte. Persönlich ist mir de Poincys Probleme völlig egal.\nSicherlich wäre er viel flexibler geworden, sobald er das indische Gold gesehen hätte... Nun, momentan hält er alle Trümpfe gegen uns. Ich denke, ich werde hier so lange bleiben, wie Levasseur der Gouverneur von Tortuga ist.";
			link.l1 = "Und warum sollten die Malteser unter der Führung von de Fontenay, die es auf den Gouverneurssitz abgesehen haben, nicht selbst Tortuga angreifen?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Stell dir das vor. Der Orden erklärt Louis den Krieg. Sei nicht absurd! Ein solcher Skandal kommt nicht in Frage. Nur eine Privatperson kann Tortuga erobern. Ein Pirat, oder ein katholischer Abenteurer wie du.\nDanach kann er die Insel der Kontrolle des neuen Gouverneurs übergeben, den de Poincy schicken wird. Aus Sicht der großen Politiker wird eine solche Aktion großartig aussehen.";
			link.l1 = "Gibt es also einen Punkt, mit Piraten zu verhandeln?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Das Problem ist, dass Levasseur bei vielen Piraten der Bruderschaft und darüber hinaus Autorität hat. Er erlaubt ihnen, sich hinter den Batterien von Tortuga zu verstecken und das, was sie geplündert haben, frei für einen Teil der Beute zu verkaufen. \nEr teilte früher mit de Poincy, aber er teilt nicht mehr. Die Piratenschiffe werden Tortuga und seine Garnison schützen, was die Stürmung des Forts noch schwieriger macht.";
			link.l1 = "Glaubst du, diese Angelegenheit ist eine verlorene Sache?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Es gibt immer eine Lösung, kleiner Bruder. Sie ist einfach nicht immer auf der Oberfläche sichtbar. Nicht alle Piraten sympathisieren mit den Hugenotten von Tortuga. Ich kenne mindestens zwei einflussreiche Piraten, die Levasseur als Verräter und Abschaum betrachten. Ich spreche von Steven Dodson, auch bekannt als der Hai, und dem legendären Baron der Moskitobucht, Jan Svenson.\nIch weiß nicht, wo man den Hai finden kann, ich habe Gerüchte gehört, dass etwas passiert ist und er seine Basis auf Isla Tesoro verlassen musste. Aber du kannst Svenson immer in Blueweld finden. Er ist dort eine bedeutende Figur.";
			link.l1 = "Glaubst du, dass dieser... Svenson mir helfen wird?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Er wird es tun, wenn du ihm hilfst. Momentan läuft es nicht gut für ihn und der Mann könnte loyale und talentierte Leute gebrauchen. Du musst ihm zuerst deine Nützlichkeit beweisen, bevor du ein ernsthaftes Gespräch führen kannst. Du wirst einen Weg finden, dies zu tun, wenn du dort ankommst. Ich finde es schwierig, von hier aus Ratschläge zu geben.\nIch nehme an, dass du dich entschieden hast weiterzumachen, Charles, da du weiterhin Fragen stellst?";
			link.l1 = "Siehst du, Michel, ich habe gerade einen Haufen meines eigenen Silbers an de Poincy verschenkt. Ich habe es durch Blut, Schweiß und Tränen zusammengetragen! Ich bin mir nicht sicher, ob du auch nur einen einzigen Louis d'or für mich riskiert hättest, wenn ich in deiner Situation wäre.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Unterbrich mich nicht! Es wäre dumm, mit leeren Händen zum Vater zurückzukehren. Das Problem ist immer noch nicht gelöst, du bist hinter Gittern und drohst wegen Verrats an der Gesellschaft verurteilt zu werden. Poincy würde nicht zögern, den Namen Monper zu beschmutzen, wenn ich seine 'Anfrage' nicht erfülle. Es stand ihm ins Gesicht geschrieben. Also werde ich nach Blueweld gehen, um einen Weg zu finden, Svenson zu erreichen. In der Zwischenzeit denkst du darüber nach, was du sonst noch 'vergessen' hast mir zu erzählen. Zum Beispiel ist das das erste Mal, dass ich von dir von etwas indischem Gold höre, das du de Poincy bringen solltest.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Es gibt Dinge, die besser verborgen bleiben. Du hast recht, ich habe dir nicht alles erzählt, was ich weiß. Vielleicht werde ich dir eines Tages mehr erzählen, aber nicht bevor du dich mit Levasseur auseinandergesetzt hast, es wäre jetzt nutzloses Wissen.\nIch bezweifle nicht, dass deine rührende Sorge um mich nur durch den Wunsch verursacht wird, die Ehre unserer Familie zu retten. Indem du mich rettest, rettest du in erster Linie dich selbst und zweitens die Möglichkeit, die besten Häuser in Paris zu besuchen. Liege ich falsch?";
			link.l1 = "Ich fürchte, das ist nicht mehr so, Bruder. Du hattest Recht. Diese letzten Monate, die ich in der Karibik verbracht habe, haben jede Faser von mir und meine gesamte Sichtweise verändert. Und ich bin sicher, es ist zum Besseren. Ich brauche diese Pariser Salons nicht mehr wirklich und werde eines Tages ohne den Namen Monper auskommen können. De Maure ist nicht schlechter...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "Und jetzt ist das Einzige, was mich wirklich verletzt, die Tatsache, dass deine Schande einen Fleck auf unserem alten Vater hinterlassen wird. Er kennt den wahren Status quo und was hier wirklich vor sich geht nicht. Außerdem muss, wie du richtig festgestellt hast, das Erbe aus seinem unheilvollen Zustand wiederhergestellt werden. Und die Million, die für deine Freiheit bezahlt wurde, hat meine Schatzkammer erheblich entlastet, so dass sie offensichtlich wieder aufgefüllt werden muss.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Du hast alle Lektionen des Lebens hervorragend begriffen, Charles. Ich bin wirklich froh für dich. Und ich bin froh, dass du de Poincys Bitte angenommen hast, anstatt nach Frankreich zurückzusegeln. Ich hoffe, alles wird gut für dich laufen und dass du das tun kannst, was ich nicht tun konnte.";
			link.l1 = "Ich fürchte, ich habe keine Wahl. Seit meinem ersten Tag in der Karibik mache ich alles alleine. Auf Wiedersehen, Michel. Ich denke, unser nächstes Treffen wird den Befehl zu deiner Freilassung beinhalten.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Warte einen Moment! Bevor du zu Jan Svenson gehst, besuche unbedingt Marcus Tyrex - Er ist der Hüter des Kodex. Er regiert La Vega auf Hispaniola. Er hat eine grenzenlose Autorität unter den Piraten und die Spanier fürchten ihn zu Tode.";
			link.l1 = "Könnte er mir bei unserer Angelegenheit helfen?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Bezweifle es. Ich kann wirklich nicht sagen, auf welcher Seite er steht, höchstwahrscheinlich steht er nur für sich selbst. Du wirst den Hai und Svenson sowieso brauchen, aber im Moment ist Tyrex der mächtigste Pirat hier draußen. Sie haben ihn aus einem Grund zum Hüter des Kodex gewählt. Du solltest eine so wichtige Figur nicht ignorieren. Es könnte nützlich sein, die Piraten besser kennenzulernen, bevor du Svenson triffst. Du könntest sogar einen Namen unter ihnen machen...";
			link.l1 = "Und schon wieder kommen wir auf die Piratensprache zurück. Es gibt keine Möglichkeit, ihr zu entkommen, oder? Sehr gut. Ich werde ihm einen Besuch abstatten.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Ein Pirat zu sein und Geschäfte mit ihnen zu machen, ist ein völlig anderes Spiel, Bruder. Ich hoffe, du wirst den Unterschied sehen. Geh nach La Vega und frage Tyrex nach Arbeit. Wenn ihr beide nicht klarkommt - schraub ihn und komm zu mir zurück.";
			link.l1 = "Sehr gut, Michel. Bis dann!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Zumindest hast du es versucht. Du hattest die Gelegenheit, dich mit einem berüchtigten Piratenbaron 'vertraut zu machen'. Macht nichts. Geh zu Jan Svenson, er ist in Blueweld. Versuche ihn zu deinem Verbündeten zu machen, sonst wird unser Umgang mit Levasseur in einem Blutbad enden.";
			link.l1 = "Gut. Ich bin auf dem Weg.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Froh, dass du angehalten hast, Bruder. Ich habe dir einmal gesagt, dass es ein völlig anderes Spiel ist - ein Pirat zu sein und Geschäfte mit ihnen zu machen. Und du hast deinen Weg verloren. Ich hoffe, du wirst denselben Fehler mit dem Hai und Svenson nicht machen. Erledige den Job, aber halte Abstand von ihnen. Du bist schließlich ein französischer Adliger, also sei über ihnen. Jetzt geh zu Jan Svenson, er ist in Blueweld. Versuche, ihn zu deinem Verbündeten zu machen oder unser Umgang mit Levasseur wird in ein Blutvergießen münden.";
			link.l1 = "Gut. Ich bin auf dem Weg.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Ich bin sehr froh das zu hören, wenn du die Wahrheit sagst. Aber kann ich wirklich dem Wort eines Piraten vertrauen, der Städte niederbrennt, auch wenn sie spanisch sind, und Zivilisten einschließlich Frauen ermordet?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Halt.. Es tut mir wirklich leid für das, was ich während meiner Zeit mit Tyrex getan habe. Ich habe die Hölle mit meinen eigenen Augen gesehen, Bruder... Nein, es ist vorbei! Ich bin fertig mit der Piraterie und ich setze keinen Fuß mehr in La Vega. Ich werde alles tun, um meinen guten Namen wiederherzustellen.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Glaub es oder nicht. Du bist hinter Gittern, nicht ich.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Hör auf... Ich bereue wirklich die Abscheulichkeiten, die ich getan habe, während ich mit Tyrex gearbeitet habe. Ich habe die Hölle mit meinen eigenen Augen gesehen, Bruder! .. Nein, meine Piratenvergangenheit ist vorbei! Ich bin nicht mehr in La Vega. Ich werde alles tun, um meinen guten Namen wiederherzustellen.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Oh, Bruder... Erzürne Gott nicht... Ich hoffe, das passiert nicht noch einmal mit Svenson und Shark. Tu Dinge, aber halte dich fern und denke daran, was für Leute das sind. Es ist unpassend für einen französischen Adligen, wie sie zu werden. Sei höher. Jetzt geh zu Jan Swenson in Blueweld und versuche, einen Weg zu finden, den alten Korsar anzusprechen. Ohne ihn wird es nicht möglich sein, das Problem mit Levasseur mit einer kleinen Menge an Blutvergießen zu lösen.";
			link.l1 = "Gut. Ich werde nicht zögern.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Du wirst dich sehr anstrengen müssen, Bruder. Erinnerst du dich an das, was ich dir einmal gesagt habe? Dass es ein völlig anderes Spiel ist - ein Pirat zu sein und mit ihnen Geschäfte zu machen. Du... Vergiss es, ich hoffe, du wirst nicht denselben Fehler mit dem Hai und Svenson machen. Erledige die Arbeit, aber halte Abstand von ihnen. Du bist schließlich ein französischer Edelmann, also sei über ihnen. Jetzt geh zu Jan Svenson, er ist in Blueweld. Versuche, ihn zu deinem Verbündeten zu machen, oder unser Handel mit Levasseur wird in einem Blutvergießen enden.";
			link.l1 = "Gut. Ich bin auf dem Weg.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Jetzt ist nicht die richtige Zeit für Gespräche, Bruder! Der Feind ist in unserem Zufluchtsort!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Du kommst genau rechtzeitig, lieber Bruder! Ich bin so froh, dich zu sehen! Diese verfluchten Kastilier haben Saint-Pierre bereits völlig übernommen. Ich dachte, wir wären sicher erledigt! "+sTemp+"";
			link.l1 = "Wir sind noch lange nicht aus dem Schneider, die Stadt ist zwar klar, aber die Halunken sitzen zurück in der Festung und es gibt ein riesiges Geschwader, das von einem Schlachtschiff angeführt wird. Aber ich bringe dir recht erfreuliche Neuigkeiten: Michel, du bist frei!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Ich glaube meinen Ohren nicht! Kann das wirklich wahr sein? Freiheit?!";
			link.l1 = "Levasseur ist tot, Tortuga wird jetzt von deinem ehemaligen Kommandeur geleitet, und der alte Fuchs Poincy hat alle Anklagen gegen dich fallen gelassen. Von nun an bedroht nichts mehr unseren guten Namen.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Ich zweifelte bis zur letzten Minute ... Du hast mich überrascht, Charles, und dort Erfolg gehabt, wo ich ein schmerzhaftes Fiasko erlitten habe.";
			link.l1 = "Fortuna favorisiert die Mutigen, Bruder... Wie du siehst, kann ich mittlerweile auch Latein. Wo ist der Schlüssel für deine Zelle?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "Der Schlüssel zu meiner Kajüte sollte auf dem Schreibtisch des Ordonnanzoffiziers liegen. Such dort nach ihnen. Vielleicht sind sie auf den Boden gefallen und irgendwo hingerutscht...";
			link.l1 = "Ich werde sie finden und zurückkehren!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Endlich Freiheit! Oh, wie lange habe ich gewartet!";
			link.l1 = "Du kannst dir nicht vorstellen, wie lange ich auf diesen Moment gewartet habe... Michel, haben wir Leute, die kämpfen können?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Was hast du vor, Charles?";
			link.l1 = "Die Bedrohung durch die Spanier ist noch nicht verschwunden. Ich will sie aus der Festung vertreiben und dann Kräfte bündeln, um das Geschwader sowohl vom Land als auch vom Meer aus anzugreifen! Mit den Kanonen des Bollwerks werde ich in der Lage sein, mit dem Schlachtschiff zu ringen!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Wir haben Mannschaften. Eine große Anzahl von Rittern ist abgezogen, um den Gouverneurspalast zu schützen. Wir werden definitiv jemanden in der Stadt finden können... Ich werde alle Leute zusammenstellen, die ich finden kann. Wir sehen uns vor den Stadttoren!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Hier ist es, Bruder, unsere Armee. Alle Leute, die ich finden konnte. Nicht viel in Bezug auf die Zahlen, aber wir werden für unser Vaterland kämpfen! Wir werden diese verdammten Eindringlinge aus der Festung klopfen! Das Element der Überraschung wird uns helfen - sie erwarten unseren Angriff nicht. Vorwärts!";
			link.l1 = "Dulce et decorum est pro patria mori! Vorwärts!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "Es ist vollbracht, Bruder! Die Festung gehört uns!";
			link.l1 = "Es ist eine Schande, dass sie im Kampf gegen die spanische Staffel so einen Schlag einstecken musste... aber sie ist immer noch durchaus in der Lage, eine Schlacht anzuführen.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Ich werde meine Rolle spielen. Wir laden die Kanonen und versetzen dem Feind einen kräftigen Schlag! Aber erst, wenn wir deinen Geschwader näher kommen sehen, sonst wird das Kriegsschiff uns schnell in Sägemehl verwandeln.";
			link.l1 = "Holt die Leute zusammen, Michel! Ich mache mich sofort wieder auf den Weg zur Küste!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, erinnere dich: der gefährlichste Teil der Staffel ist das Kriegsschiff! Versuche zuerst, sie auszuschalten. Mit dem, was von der Batterie des Forts übrig ist, werden wir uns auch auf sie konzentrieren.";
			link.l1 = "In Ordnung, Bruder. Vielleicht sollte ich sie gefangen nehmen.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Nach den Umständen zu urteilen, bin ich nicht derjenige, der dich unterrichten sollte. Jetzt sollten wir aufhören, unsere Zeit zu verschwenden!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Herrlichkeit siegreich! Herzlichen Glückwunsch zu deinem Sieg, Bruder! Du warst großartig! Die Spanier sind völlig vernichtet!";
			link.l1 = "Ich hoffe, das bringt sie dazu, zweimal nachzudenken, bevor sie französische Kolonien angreifen.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Nun sag mir, Charles: was ist dein früheres Leben wert... verglichen mit diesem?";
			link.l1 = "Erinnere mich nicht daran...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Erinnerst du dich an das, was ich dir bei unserem ersten Treffen hier gesagt habe? 'Du wirst dieses Leben lieben', das war's! Ja, und ein riesiges Dankeschön an dich, Bruder, für deine Hilfe. Ohne dich hätte ich wahrscheinlich nie aus dem Untergrundstützpunkt entkommen können.";
			link.l1 = "Erwähne es nicht, Michel. Du bist schließlich mein Bruder und ich war verpflichtet, dir zu helfen.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Nur schau dich an, Bruder, ich bin beeindruckt: so viel Stärke in den Augen, Selbstbewusstsein in den Bewegungen, Statur in der Haltung... wo ist dieser beschissene Künstler und Hofnarr hin? Tatsächlich! Du hast meine kühnsten Erwartungen übertroffen, um ehrlich zu sein, ich hätte nie gedacht, dass du... das werden würdest.\nEs... ängstigt mich sogar ein bisschen. Denn du wirst vor nichts Halt machen, um dein Ziel zu erreichen. Du bist gut, zu gut...";
			link.l1 = "Aus irgendeinem Grund habe ich wieder Schwierigkeiten, dich zu verstehen. Bist du wieder unzufrieden mit mir?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Nein! Wovon redest du?... Überhaupt nicht! Ich habe nur meine Aufregung kanalisiert.";
			link.l1 = "In Ordnung. Also, was wirst du als nächstes tun, Bruder? Wirst du weiterhin der Gesellschaft dienen? Oder kehrst du zu unserem Erbe zurück? Ja, und ich habe fast vergessen: du hast versprochen, mir von einer Sache zu erzählen.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "Über was genau?";
			link.l1 = "Über deinen Dienst für de Poincy. Über das indianische Gold, das du ihm bringen wolltest. Über alles, was deiner Inhaftierung vorausging. Es gibt vieles, was du mir, Michel, nicht erzählt hast, was mich ziemlich blind macht. Also...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Bruder, ich erinnere mich sehr gut an das, was ich gesagt habe. Ich werde dir alles erzählen. Aber nicht mitten in einer brennenden Stadt!\nWir beide haben jetzt viel zu tun. Du musst deine Staffel regeln, sie reparieren und die Schiffe wieder bereit machen. Ich und der Gouverneur werden die Einheimischen organisieren und beruhigen.\nWir werden morgen früh bei einem Glas gutem französischem Wein alles besprechen. Vertraue mir, Bruder, ich habe einen großen Plan. Einen wirklich großen. Aber nicht jetzt. Besuche Abt Benoit morgen um neun Uhr morgens. Ich werde die Nacht bei ihm verbringen, er ist ein alter Freund von mir.";
			link.l1 = "In Ordnung, Michel. Es ist also beschlossen. Ich freue mich auf unser Gespräch morgen.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Dialog 28.";
			link.l1 = "Gut, Michel. Dann ist es beschlossen. Ich freue mich auf unser Gespräch morgen.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Keine Verabschiedungen nötig, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Also treffen wir uns wieder, "+pchar.name+". Trotz meiner Warnungen hast du weiter nach mir gesucht und deine Suchen haben dich weit, weit weggebracht...";
			link.l1 = "Michel?... Aus irgendeinem Grund bin ich nicht überrascht. Ist Miguel Dichoso für einen weiteren Schatzhaufen nach Tayasal zurückgekehrt? Hm-hm-hm. Ja, ich habe ein Treffen mit dir gesucht, lieber Bruder. Ich war einfach nur wild darauf, einen Blick in deine schamlosen Augen zu werfen. Als Sahnehäubchen war dein Mordversuch an mir in der Friedhofskrypta. Aber zuerst, sag mir, wie soll ich dich nennen? Michel de Monper oder Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Diese Namen sind nicht mehr von Bedeutung, "+pchar.name+". Es ist alles Vergangenheit, die sehr bald sogar aus der Geschichte selbst verschwinden wird. Jetzt ist der Moment der Wahrheit, auf den ich seit einem langen Vierteljahrhundert hingearbeitet habe, seit ich zum ersten Mal an Land ging...";
			link.l1 = "Was?!! Das... das kann nicht sein!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Ja, "+pchar.name+". Ich sehe an Ihrem Gesicht, dass Sie verstehen, wer ich bin, aber Sie können es nicht glauben. Ich bin derjenige, den Sie in den letzten Monaten treffen wollten. Derjenige, mit dem der Vertreter Ihres Gottes, der Inquisitor aus Santiago, Sie in die Schlacht gesegnet hat.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Ich stimme zu, "+pchar.name+", dass es schwer zu glauben ist. Das Leben ist komplizierter und überraschender als jedes Märchen...";
			link.l1 = "Ich war auf alles vorbereitet, aber... mein Bruder!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Bruder? Nur durch das Blut unseres Vaters. Wir haben verschiedene Mütter, "+pchar.name+". Wisse, dass meine Mutter eine Tochter von Kanek war, genannt Shochikezhal. Sie wurde von französischen Kaperfahrern unter dem Kommando des berühmten Nicolas Gotier entführt, nachdem sie unklugerweise Tayasal verlassen hatte. Sie hatten beschlossen, sie zu versklaven. Ein Mann namens Serge Benoit war unter ihnen. \nBeschämt über die Tat seines Kapitäns verließ er ihn, nahm den Schleier und jetzt kennst du ihn als Abt Benoit. Henri de Monper, unser Vater, war damals Marineoffizier. Er kaufte Shochikezhal und brachte sie nach Frankreich, wo sie mir das Leben schenkte. Ungefähr zur gleichen Zeit wurdest auch du geboren, "+pchar.name+". Deine Mutter starb bei der Geburt und unser Vater erklärte, dass seine rechtmäßige Frau Zwillinge zur Welt gebracht hatte.\nShochikezhal, meine Mutter, wurde zur Amme für uns beide. Du wurdest mit der Milch einer indischen Frau vom Volk der Itza gesäugt, "+pchar.name+"! Später hat deine Großmutter mütterlicherseits beschlossen, dich zur Erziehung aufzunehmen, und du hast den Namen deiner Mutter bekommen - de Maure.";
			link.l1 = "Wie hast du das alles herausgefunden?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Würdest du nicht denken, Bruder, dass ich mehr weiß als gewöhnliche Leute? Auch unser Vater hat mir viel erzählt und ich bin mir vielem bewusst... Es ist, wie man sagt, aus dem Stegreif.";
			link.l1 = "Nun ist alles klar... Und was ist mit deiner Mutter passiert? Warum habe ich sie nie gesehen?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Sie starb, um mein Leben zu retten. Etwa ein Jahr nach meiner Geburt wäre ich fast an einer Krankheit gestorben. Meine Mutter, die Tochter eines Itza-Priesters, führte eine geheime magische Mayan-Heilzeremonie für mich durch. Mir ging es besser, aber diese Zeremonie war von einigen... zerstörerischen Nebenwirkungen in Form von Donner, Blitz und einem tropischen Hurrikan begleitet. Shochikezhal wurde der Hexerei beschuldigt und auf dem Scheiterhaufen der Inquisition verbrannt...";
			link.l1 = "Und du hast dich verbessert...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Neben meiner Heilung hat mir dieses Ritual auch andere Fähigkeiten verliehen, zusätzlich zu der Öffnung einer Verbindung zur Welt der Götter. Und den Rest kennen Sie bereits. Wie Sie bereits wissen, werde ich das Licht des Wissens und der Erfahrung der weißen Rasse in die Vergangenheit tragen und es dem Volk der Maya übergeben. Die Geschichte wird umgeschrieben und ihr, Weiße, werdet diese Welt nicht beherrschen. Ich werde dafür sorgen.";
			link.l1 = "Also war dein ganzes Leben, das Studium an der besten Marineakademie, der Dienst in der Armee und im Malteserorden, im Grunde genommen nur eine Ansammlung von militärischer Erfahrung?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Genau. Als ich realisierte, dass ich genug wusste, arrangierte ich, dass ich in die Karibik beordert werde. Ich redete mich bei Chevalier de Poincy ein, eine Basis auf Martinique zu gründen. Als Nächstes musste ich nach Tayasal kommen. Es war für mich nicht gerade eine einfache Aufgabe, da dieses physische Gefäß sterblich bleibt und die Portale in der Karibik nicht korrekt funktionierten.";
			link.l1 = "Und du wurdest Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Lieber Bruder, ich habe diesen Spitznamen auf den Schlachtfeldern Europas bekommen. Dort habe ich auch Ramon de Mendoza y Riba getroffen. Du denkst, das Leben besteht aus Zufällen? Nein, keineswegs, jeder Zufall ist eine unbekannte Regelmäßigkeit. Vieles wurde getan, um meine Rückkehr nach Tayasal zu ermöglichen. Ich musste zwei Leben leben. Michel de Monper und Miguel Dichoso. Ich musste auch dafür sorgen, dass die Leute glauben, sie seien verschiedene Personen.\nIch musste piratisieren, genau wie du, im Dienst für de Poincy, um sein Vertrauen, seine Gunst und sein Geld zu gewinnen. Ich musste Blaze Sharp, einen der Anführer der Piraten, als Gefallen für Ramon de Mendoza ermorden, um Soldaten für die Expedition zu bekommen.\nIch musste sowohl de Poincy als auch de Mendoza mit Geschichten von Tayasals Schätzen verführen. Ich hatte siebenhundertfünfzigtausend Silberstücke aus de Poincys Schatzkammer erhalten und die spanische Militärfregatte an den Piraten Dodson verkauft. Und dann geschah die Expedition. Ich war nur zurückgekehrt nach Tayasal, um Misserfolge zu erleben...";
			link.l1 = "Ich verstehe... Während du nur ein fünfjähriger Junge warst, der in unserem väterlichen Erbe den Schmetterlingen nachjagte, hat Kanek der große Priester, erschreckt durch Don Alonso de Maldonados Invasion in Tayasal, die für die Zeitreise so wichtige Kukulcan-Maske sicher versteckt... entschuldige, ich meine DEINE Maske.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Ja, Kanek hatte sich damals selbst überlistet. Er führte das schwierigste Ritual durch, ein Ritual, das selbst die Alten nicht zu vollziehen wagten. Er versteckte die Maske auf der frisch geschaffenen verlassenen Insel und schaffte es, den Schlüssel zu Ksocheatem - dem sogenannten Hüter der Wahrheit - zu verlieren.\nIch musste klug vorgehen. Das Ritual verhinderte, dass ein Schiff, das geschützte Gegenstände aus Taysals Schatzkammer an Bord hatte, die Karibik verließ, indem es solche Schiffe an die Küsten von Ksocheatem warf. Ich beabsichtigte, das zu nutzen. Ich nahm genug Schätze, um Mendoza zu besänftigen. Ich nahm auch einen besonderen, durch das Ritual geschützten Gegenstand mit.\nEin Schiff mit diesem Gegenstand an Bord würde unweigerlich direkt zu Ksocheatem gebracht werden, direkt zu meiner Maske. Also ging ich aufs Meer hinaus und ließ Mendoza von mir wissen.";
			link.l1 = "Also, du hast Tayasal alleine verlassen?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "Du meinst ohne Mendozas Soldaten? Sicher. Alle Spanier wurden hier in Tayasal abgeschlachtet. Die Itzas brachten die Schätze selbst an die Küste und ich erzählte Mendoza, dass die Soldaten von den Miskito überfallen wurden. Er glaubte mir, da er nur an Gold und nicht an Menschen interessiert war.\nIch hatte geplant, das Schiff mit den Schätzen unter die Kanonen der 'Gryffondor' zu stellen, aber es lief viel besser: Der Baron beschloss, die Schätze unter meiner Aufsicht nach Spanien zu schicken. Das war das bestmögliche Ergebnis, ich musste nur warten, bis das Schiff die unsichtbare Grenze der Karibik überquerte.\nEs stellte sich jedoch heraus, dass der Kapitän andere Befehle hatte. Ich erfuhr, dass eine spezielle Entertruppe meutern sollte, sobald wir den Atlantischen Ozean erreichten, und die gesamte Besatzung und alle Offiziere töten sollte. Der Kapitän hatte den Befehl, das indische Gold danach an Mendoza zurückzugeben.\nEin feines Exemplar der weißen Rasse, nicht wahr, Bruder? Ich musste es riskieren, ich wusste nicht, wann der Aufstand stattfinden sollte. Aber alles lief nach Plan: Der Sturm traf uns, sobald die 'Santa Quiteria' die Ostseite der Insel Trinidad und Tobago erreichte. Die Fregatte wurde zurück in die Karibik nach Ksocheatem getrieben.\nDann erlitt ich das größte Versagen meines Lebens - eine Welle spülte mich vom Schiff und ich fand mich ein paar Tage später in der Bucht von Le Marin auf Martinique wieder. Fischer fanden mich und brachten mich nach Le Francois. Aber de Poincys Männer fingen mich, während ich bei Cesar Craig wieder zu Kräften kam. Die 'Gryffondor' fand die 'Santa Quiteria' nicht an dem von mir festgelegten Ort. Chevalier de Poincy wurde wütend, als er erfuhr, dass das indische Gold zusammen mit dem Geld aus der Ordenskasse und seinen eigenen Ersparnissen verschwunden war.\nEr ließ mich verhaften. Er konnte mich jedoch nicht töten, er wollte es nicht. Er wollte Gold. Gold! Das ist das einzige, was eure Leute wollen und worum sie sich kümmern! Ihr werdet alles tun, um es zu bekommen... Ich war in einer schrecklichen Lage: Ich hatte keine Maske bei mir und ich verrottete in einer Zelle ohne einen einzigen Groschen in meinen Taschen.\nDas war, als ich dich rief. Ja-ja, lieber Bruder, du solltest mich befreien, damit ich tun konnte, wozu ich geboren wurde. Und du hast hervorragende Arbeit geleistet. Es scheint, dass die Itza-Milch, die du gesogen hast, dir etwas Gutes getan hat.";
			link.l1 = "Was mich interessiert, ist, worauf du gezählt hast, als du damals aus Saint-Pierre geflohen bist? Was war dein Plan?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Du warst von Anfang an mein Plan, Bruder. Kukulcan kann die Herzen der Menschen lesen. Der Brief, den ich dir beim Abt hinterlassen habe, sollte dich zum Handeln bringen. Ich lag richtig mit dir. Ich habe deinen Fortschritt beobachtet, seit du das erste Treffen mit dem Inquisitor von Santiago hattest. Du hast alles für mich getan. Du hast den Wächter der Wahrheit erschaffen. Du hast die Konkurrenten beseitigt. Du hast Ksocheatem gefunden.\nIch war da, habe dir gefolgt. Allerdings habe ich nicht erwartet, dass du nach Tayasal kommst. Du hast alle meine Erwartungen übertroffen. Und mit deiner Hilfe werde ich tun, wozu ich geboren wurde. Der Grund, warum ich in sterblichem Fleisch geboren wurde.";
			link.l1 = "Es gibt nur einen kleinen Haken in deiner Argumentation, lieber Bruder. Du besitzt deine Maske nicht und ohne sie bist du nichts. Ich habe sie. Und ich bin nicht gerade darauf erpicht, sie dir zu geben. Ich würde sie eher in Stücke sprengen, als sie in deine Hände fallen zu lassen.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Du kannst nicht ändern, was das Schicksal vorbestimmt hat. Ich werde nicht zulassen, dass du mein Artefakt beschädigst. Ich kann es fühlen... Es ist bei dir. Und du bist hier, in meinem Tempel, in meiner vollen Macht! Du wirst diesen Ort nie verlassen. Es ist Zeit für deine letzte Prüfung, lieber Bruder, um zu sehen, was du in einem Kampf gegen Kukulcan wert bist!";
			link.l1 = "Ich nehme an, dass dein sterblicher Körper noch bluten kann!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! Mir tut's leid um dich, Charles. Das ist wirklich traurig. Aber du verdienst eine Chance, gegen einen Gott zu kämpfen. Auch wenn es sinnlos ist. Ich sag's dir später, wenn du den ersten Akt überlebst.";
			link.l1 = "Ich nehme an, dass dein sterblicher Körper noch bluten kann!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Es scheint, dass deine Kräfte dich verlassen, großer Kukulcan... Du magst stark sein, aber dein Körper ist immer noch sterblich!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Ich denke, das wird genug Unterhaltung sein. Du bist wahrlich ein Meisterschwertkämpfer und ein großer Krieger, ich würde sogar wagen zu sagen, der größte Krieger deiner Zeit, aber diese Schlacht hast du verloren, "+pchar.name+"...";
				link.l1 = "Wir sind nur...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Genug, lieber Bruder. Du kannst der Macht von Kukulcan nicht widerstehen, wenn er mit seinem Artefakt zusammen ist! Ich habe dir erlaubt, so lange am Leben zu bleiben, nur um zu sehen, was du wirklich erreichen konntest.";
			link.l1 = "Verdammt... Dieser letzte Schlag... Aber von welchem Artefakt sprichst du? Die Maske? Sie ist bei mir!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Armer, armer Kapitän "+GetFullName(pchar)+"... Du bist so weit gekommen, hast alle Gefahren überlebt, viele der stärksten Feinde getötet, nur um am Ende besiegt zu werden!.. Die Jade-Maske, die du in der Metallkiste in der Nähe der Wracks der 'Santa Quiteria' auf Ksocheatem gefunden hast, ist eine Fälschung! Es ist nur eine alte Maske aus Taysals Schatzkammer. Es ist NICHT DIE MASKE VON KUKULCAN!.\nIch hatte sie persönlich nach meiner gescheiterten Expedition hierher gebracht, sie wird durch das antike Ritual bewacht. Diese Maske war der Grund, warum der Sturm die Santa Quiteria nach Ksocheatem getragen hat. Sie hatte auch einen zweiten Zweck. Sie sollte jeden täuschen, der dort nach meinem WAHREN Artefakt kam.";
			link.l1 = "Aber... Wo war dann die echte Maske?! Ich habe ganz Ksocheatem durchsucht!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Du hast nicht, "+pchar.name+". Mein Artefakt lag auf der gegenüberliegenden Seite der Insel von der 'Santa Quiteria', in einem sicher bewachten Heiligtum. Der Weg dorthin führt durch unterirdische Höhlen. Es ist kompliziert zu finden und für das unverfeinerte Auge eines Sterblichen nicht offensichtlich. Da ist es! Schau es dir gut an, einen letzten Blick...";
			link.l1 = "Das kann nicht sein!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Du hast überlebt und viele Schlachten gewonnen, Bruder. Aber diese hast du verloren, "+pchar.name+"...";
			link.l1 = "Und was jetzt?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Ich werde direkt ins zehnte Jahrhundert reisen, sieben Jahrhunderte zurück. Das wird ausreichen, damit die Maya-Zivilisation unerschütterliche militärische und wissenschaftliche Stärke über die weiße Rasse erreicht.";
			link.l1 = "Und was wird mit unserer Welt geschehen? Wird sie verschwinden?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Nein. Es wird sich ändern. Vielleicht wird dort ein Platz für dich sein, aber du wirst dich an nichts erinnern, was in dieser Welt passiert ist. Einige von denen, die hier geboren wurden, werden dort niemals geboren werden, das Gegenteil ist auch korrekt. Die Toten werden wieder zum Leben erweckt und die Lebenden werden sterben, auf die eine oder andere Weise, jeder wird wiedergeboren. Suum cuique, jedem das Seine, "+pchar.name+".\nHab keine Angst, kleiner Bruder. Du wirst nie begreifen, was passiert ist und du wirst die neue Realität ganz natürlich annehmen. Nur ich, Kukulcan, werde die Erinnerungen behalten... Aber genug! Kanek hat bereits alles für das Ritual vorbereitet.\nDu wirst mir folgen, "+GetFullName(pchar)+", und du wirst die letzten Momente der Existenz dieser Realität bezeugen, die du so eifrig erhalten wolltest.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "Die Tore der Zeiten haben sich geöffnet! Freut euch, meine Kinder, denn ihr steht so nahe bei der Größe! Wir werden eine neue Welt erschaffen, eine Welt ohne Platz für die bleichen Eindringlinge!\nLebewohl, "+pchar.name+", und sei bereit, dein neues Schicksal zu akzeptieren, was auch immer es sein mag. Jedem das Seine!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Dieser Kampf ist noch nicht vorbei, Sterblicher. Du bist erheblich erschöpft und ich habe Verstärkungen, die kommen! Du wirst mein Artefakt aufgeben. Entweder das, oder ich nehme es von deinem toten Körper, es macht mir keinen Unterschied...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! Ich befehle dir, diesen Mann sofort zu töten!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Hast du mich nicht gehört? Ich wiederhole: Ich befehle dir und deinen Kriegern, diesen Mann zu fangen und zu töten!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Was zum Teufel? Kanek! Wiederhole meinen Befehl an deinen verdammten Sohn!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Du verrätst dein Volk, Urakan! Du bist vor solch eminenten Veränderungen eingeknickt! Krieger, ich befehle euch, nicht nur diesen Mann, der sich meinen Bruder nennt, zu fassen und zu töten, sondern auch den Verräter Urakan!";
			link.l1 = "Krieger, im Namen von Cavil und Hurakan befehle ich euch, still zu stehen, wenn ihr euer Leben schätzt! Keiner von euch wird einen Kampf gegen Cavil überleben! Lassen wir die Götter selbst entscheiden, wer von ihnen auf Erden der Stärkste ist!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Dieser Tag wird immer besser und besser. Du hast solch einen Verlauf der Ereignisse nicht erwartet, oder, Bruder? Die Götter müssen selbst entscheiden, wer von ihnen wirklich der Stärkste ist. Und jeder wird bekommen, was er verdient, Michel. Suum cuique! Jedem das Seine...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
