// диалоги НПС по квесту 'В поисках Стража Истины'
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
			dialog.text = "Wie kann ich Ihnen helfen?";
			link.l1 = "Es tut mir leid, es ist nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// пленный испанец
		case "spa_prisoner":
			PlaySound("Voice\English\Ransack_1.wav");
			dialog.text = "Was willst du? Noch ein Verhör? Geh zum Teufel!";
			link.l1 = "Herr, wie ist Ihr Name?";
			link.l1.go = "spa_prisoner_1";			
		break;
		
		case "spa_prisoner_1":
			dialog.text = "Wo zur Hölle kümmert es dich um den Namen des Mannes, den du hängen oder erschießen wirst? Bastardo! Ich war unvorsichtig genug, um doch in deine Hände zu fallen...";
			link.l1 = "Herr, nennen Sie Ihren Namen. Ich kann nicht mit einem Mann sprechen, ohne seinen Namen zu kennen.";
			link.l1.go = "spa_prisoner_2";			
		break;
		
		case "spa_prisoner_2":
			dialog.text = "Don "+GetFullName(npchar)+". Nun, bist du zufrieden? Mit wem habe ich das Vergnügen zu sprechen?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+". Hast du schon mal von mir gehört?";
			link.l1.go = "spa_prisoner_3";			
		break;
		
		case "spa_prisoner_3":
			dialog.text = "Nein, verdammt! Sieh ich so aus, als ob ich jeden herumstreunenden Vagabunden in der Westindies kenne, der...";
			link.l1 = "Genug. Lassen wir die Beleidigungen und benehmen uns wie Gentlemen. Dein Schicksal wird davon abhängen, was du mir erzählen kannst. Wenn du mir etwas Interessantes erzählst, werde ich für deine Freilassung in meine Obhut bitten. Das wird dir ermöglichen, der Musketenkugel oder Schlinge zu entkommen, die jetzt auf dich wartet.";
			link.l1.go = "spa_prisoner_4";			
		break;
		
		case "spa_prisoner_4":
			dialog.text = "Mein Gott, das ist ein Angebot, das ich nicht ablehnen kann. Was möchten Sie wissen, señor?";
			link.l1 = "Wer hat einen so großen Angriff auf St. Pierre organisiert und warum?";
			link.l1.go = "spa_prisoner_5";			
		break;
		
		case "spa_prisoner_5":
			dialog.text = "Baron Ramon de Mendosa y Riba, der Garnisonskommandant der Providence Insel. Er schickte ein Geschwader aus, um die Stadt zu überfallen und zu plündern, und alle Wertsachen zu beschlagnahmen, die wir finden könnten.";
			link.l1 = "Was war Ihre unmittelbare Aufgabe im Angriff? Speziell, was waren Ihre Befehle?";
			link.l1.go = "spa_prisoner_6";			
		break;
		
		case "spa_prisoner_6":
			dialog.text = "Ich bin der Kommandant des Marinebataillons. Unsere Befehle waren, das Fort zu besetzen und seine Batterien zu sichern, damit sie nicht auf unsere Landungsboote schießen, während sie sich der Stadt näherten. Danach nahmen meine Männer am Angriff auf St. Pierre selbst teil.";
			link.l1 = "Wurden Sie über die Wertsachen in der Stadt informiert? Über die Menge und Qualität?";
			link.l1.go = "spa_prisoner_7";			
		break;
		
		case "spa_prisoner_7":
			dialog.text = "Wir hatten keine genauen Informationen über die Menge, aber Baron de Mendosa y Riba erzählte uns, dass unter der Festung Silber gelagert wird und die Hafenlager strategische Rohstoffe enthalten, die für die Kriegsanstrengungen unerlässlich sind: Eisenholz und Schiffsseide.";
			link.l1 = "Hast du diese Wertsachen gefunden?";
			link.l1.go = "spa_prisoner_8";			
		break;
		
		case "spa_prisoner_8":
			dialog.text = "Nein. Wir haben keines von beiden gefunden. Die Lagerhäuser waren mit typischen Kolonialwaren gefüllt und unter der Festung befanden sich Schießpulver, Waffen und Blei. Aber wir hatten nicht genug Zeit, um eine gründlichere Suche durchzuführen... die französischen Verstärkungen kamen brüllend herein und wir waren gezwungen, die Schlacht zu liefern.";
			link.l1 = "Haben Sie es nicht seltsam gefunden, dass Sie die Wertsachen nicht gefunden haben?";
			link.l1.go = "spa_prisoner_9";			
		break;
		
		case "spa_prisoner_9":
			dialog.text = "Natürlich habe ich das getan, aber ich hinterfrage normalerweise keine Befehle.";
			link.l1 = "Hören Sie gut zu, was ich Ihnen jetzt sage. Fort St. Pierre hat noch nie Silber beherbergt, und in diesen Lagern wurde noch nie Eisenholz und Seide gelagert. Denken Sie gut nach, Senor, bevor Sie antworten, denn wenn Ihre Antwort mir nicht gefällt, drehe ich mich um und gehe aus hier raus und überlasse Sie Ihrem Schicksal... einem traurigen Schicksal.";
			link.l1.go = "spa_prisoner_10";			
		break;
		
		case "spa_prisoner_10":
			dialog.text = "Ich höre zu.";
			link.l1 = "Ich glaube nicht, dass das einzige Ziel deines Überfalls einfacher Raub war. St.Pierre ist eine bescheidene und relativ arme Kolonie, um hier ein ganzes Geschwader unter der Führung eines erstklassigen Linienschiffs zu schicken. Sicherlich hattest du oder dein Kommandant oder jemand anderes zusätzliche Befehle oder Anweisungen. Was haben sie dir gesagt? Denke gut nach, bevor du antwortest...";
			link.l1.go = "spa_prisoner_11";			
		break;
		
		case "spa_prisoner_11":
			dialog.text = "";
			link.l1 = "Du wirst still bleiben? Gut. Denk einen Moment nach, ich werde warten.";
			link.l1.go = "spa_prisoner_12";			
		break;
		
		case "spa_prisoner_12":
			dialog.text = "Herr, wird mein Leben von meiner Antwort abhängen?";
			link.l1 = "Richtig.";
			link.l1.go = "spa_prisoner_13";			
		break;
		
		case "spa_prisoner_13":
			dialog.text = "Ich habe etwas... Aber du musst mir schwören, dass du mich hier rausholst und mich nach Spanien zurück auslösen wirst.";
			link.l1 = "Wenn du mir etwas sagst, das meiner Aufmerksamkeit würdig ist, schwöre ich beim Heiligen Kreuz, dass du an Bord meines Schiffes für Lösegeld gebracht wirst und der Hinrichtung entkommst.";
			link.l1.go = "spa_prisoner_14";			
		break;
		
		case "spa_prisoner_14":
			dialog.text = "In Ordnung. Don Diego de Montoya hat unser Bataillon von Marines angewiesen, dass wir unter aller Geheimhaltung und Wichtigkeit einen Mann namens Miguel Dichoso finden und gefangen nehmen müssen, der sich irgendwo in St. Pierre unter dem Schutz der Behörden befindet.";
			link.l1 = "Mach weiter. Wer ist Diego de Montoya?";
			link.l1.go = "spa_prisoner_15";			
		break;
		
		case "spa_prisoner_15":
			dialog.text = "Der Offizier, der das Geschwader kommandiert. Er floh kurz nach deiner... dramatischen Ankunft.";
			link.l1 = "Wer ist er, dieser Don Diego?";
			link.l1.go = "spa_prisoner_16";			
		break;
		
		case "spa_prisoner_16":
			dialog.text = "Ich weiß nur, dass er ein bevollmächtigter Vertreter von Baron de Mendosa y Riba ist, seine rechte Hand und Agent für kritische Aufgaben.";
			link.l1 = "Interessant... Und wer ist Miguel Dichoso, der Mann, für den anscheinend diese ganze Katastrophe arrangiert wurde? Muss ein übler Kerl sein, hm?";
			link.l1.go = "spa_prisoner_17";			
		break;
		
		case "spa_prisoner_17":
			dialog.text = "Erinnern Sie sich an Ihren Eid, Senor?";
			link.l1 = "Ja. Und ich bekräftige, dass Sie, wenn Sie Ihre Geschichte weiter erzählen, als Schlüsselzeuge zu meinem Schiff gebracht werden und später... nun, ich werde einen Weg finden, Sie zu einer spanischen Siedlung zu bringen. Aber nicht bevor Sie mir alles erzählt haben, was Sie wissen.";
			link.l1.go = "spa_prisoner_18";			
		break;
		
		case "spa_prisoner_18":
			dialog.text = "Miguel Dichoso ist der ehemalige Waffenbruder des Barons, jedoch sagen einige, dass Miguel ihn verraten hat. Senor de Mendosa y Riba will ihn lebend, daher haben wir den Befehl erhalten, Dichoso unter keinen Umständen zu töten.";
			link.l1 = "Ist Dichoso auch ein Spanier?";
			link.l1.go = "spa_prisoner_19";			
		break;
		
		case "spa_prisoner_19":
			dialog.text = "Ja. Don Diego de Montoya gab uns eine ungefähre Beschreibung und befahl, dass jeder Mann, der wie Dichoso aussieht, direkt zu ihm gebracht werden musste. Aber angesichts der kurzen Zeit, die wir vor Ihrem Gegenangriff hatten, hatten wir nie die Zeit zu suchen.";
			link.l1 = "Kannten Sie Dichoso persönlich?";
			link.l1.go = "spa_prisoner_20";			
		break;
		
		case "spa_prisoner_20":
			dialog.text = "Nein, nur vom Hörensagen. Ich habe den Mann vorher nie gesehen. Einige meiner Kameraden kannten ihn persönlich. Sie sind alle tot.";
			link.l1 = "Wie schlimm hat Dichoso Ihren Don Mendosa verraten, dass er sich entschieden hat, ein ganzes Geschwader hinter ihm her zu schicken?";
			link.l1.go = "spa_prisoner_21";			
		break;
		
		case "spa_prisoner_21":
			dialog.text = "Ich werde es dir erzählen. Der Baron kam erst kürzlich aus Spanien in die Karibik. Sein Auftrag war es, die Sicherheit der spanischen Schatzflottenkonvois zu gewährleisten, aber stattdessen schaute er ins Landesinnere... auf der Suche nach indischem Gold. Gerüchte von versteckten Schätzen ließen ihn den Verstand verlieren. Er entschied, dass es irgendwo tief in den Dschungeln von Yucatan eine alte Maya-Stadt gibt - Tayasal, die legendäre Stadt aus Gold\nDer Baron schickte mehrere Expeditionen, um die Stadt zu finden, aber alle wurden völlig in den wilden Dschungel vernichtet. Zweifellos wurden alle von den kriegerischen Itza, die dort leben, abgeschlachtet\nSchließlich hatte Inquisitor Vincento genug von Don Mendosas Fantasien und dem sinnlosen Tod guter Soldaten. Der Inquisitor informierte Madrid über die Situation. Der Vizekönig verbot Don Mendosa, nach der mythischen Stadt zu suchen und sich auf seine Pflichten zu konzentrieren. Dann tauchte Miguel Dichoso auf\nEr überzeugte den Baron, eine weitere Expedition zu organisieren, die überraschenderweise ein Erfolg war. Sie fanden Ruinen einer alten Stadt und einen Haufen Gold, besetzt mit Juwelen. Aber auf ihrer Rückkehr wurden sie vom Mosquito-Stamm angegriffen\nAlle außer Miguel kamen ums Leben, die indianischen Pfeile sind in ein lokales Gift getaucht, selbst eine kleine Kratzwunde führt zu einem sicheren, qualvollen Tod in wenigen Tagen. Dichoso kehrte mit dem Schatz, den er tragen konnte, nach Providence zurück\nCarajo! Der Baron war unsagbar glücklich, er schickte dringende Briefe nach Madrid und an Pater Vincento in Santiago, zweifellos wollte er seinen Erfolg dem verehrten Vater unter die Nase reiben. Dann wurde eine Fregatte vorbereitet, um den Schatz nach Spanien zurückzubringen. Dichoso meldete sich freiwillig, um sie zu begleiten.";
			link.l1 = "Lass mich raten. Er hat das Gold nicht geliefert?";
			link.l1.go = "spa_prisoner_22";			
		break;
		
		case "spa_prisoner_22":
			dialog.text = "Richtig, Señor! Die Fregatte verschwand spurlos zusammen mit der gesamten Ladung und Besatzung, einschließlich Dichoso. Der Baron war außer sich vor Wut. Er wurde erneut vor dem Escorial gedemütigt, zur großen Zufriedenheit von Vater Vincento. Jetzt ist Don Mendosa ein Mann, besessen davon, seinen verletzten Stolz, seinen verlorenen Schatz und Miguel Dichoso wiederzugewinnen";
			link.l1 = "Ist es nicht möglich, dass die Fregatte einfach in einen Sturm geraten und gesunken ist? Oder von Piraten gefangen wurde?";
			link.l1.go = "spa_prisoner_23";			
		break;
		
		case "spa_prisoner_23":
			dialog.text = "Der Baron schwor im Eifer des Gefechts, dass er sicher war, dass Dichoso ihn verraten hat. Ich kenne die Einzelheiten nicht. Nach mehreren Wochen kam Don Diego de Montoya mit neuen Informationen, dass Miguel Dichoso möglicherweise in St.Pierre sei.";
			link.l1 = "Hm. Interessant. Wieder diese indischen Schätze. Alles scheint verdächtig mit ihnen verbunden zu sein... Also, du hast Dichoso nicht gefunden?";
			link.l1.go = "spa_prisoner_24";			
		break;
		
		case "spa_prisoner_24":
			dialog.text = "Nein. Und ehrlich gesagt wäre ich überrascht, wenn er jemals hier war. Der Baron ist so besessen von dem Gedanken, Dichoso zu fangen, dass er selbst die abwegigsten Fantasien glauben würde.";
			link.l1 = "Sag mir, "+npchar.name+", wie hat Don Mendosa von dieser... äh... Stadt Tayasal erfahren? Er hat es nicht geträumt, oder? Gab es einige Fakten oder sonst etwas?";
			link.l1.go = "spa_prisoner_25";			
		break;
		
		case "spa_prisoner_25":
			dialog.text = "Es war Vater Vincento, der zuerst von der angeblichen Existenz von Tayasal und der Stadt aus Gold hörte. Wo er davon erfahren hat, habe ich keine Ahnung...";
			link.l1 = "Das ist eine interessante Entwicklung. Vater Vincento kam ganz allein auf die Theorie der Existenz von Tayasal, informierte Spanien ganz allein und begann, Fliegen in die Salbe des Barons zu werfen...";
			link.l1.go = "spa_prisoner_26";			
		break;
		
		case "spa_prisoner_26":
			dialog.text = "Als Mitkatholik solltest du wissen, wie diese ehrwürdigen Väter des Heiligen Tribunals arbeiten... Er hat Madrid nicht ohne Grund informiert. Er hat irgendeine Art von Vorteil, aber die Ankunft des Barons war anscheinend nicht Teil seiner Pläne. Wie auch immer, ich weiß nichts weiter darüber. Ich hatte nie den Wunsch, mich mit der Inquisition zu befassen.";
			link.l1 = "Gut. Sie haben mir viele interessante Informationen gegeben, "+npchar.name+", und getreu meinem Eid bringe ich dich hier raus. Ich werde später für dich zurückkommen, aber jetzt... lass mich ein bisschen über das nachdenken, was du mir erzählt hast...";
			link.l1.go = "spa_prisoner_27";			
		break;
		
		case "spa_prisoner_27":
			DialogExit();
			pchar.questTemp.Guardoftruth = "think";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto3", "GuardOT_MCthink", -1);
		break;
		
		case "spa_prisoner_28":
			PlaySound("Voice\English\Ransack_2.wav");
			dialog.text = "Herr? Werden Sie Ihr Versprechen einhalten?";
			link.l1 = "Ich halte immer meine Versprechen. Heute ist dein Glückstag, "+npchar.name+". Du kommst mit mir nach Santiago auf Kuba. Ich erzähle dir mehr über meinen Plan, wenn wir ankommen. Aber vorerst, willkommen an Bord. Du wirst zum Hafen begleitet und zu meinem Schiff gebracht.";
			link.l1.go = "spa_prisoner_29";			
		break;
		
		case "spa_prisoner_29":
			dialog.text = "Mein Dank, Kapitän. Ich bin froh, dass Sie ein Gentleman Ihres Wortes sind.";
			link.l1 = "Sie können sich später bedanken. Sie werden mein Gast sein, aber unter Bewachung. Verstehen Sie das nicht falsch, ich brauche Sie noch.";
			link.l1.go = "spa_prisoner_30";			
		break;
		
		case "spa_prisoner_30":
			dialog.text = "Ich verstehe, senor. Ich gebe Ihnen mein Wort als spanischer Offizier, dass ich keine Fluchtversuche unternehmen werde.";
			link.l1 = "Gott schont die Vorsichtigen. Wir sehen uns an Bord.";
			link.l1.go = "spa_prisoner_31";			
		break;
		
		case "spa_prisoner_31":
			DialogExit();
			pchar.questTemp.Guardoftruth = "cuba";
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.GuardOT_exitbase.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_exitbase.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_exitbase.function = "GuardOT_ExitFrombase";
			AddQuestRecord("Guardoftruth", "4");
		break;
		
		case "spa_prisoner_32":
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = "Kapitän, was sind Ihre Ziele hier auf Kuba? Sind Sie hier, um mich abzusetzen? Ich wage es nicht einmal, darauf zu hoffen...";
			link.l1 = "Das ist genau richtig, ich bin hier, um an eure Landsleute zurückzuliefern. Nun, der Grund für meine Ankunft hier ist etwas komplizierter als nur das. Aber das betrifft dich nicht mehr. Ich werde dich jetzt ohne Lösegeld gehen lassen, aber unter der Bedingung, dass du mir zwei Dinge schwörst.";
			link.l1.go = "spa_prisoner_33";			
		break;
		
		case "spa_prisoner_33":
			dialog.text = "Was sind sie?";
			link.l1 = "Das Erste ist, dass ich dir einen versiegelten Brief gebe. Du wirst diesen Brief persönlich an den Inquisitor von Santiago, Vater Vincento, liefern. Wenn er fragt, von wem der Brief ist und wie du ihn bekommen hast, sag ihm die Wahrheit...";
			link.l1.go = "spa_prisoner_34";			
		break;
		
		case "spa_prisoner_34":
			dialog.text = "";
			link.l1 = "Das Zweite ist, dass du keinerlei Versuche, mich zu finden und mein Schiff anzugreifen, unterstützen oder helfen wirst, zumindest für eine Woche. Einverstanden?";
			link.l1.go = "spa_prisoner_35";			
		break;
		
		case "spa_prisoner_35":
			dialog.text = "Ist das alles?";
			link.l1 = "Ja, das ist alles. Erfülle meine Bedingungen und du bist frei zu gehen.";
			link.l1.go = "spa_prisoner_36";			
		break;
		
		case "spa_prisoner_36":
			dialog.text = "Ich schwöre Ihnen, Senor, dass ich den Brief persönlich an Pater Vincento übergeben werde und dass ich keine Handlungen jeglicher Art unternehmen werde, die die Aggression der Garnison von Santiago gegen Sie oder Ihr Schiff provozieren könnten. Seien Sie versichert, ich werde mein Wort halten. Ich bin ein Spanier und ich respektiere starke und noble Gegner.";
			link.l1 = "In Ordnung, Don "+GetFullName(npchar)+", Ich akzeptiere Ihren Schwur und lasse Sie jetzt sofort gehen. Hier, nehmen Sie diesen Brief für den Inquisitor. Sie sind jetzt frei.";
			link.l1.go = "spa_prisoner_37";			
		break;
		
		case "spa_prisoner_37":
			Log_Info("You've given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Lebewohl, Senor. Ich hoffe, wir werden uns nie wieder auf dem Schlachtfeld begegnen. Es würde mich furchtbar betrüben.";
			link.l1 = "Auf Wiedersehen...";
			link.l1.go = "spa_prisoner_38";			
		break;
		
		case "spa_prisoner_38":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Guardoftruth", "5");
			pchar.quest.GuardOT_mayak.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_mayak.win_condition.l1.date.hour  = sti(GetTime()-(rand(4)));
			pchar.quest.GuardOT_mayak.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GuardOT_mayak.win_condition.l2 = "location";
			pchar.quest.GuardOT_mayak.win_condition.l2.location = "mayak9";
			pchar.quest.GuardOT_mayak.function = "GuardOT_CreateVinsentoAgent";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "spa_prisoner_39":
			dialog.text = "Dios mio, was für ein glückliches Treffen! Hallo, Monsieur "+GetFullName(pchar)+"! Ich sehe, Sie sind ein gern gesehener Gast in Santiago geworden. Arbeiten Sie für die Heilige Inquisition?";
			link.l1 = "Grüße, senor "+npchar.name+". Ich dachte, wir würden uns nie wiedersehen, zumindest nicht unter freundlichen Umständen! Nein, ich bin nur vorbeigekommen, um Vater Vincento zu besuchen. Und was ist mit dir? Dienst du jetzt in Santiago?";
			link.l1.go = "spa_prisoner_40";
		break;
		
		case "spa_prisoner_40":
			dialog.text = "Nachdem du mich aus der Verhaftung befreit hast, war ich gezwungen, in Santiago zu bleiben, es ist nicht sicher für mich, nach Providence zurückzukehren... aber wie du sehen kannst, habe ich mein Wort gehalten. Keine spanischen Schiffe auf heißer Verfolgung von dir...";
			link.l1 = "Ich bin froh, dass wir beide Männer unseres Wortes sind.";
			link.l1.go = "spa_prisoner_41";
		break;
		
		case "spa_prisoner_41":
			dialog.text = "Hört zu, Kapitän, würdet Ihr wohl ein Glas Rum erheben, auf unser Wiedersehen, sozusagen? Ich hätte nie gedacht, dass ich das jemals einem Franzosen anbieten würde, aber Ihr, Señor, seid eine Ausnahme.";
			link.l1 = "Natürlich! Ich hätte nichts dagegen, meinen Mund mit etwas Rum zu spülen. Lass uns zur Taverne gehen.";
			link.l1.go = "spa_prisoner_42";
		break;
		
		case "spa_prisoner_42":
			DialogExit();
			NextDiag.CurrentNode = "spa_prisoner_43"; 
			FreeSitLocator("Santiago_tavern", "sit_front4");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Santiago_tavern", "sit", "sit_front4", "GuardOT_SpaOfficerInTavern", -1);
		break;
		
		case "spa_prisoner_43":
			LAi_SetSitType(Pchar);
			dialog.text = "Ach, Prost!";
			link.l1 = "Worauf trinken wir, Señor Offizier?";
			link.l1.go = "spa_prisoner_44";
		break;
		
		case "spa_prisoner_44":
			dialog.text = "Lassen wir auf etwas Neutrales trinken, was uns beide betrifft. Zum Beispiel, tapferer und erfolgreicher Dienst für sein Land! Wir haben alle unseren eigenen!";
			link.l1 = "Und lasst uns auch auf unsere Monarchen trinken, die eine Einigung miteinander erzielen, und dass die Franzosen und die Spanier sowohl zu Hause als auch in der Karibik aufhören zu kämpfen.";
			link.l1.go = "spa_prisoner_45";
		break;
		
		case "spa_prisoner_45":
			dialog.text = "Gut gesagt, Kapitän! Auf den Frieden! Ich werde dir zeigen, wie man auf Spanisch trinkt! Hoch, runter, in die Mitte und rein!";
			link.l1 = "Auf den Frieden... (trinken)";
			link.l1.go = "spa_prisoner_46";
		break;
		
		case "spa_prisoner_46":
			dialog.text = "Aha! Kubanischer Rum ist wirklich der beste in der Karibik...";
			link.l1 = "Ich stimme zu. Sag mir, haben sie versucht, dich für deine Gefangennahme in St. Pierre zu bestrafen?";
			link.l1.go = "spa_prisoner_47";
		break;
		
		case "spa_prisoner_47":
			dialog.text = "Glücklicherweise habe ich nur einen Klaps auf das Handgelenk bekommen. Diese Katastrophe liegt jetzt hinter mir. Sie brauchen schließlich Offiziere hier in den Kolonien.";
			link.l1 = "Und Ihr Kommandant... wie war sein Name... Diego, richtig? Wie ist der ergebnislose Überfall für ihn ausgegangen? Wurde er degradiert?";
			link.l1.go = "spa_prisoner_48";
		break;
		
		case "spa_prisoner_48":
			dialog.text = "Ach nein! Unser lieber Diego de Montoya ist unantastbar, solange er Don Ramon de Mendosa y Riba hinter sich hat. Übrigens, Don Diego war erst gestern in Santiago. Er kam aus San Jose.";
			link.l1 = "Ach wirklich? Faszinierend! Gut, dass wir uns nicht auf der Straße getroffen haben. Ich fürchte, diese Angelegenheit hätte in einem Duell enden können, haha!";
			link.l1.go = "spa_prisoner_49";
		break;
		
		case "spa_prisoner_49":
			dialog.text = "Don Diego hat jetzt keine Zeit für Sie, Kapitän. Er hat gerade viel zu viel auf dem Spiel, um sein Leben in einem Duell zu riskieren. Er hat zusammen mit Baron Mendosa im West Main irgendeinen Plan ausgeheckt. Er hat eine Staffel in Havanna zusammengestellt und plant, jeden Tag zurück nach Spanien zu segeln.";
			link.l1 = "Bist du auch in seiner Mannschaft?";
			link.l1.go = "spa_prisoner_50";
		break;
		
		case "spa_prisoner_50":
			dialog.text = "Nein. Morgen breche ich zur Garnison in San Juan auf, das liegt in Puerto Rico. Auf Providence bin ich bei Don Mendosa nicht mehr willkommen.";
			link.l1 = "Nun, dann lass uns auf deine neue Position trinken und mögen dich dort nichts als glückliche Zeiten und schöne Mädchen erwarten.";
			link.l1.go = "spa_prisoner_51";
		break;
		
		case "spa_prisoner_51":
			dialog.text = "Vielen Dank, Monsieur. Auch Ihnen alles Gute. Ah, ich glaube, es ist Zeit für mich zu gehen. Ich werde dieses Getränk beenden und dann Abschied von Ihnen nehmen.";
			link.l1 = "Geh mit Gott, Herr "+npchar.name+". Vielleicht treffen wir uns wieder in Frieden.";
			link.l1.go = "spa_prisoner_52";
		break;
		
		case "spa_prisoner_52":
			DialogExit();
			AddDialogExitQuest("GuardOT_SpaOfficerOutTavern");
		break;
		
		case "spa_prisoner_53":
			PlaySound("Voice\English\other\OZGi-01.wav");
			dialog.text = "Just as I told you, Don Diego: the fish took the bait; hook, line, and sinker... Oh, looks like we meet again, monsieur. Unfortunately, not under the peaceful auspices that we wished.";
			link.l1 = ""+npchar.name+"? Nun! Das habe ich nicht erwartet. Aus irgendeinem Grund dachte ich, du wärst ein ehrlicher, edler Offizier. Es stellt sich heraus, dass ich mich geirrt habe.";
			link.l1.go = "spa_prisoner_54";
		break;
		
		case "spa_prisoner_54":
			dialog.text = "Was macht dich falsch? Ich habe mein Wort gehalten, ich habe dir keine ewige Freundschaft geschworen. Nichts hat sich geändert, Monsieur. Sie sind immer noch ein Feind von Spanien und mein persönlicher Feind. Dies ist nicht Santiago, hier gibt es keinen Pater Vincento, und seine kleine sichere Passage wird Ihnen nicht helfen...";
			link.l1 = "Oh, ist es so? Ich denke, dass ein freundliches Gespräch bei etwas Rum, und dabei zu versuchen, mich in eine Falle zu locken, ziemlich hinterhältig ist, finden Sie nicht, senor "+npchar.name+"?";
			link.l1.go = "spa_prisoner_55";
		break;
		
		case "spa_prisoner_55":
			dialog.text = "Du wagst es, mich verräterisch zu nennen, du Tölpel?!";
			link.l1 = "...";
			link.l1.go = "spa_prisoner_56";
		break;
		
		case "spa_prisoner_56":
			DialogExit();
			sld = CharacterFromID("Diego");
			sld.dialog.currentnode = "shore";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		// посланец Винсенто
		case "vinsentoagent":
			PlaySound("Voice\English\other\OZGi-02.wav");
			dialog.text = "He, du! Ja, ja, du! "+GetFullName(pchar)+"?";
			link.l1 = "Ja, Kumpel. Ich bin's.";
			link.l1.go = "vinsentoagent_1";			
		break;
		
		case "vinsentoagent_1":
			dialog.text = "Ich habe einen Brief von einer wichtigen Person erhalten. Du weißt bereits, wer es ist.";
			link.l1 = "Ich weiß, gib es hier.";
			link.l1.go = "vinsentoagent_2";			
		break;
		
		case "vinsentoagent_2":
			GiveItem2Character(pchar, "specialletter");
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento";
			dialog.text = "Da hast du es. Wie wäre es mit ein paar Münzen für meine Mühe?";
			if (sti(Pchar.money) >= 2000)
			{
				link.l1 = "Nimm ein wenig Silber. Du hast es ehrlich verdient.";
				link.l1.go = "vinsentoagent_2_1";	
				AddCharacterExpToSkill(pchar, "Leadership", 50);
			}
			else
			{
				link.l1 = "Versuchst du mich übers Ohr zu hauen, Kumpel? Du wurdest bereits für die Lieferung bezahlt.";
				link.l1.go = "vinsentoagent_2_2";
			}
		break;
		
		case "vinsentoagent_2_1":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Danke, Junge. Es ist ein Vergnügen, mit einem großzügigen Gentleman zu verhandeln.";
			link.l1 = "In Ordnung, verschwinde, und sprich kein Wort über das, was hier passiert ist.";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_2_2":
			dialog.text = "Der Havanna-Wolf ist dein Freund...";
			link.l1 = "Hä? Du bist immer noch hier...";
			link.l1.go = "vinsentoagent_3";			
		break;
		
		case "vinsentoagent_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
		break;
		
		// боцман Гая Марше
		case "boatsvandega":
			dialog.text = "Willkommen an Bord der 'Admirable', Kapitän "+GetFullName(pchar)+"!";
			link.l1 = TimeGreeting()+"! Überraschend. Kennst du mich?";
			link.l1.go = "boatsvandega_1";			
		break;
		
		case "boatsvandega_1":
			dialog.text = "Wer in den französischen Kolonien hat noch nicht von dem großartigen Kapitän namens "+GetFullName(pchar)+", derjenige, der einer spanischen Staffel unter Führung eines Schlachtschiffs, die St. Pierre angriff, die Zähne ausschlug und die gesamte feindliche Überfallspartei tötete! Du bist ein nationaler Held!";
			link.l1 = "Ach, komm schon. 'Ein Held'... Ich bin nur ein Soldat, der seine Pflicht für Frankreich erfüllt.";
			link.l1.go = "boatsvandega_2";
		break;
		
		case "boatsvandega_2":
			dialog.text = "Denken Sie nicht, dass viele Soldaten das getan hätten, was Sie getan haben, Kapitän... Eh, ich würde Ihnen gerne etwas Rum in der Taverne spendieren, aber ach: der Kapitän hat den Männern verboten, auch nur einen Tropfen Rum zu trinken und ich möchte kein schlechtes Beispiel setzen...";
			link.l1 = "Hm... Also bist du selbst kein Kapitän?";
			link.l1.go = "boatsvandega_3";
		break;
		
		case "boatsvandega_3":
			dialog.text = "Sehe ich aus wie ein Kapitän? Hoho! Nein, ich bin nur der Bootsmann. Mein Name ist Serge Degas. Unser Kapitän, Gaius Marchais, verbringt den ganzen Tag in der Taverne, inzwischen liegen wir draußen und warten auf irgendeinen 'Händler' Karawane. Der Kapitän schuldet den Seeleuten eine Zulage, und uns auch, die ganze Crew ist völlig pleite..";
			link.l1 = "Was ist los? Kommt die spanische Vanille-Karawane nicht, um ihre Federn zu rupfen?";
			link.l1.go = "boatsvandega_4";
		break;
		
		case "boatsvandega_4":
			dialog.text = "Keine Chance! Unser Kapitän hat der Piraterie ein Ende gesetzt, nachdem er diese Galeone erobert hat. Sie sehen, er hat gehört, dass ein Handelskarawan, der nach Europa segelt, bald einen Zwischenstopp in Guadeloupe machen wird und dort Vanille kaufen wird. Also hat er unsere Laderäume in Bridgetown bis obenhin mit Vanille gefüllt! Dachte, er könnte sie für dreihundert Pesos pro Kiste verkaufen, ja, schöne Aussicht!\nNatürlich gibt es keine Vanillekarawane, als wir ankommen, und den Einheimischen Vanille zu verkaufen wäre ein Verlust. Also hier sind wir, warten auf die 'Händler', ich bin sicher, sie werden hier eines Tages oder drei Jahre von jetzt aufkreuzen... Der Kapitän sitzt den ganzen Tag in der Taverne, ist eine königliche Plage und belästigt jeden. Er kehrt nur zum Schiff zurück, um ohnmächtig zu werden. Jetzt ist er endlich bereit, für zweihundert Pesos zu verkaufen, nur um die Kosten zu decken.\nUnser ganzes Geld steckt in dieser Fracht. Eines Tages wird die Besatzung ihn fesseln und Vanille billig verkaufen, nur um unsere Schulden zu decken... Ich schwöre, ich kann sehen, dass es jeden Tag jetzt kommt.";
			link.l1 = "Aye...was frisst deinen Kapitän?";
			link.l1.go = "boatsvandega_5";
		break;
		
		case "boatsvandega_5":
			dialog.text = "Nun, wenn eine Arbeit getan werden soll, dann sollte sie gut gemacht werden. Er tut weder das eine noch das andere. Er ist ein schrecklicher Händler. Es wäre eine andere Sache gewesen, wenn er auch Fracht transportiert hätte, aber er wollte sich wie ein echter Händler fühlen. Ich hoffe, er stolpert eines Nachts über Bord...";
			link.l1 = "Ich habe dich verstanden, Serge. Mach dir keine Sorgen, ich bin sicher, dass eines Tages deine... Karawane auftauchen wird.";
			link.l1.go = "boatsvandega_6";
		break;
		
		case "boatsvandega_6":
			dialog.text = "Oh, ich glaube nicht an Wunder, Kapitän. Vielleicht werden wir uns eines Tages wieder treffen und etwas Rum trinken... was würde ich jetzt nicht für etwas Rum tun...";
			link.l1 = "Viel Glück, Kumpel.";
			link.l1.go = "boatsvandega_7";
		break;
		
		case "boatsvandega_7":
			DialogExit();
			NextDiag.currentnode = "boatsvandega_8";
			npchar.DeckDialogNode = "boatsvandega_8";
			// активируем каракку
			sld = characterFromId("GOT_Gevarra");
			sld.Dialog.Filename = "Quest\Sharlie\Guardoftruth.c";
			sld.DeckDialogNode = "gevarra";
			AddQuestRecord("Guardoftruth", "16");
		break;
		
		case "boatsvandega_8":
			dialog.text = "Eh, Kapitän, ich hätte gerne einen Schluck Rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "boatsvandega_8";
		break;
		
		// Гай Марше
		case "marshe_tavern":
			PlaySound("Voice\English\tavern\Kontrabandisti-08.wav");
			dialog.text = NPCStringReactionRepeat("Ho! Bist du nicht von dem Handelsschiff? Nein? Oh, entschuldige. Natürlich nicht... Mein Fehler.","Ich bin nicht in Stimmung, Monsieur, also suchen Sie sich jemand anderen zum Reden.","Ach, du schon wieder?!","Ähem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Mach dir keine Sorgen, Kumpel. Es passiert.","Haben Sie etwas Rum, Kapitän. Es wird Ihre Sorgen ein wenig lindern...","Sei nicht nervös, Kumpel. Es ist schlecht für deine Gesundheit.","In Ordnung, in Ordnung. Ich gehe jetzt.",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "marshe_tavern";
		break;
		
		case "marshe_lay":
			PlaySound("Voice\English\citizen\convict-03.wav");
			dialog.text = "Ach du grüne Neune... Mm... Was zum Teufel, was ist das?..";
			link.l1 = "Ruhe, Kamerad... Mach kein Lärm...";
			link.l1.go = "marshe_lay_1";
		break;
		
		case "marshe_lay_1":
			PlaySound("Voice\English\citizen\convict-02.wav");
			dialog.text = "Hä? Was? Verdammt!";
			link.l1 = "";
			link.l1.go = "marshe_lay_2";
		break;
		
		case "marshe_lay_2":
			DialogExit();
			LAi_SetgroundSitType(npchar);
			NextDiag.currentnode = "marshe_sitground";
		break;
		
		case "marshe_sitground":
			PlaySound("Voice\English\EvilPirates07.wav");
			dialog.text = "Aaah! Wer bist du? Was willst du von mir?";
			link.l1 = "Wenn du nicht den Mund hältst, schlage ich dir die Zähne ein, kapiert? Wo sind die heiligen Gefäße, die du gegriffen hast, als du dieses Schiff erobert hast?";
			link.l1.go = "marshe_sitground_1";
		break;
		
		case "marshe_sitground_1":
			dialog.text = "Welche Schiffe? Ich weiß nicht, wovon du redest! Das ist mein Schiff!";
			link.l1 = "Ihr Schiff? Bis vor kurzem hieß sie 'Santa Margarita' und segelte unter der spanischen Flagge... Ich frage Sie, wo sind diese heiligen Gefäße? Ein goldener Monstranz, ein Kreuz mit Lapislazuli besetzt, und ein goldener Weihrauchfass? Was haben Sie damit gemacht? Sie haben sie nicht verkauft, oder?";
			link.l1.go = "marshe_sitground_2";
		break;
		
		case "marshe_sitground_2":
			dialog.text = "Oh Gott, ich glaube meinen Ohren nicht... du bist Spanier? Oh, nein... du bist kein Spanier! Du bist Franzose! Das ist noch schlimmer! Du hast dich an diese abscheulichen Kastilier verkauft! Wie viel zahlen sie heutzutage für die Seelen der Franzosen? Ich werde dir nichts erzählen, Verräter! Du wirst diese Kinkerlitzchen nicht in die Hände bekommen!";
			link.l1 = "Kein Wort, was? Das ist mir recht. Das ist sowieso nicht der beste Ort für ein Verhör... Wir werden dich knebeln, damit du nicht quiekst und dann gehen wir in mein Beiboot... du wirst schließlich reden, Kamerad. Daran habe ich keinen Zweifel.";
			link.l1.go = "marshe_sitground_3";
		break;
		
		case "marshe_sitground_3":
			dialog.text = "Du spanischer Überläufer! Du solltest besser...";
			link.l1 = "Schweig, Schurke... Folge mir direkt oder ich schlage dich nieder und schleife dich über das Deck an deinen Füßen.";
			link.l1.go = "marshe_sitground_4";
		break;
		
		case "marshe_sitground_4":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Deck_Galeon_Ship", "goto", "stand");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1 = "locator";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.location = "Deck_Galeon_Ship";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator_group = "reload";
			pchar.quest.GuardOT_marchfromgaleon.win_condition.l1.locator = "reload2";
			pchar.quest.GuardOT_marchfromgaleon.function = "GuardOT_ExitGaleon";
		break;
		
		// капитан каракки - Карлос Геварра
		case "gevarra":
			dialog.text = "Wie kann ich Ihnen helfen, Herr?";
			link.l1 = "Wie steht's, Kapitän? Was führt Sie nach Basse-Terre? Soweit ich verstehe, sind Sie ein Spanier, der unter der niederländischen Flagge segelt?";
			link.l1.go = "gevarra_1";			
		break;
		
		case "gevarra_1":
			dialog.text = "Was ist das Problem, mein Herr? Ja, ich bin Spanier. Das ist leicht zu erraten anhand des Namens und der Art meines Schiffes, aber ich bin hier ganz legal. Ich habe eine Lizenz von der Niederländischen Westindien-Kompanie, also...";
			link.l1 = "Machen Sie kein Aufhebens, Senor! Wir sind tatsächlich sehr froh, dass Sie Spanier sind... Sagen Sie, sind Sie hier für den Import oder den Export?";
			link.l1.go = "gevarra_2";			
		break;
		
		case "gevarra_2":
			dialog.text = "Ich habe Ware aus Havanna mitgebracht und sie auf dem lokalen Markt verkauft. Jetzt warte ich auf eine profitable Fracht, um nicht mit einem leeren Laderaum nach Hause zu segeln.";
			link.l1 = "Herr, ich habe ein Geschäftsvorschlag für Sie! Sie könnten gutes Geld verdienen, wenn Sie mir helfen. Sollen wir es besprechen? Wie ist übrigens Ihr Name?";
			link.l1.go = "gevarra_3";			
		break;
		
		case "gevarra_3":
			dialog.text = "Carlos. Kapitän Carlos Guevara. Was ist dein Angebot?";
			link.l1 = "Ich muss eine Ladung Vanille kaufen und sie nach Kuba schicken, zu einem Mann namens "+pchar.questTemp.Guardoftruth.LMname+", der Wächter des Leuchtturms von Santiago. Allerdings habe ich ein ernstes Problem. Erstens hat kein Geschäft die Menge an Vanille, die ich brauche...";
			link.l1.go = "gevarra_4";			
		break;
		
		case "gevarra_4":
			dialog.text = "";
			link.l1 = "Zweitens, ich muss sofort nach St. Christopher abreisen und ich weiß nicht, wie lange ich weg sein werde. Ich verliere jeden Tag Geld, verstehst du? Es ist eine verdammt Schande!";
			link.l1.go = "gevarra_5";			
		break;
		
		case "gevarra_5":
			dialog.text = "Ich verstehe. Que lastima, senor. Sie können schließlich nicht das ganze Geld der Welt machen. Also, was wollen Sie von mir?";
			link.l1 = "Schau mal dort hin. Siehst du diese Galeone? Sie ist vollgestopft mit Vanille, die ich dringend brauche. Das Problem ist, der Kapitän der Galeone hat sich irgendeinen Unsinn in den Kopf gesetzt, dass bald eine Gewürzkarawane hier ankommen wird, die seine Ladung mit Gewinn kauft, fast dreihundert Pesos pro Kiste!";
			link.l1.go = "gevarra_6";			
		break;
		
		case "gevarra_6":
			dialog.text = "Ja, es gibt heutzutage viele naive Männer, ein Narr und sein Geld sind bald getrennt...";
			link.l1 = "Naiv ist eine Sache, aber er ist einfach nur flach aus dumm! Ich habe angeboten, seine Vanille für zweihundertzehn Pesos zu kaufen, er wird nicht einmal zweihundert in einem Laden hier holen. Und kannst du es glauben, er hat mir gesagt, ich soll abhauen! Er sagte, er würde nur für zweihundertfünfzig verkaufen!";
			link.l1.go = "gevarra_7";			
		break;
		
		case "gevarra_7":
			dialog.text = "Haha! Was für ein Idiot!";
			link.l1 = "Ja! Das ist im Grunde das, was ich ihm gesagt habe. Natürlich wurde er wütend auf mich... aber ich brauche wirklich diese Vanille! Hier ist mein Vorschlag, Senor. Ich bin kein Händler, aber ich denke, Sie sind ein echter Meister in der Kunst des Handels. Und Sie haben einen geräumigen Laderaum...";
			link.l1.go = "gevarra_8";			
		break;
		
		case "gevarra_8":
			dialog.text = "";
			link.l1 = "Überrede diesen verdammten Narren dazu, dir die Ladung zu verkaufen. Er wird sie mir jetzt nicht mehr verkaufen, nachdem ich ihn ins Gesicht beleidigt habe. Ich bin bereit, zweihundertzehn Pesos pro Kiste zu zahlen. Wenn du den Preis senkst, behalte die Differenz für dich. Und dafür werde ich dein Boot mieten, um die Vanille nach Santiago zu liefern";
			link.l1.go = "gevarra_9";			
		break;
		
		case "gevarra_9":
			dialog.text = "Wie viel bist du bereit, mir für die Lieferung zu zahlen?";
			link.l1 = "Wie viel willst du?";
			link.l1.go = "gevarra_10";			
		break;
		
		case "gevarra_10":
			dialog.text = "Santiago ist ziemlich weit weg...dreißigtausend Pesos.";
			link.l1 = "Das ist zu viel, Amigo. Triff mich hier auf halbem Weg.";
			link.l1.go = "gevarra_11";			
		break;
		
		case "gevarra_11":
			dialog.text = "Also gut, es liegt sowieso auf meinem Weg...Fünfundzwanzigtausend und keinen Peso weniger.";
			link.l1 = "Das ist gut. Der Kapitän der Galeone heißt Gaius Marchais. Er verbringt den ganzen Tag schmollend in der Taverne. Ich hoffe, du kannst ihn überzeugen, sich von seinen Gewürzen zu trennen.";
			link.l1.go = "gevarra_12";			
		break;
		
		case "gevarra_12":
			dialog.text = "Ich habe schon mit größeren Idioten Geschäfte gemacht. Ich werde ihm alle Details erzählen, wer die Gerüchte über den Karawanen verbreitet, der angeblich die Ware zu horrenden Preisen kaufen wollte. Sobald ich ihn davon überzeugt habe, dass alles nur Einbildung ist, wird er verkaufen, da bin ich sicher.";
			link.l1 = "Also, wir haben einen Deal?";
			link.l1.go = "gevarra_13";			
		break;
		
		case "gevarra_13":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Wir haben einen Deal, wenn du das Geld hast, um für die Vanille und den Versand zu bezahlen. Wie das charmante irische Sprichwort sagt: 'Zeig mir das Geld.'";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Hier, schau mal. Alles ist hier.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Ich habe das Silber auf meinem Schiff. Ich gehe es holen und bin gleich wieder da!";
				link.l1.go = "gevarra_14_no";
			}
		break;
		
		case "gevarra_14_no":
			DialogExit();
			NextDiag.currentnode = "gevarra_wait";
			npchar.DeckDialogNode = "gevarra_wait";
		break;
		
		case "gevarra_wait":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			dialog.text = "Haben Sie das Geld mitgebracht?";
			if (sti(Pchar.money) >= iTemp)
			{
				link.l1 = "Hier, schau mal. Alles ist hier.";
				link.l1.go = "gevarra_14";
			}
			else
			{
				link.l1 = "Ich verstehe es gerade jetzt!";
				link.l1.go = "exit";
			}	
		break;
		
		case "gevarra_14":
			if (stf(environment.time) < 24.0)
			{
				sTemp = "tomorrow";
				iTemp = 1;
			}
			else
			{
				sTemp = "today";
				iTemp = 0;
			}
			if (stf(environment.time) > 21.0 && stf(environment.time) < 7.0)
			{
				dialog.text = "Ausgezeichnet! Ich mache gerne Geschäfte mit vernünftigen Partnern. Komm zurück "+sTemp+"bis zehn Uhr morgens. Ich denke, dass unser gemeinsamer Freund Gaius bis dahin wieder zu Sinnen gekommen sein wird.";
				link.l1 = "Großartig! Bis später!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = 10.0;
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
			else
			{
				dialog.text = "Fantastisch! Ich mache gerne Geschäfte mit vernünftigen Partnern. Ich gehe jetzt zur Küste. Kommen Sie in drei Stunden zurück. Ich denke, dass unser gemeinsamer Freund Gaius bis dahin zur Besinnung gekommen sein wird..";
				link.l1 = "Toll! Bis später!";
				link.l1.go = "gevarra_15";
				pchar.quest.GuardOT_tradetimer.win_condition.l1 = "Timer";
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.hour  = sti(GetTime()+3);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.GuardOT_tradetimer.function = "GuardOT_PrepareTrade";
			}
		break;
		
		case "gevarra_15":
			iTemp = sti(pchar.questTemp.Guardoftruth.VanilleQty)*210+25000;
			DialogExit();
			NextDiag.currentnode = "gevarra_time";
			npchar.DeckDialogNode = "gevarra_time";
			AddMoneyToCharacter(pchar, -iTemp); // деньги сразу списываем
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			AddQuestRecord("Guardoftruth", "17");
			AddCharacterExpToSkill(pchar, "Sneak", 50);
		break;
		
		case "gevarra_time":
			dialog.text = "Herr, ich erinnere mich gut an meine Rolle. Mach dir keine Sorgen, er mag eine harte Nuss sein, aber ich werde ihn knacken.";
			link.l1 = "Danke.";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_time";
		break;
		
		case "gevarra_16":
			dialog.text = "Es ist getan, senor. Der arme Mann war überglücklich, dass ich seine Vanille kaufen wollte. Seine Hände zitterten vor Glück, während ich eine Anzahlung zählte - oder vielleicht war das nur vom Rum. Wir werden die Ladung morgen Mittag am Capster Strand verladen, um unerwünschte Aufmerksamkeit von Zollbeamten im Hafen zu vermeiden\nIch werde sofort nach Santiago segeln, sobald ich die Ladung an Bord habe. Ich kontaktiere Ihren Partner am Leuchtturm und überschreibe ihm die Vanille nach der Lieferung dort. Gibt es eine Nachricht, die Sie ihm übermitteln möchten?";
			link.l1 = "Ja. Hier ist ein Brief. Du sagst, der Handel wird morgen mittags am Capster Strand sein? Gut dann, ich werde vor dem Landzunge ankern, unzugänglich für die Insel, falls etwas passiert.";
			link.l1.go = "gevarra_17";
		break;
		
		case "gevarra_17":
			Log_Info("You handed the letter over");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie können mir vertrauen, Senor. Ich bin ein ehrlicher Mann. Außerdem habe ich keine Lust, mich mit Ihnen anzulegen, und ein Kaufmann ist nichts ohne seinen Ruf. Aber wenn Sie zuschauen und überprüfen möchten, ist das für mich keine Belastung.";
			link.l1 = "Ich bin dankbar, senor. Ich werde morgen auf das Geschäft aufpassen und sobald Sie ablegen, werde ich meine Geschäfte in St. Christopher erledigen.";
			link.l1.go = "gevarra_18";
		break;
		
		case "gevarra_18":
			DialogExit();
			NextDiag.currentnode = "gevarra_exit";
			npchar.DeckDialogNode = "gevarra_exit";
			bQuestDisableMapEnter = true;
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			AddQuestRecord("Guardoftruth", "18");
			pchar.quest.GuardOT_gotoshore.win_condition.l1 = "ExitFromSea";
			pchar.quest.GuardOT_gotoshore.function = "GuardOT_TradeComplete";
		break;
		
		case "gevarra_exit":
			dialog.text = "Kapitän, ich versichere Ihnen: Ich werde Sie nicht enttäuschen und die Bedingungen unseres Vertrags vollständig erfüllen.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gevarra_exit";
		break;
		
		// матросы Марше
		case "marshe_sailor":
			dialog.text = LinkRandPhrase("Hicks! H-hurra! Der gute alte Käpt'n hat uns endlich unseren Lohn gegeben! Drei Hurra für den Käpt'n! Hicks!","Es gibt sie in Pints?! Ich hole mir eins!","Mögen unsere Beutel fett und unsere Dirnen fetter sein! Hurra!","Und dort lagen sie, all die guten toten Männer, hic! Wie der Morgengrauen in einem Sauflokal. Yo ho ho und eine Flasche Rum!","Yo ho ho und eine Flasche Rum!");
			link.l1 = LinkRandPhrase("Ja, Kumpel.","Glaubst du nicht, dass du schon genug Rum gehabt hast?","Trinken und der Teufel haben für den Rest gesorgt...");
			link.l1.go = "exit";
		break;
		
		case "galeonguard":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Halt! Wer geht dort? Alarm! Abwehren die Angreifer!";
			link.l1 = "...";
			link.l1.go = "galeonguard_1";
		break;
		
		case "galeonguard_1":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			CheckAndSetOverloadMode(GetMainCharacter());
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Attack");
			LAi_RemoveCheckMinHP(pchar);
			GuardOT_GaleonGuardFightAdd();
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_galeonguard_"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "GaleonFight");
			}
			LAi_group_FightGroups("GaleonFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// англичане в бухте
		case "dominica_hunter":
			dialog.text = "Har har! Du bist auch wegen Rollie dem Käppi's Schatz hier, eh? Wir haben gesucht und gesucht und gesucht und wir konnten ihn einfach nicht finden. Ich wünschte, mindestens einer dieser Idioten würde erraten, hinter den Wasserfall zu schwimmen, auf den Sims!";
			link.l1 = "Du bist einer von Oberst Fox's Männern, nicht wahr?";
			link.l1.go = "dominica_hunter_1";
		break;
		
		case "dominica_hunter_1":
			dialog.text = "Es könnte sein, dass ich Verbindungen zu den Seefüchsen habe. Du musst es nicht wissen, es hat keinen Sinn. Du musst jetzt nichts wissen. Du hast meinen Schatz gefunden, wofür wir dir nun großen Dank schulden...";
			link.l1 = "Ich verstehe. Du bist kein Seefuchs, eher ein Seehund... oder Schakal. Was passt besser zu dir?";
			link.l1.go = "dominica_hunter_2";
		break;
		
		case "dominica_hunter_2":
			dialog.text = "Sieht so aus, als hätten wir einen echten Philosophen in unserer Mitte, Jungs. Einen wahren Experten für das Tierreich!";
			link.l1 = "Sollst du die Schärfe meines Säbels inspizieren, Schakal?";
			link.l1.go = "dominica_hunter_3";
		break;
		
		case "dominica_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("GuardOT_DH_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_HuntersDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Белинда Риберо
		case "belinda":
			dialog.text = TimeGreeting()+", senor. Wie kann ich Ihnen helfen?";
			link.l1 = "Hallo. Sind Sie Donna Belinda de Ribero?";
			link.l1.go = "belinda_1";
		break;
		
		case "belinda_1":
			dialog.text = "Ja, das bin ich. Mit wem habe ich die Ehre zu sprechen?";
			link.l1 = "Kapitän "+GetFullName(pchar)+", gnädige Frau. Lassen Sie sich bitte nicht von meinem französischen Nachnamen abschrecken, ich erfülle derzeit einen Auftrag des sehr ehrenwerten Inquisitors von Santiago, Vater Vincento.";
			link.l1.go = "belinda_2";
		break;
		
		case "belinda_2":
			dialog.text = "Que interesante! Ich habe gehört, dass das Heilige Tribunal und die Gesellschaft Jesu mit einer großen Menge von Menschen aller Klassen und Nationalitäten gefüllt sind, aber ich habe noch nie zuvor einen Ausländer getroffen, der für sie arbeitet. Was kann ich für Sie tun, senor?";
			link.l1 = "Sie besitzen ein Objekt, an dem der ehrwürdige Vater sehr interessiert ist. Ein goldenes Ostensorium, eine Monstranz, die Sie kürzlich von dem Bankier in Willemstad erworben haben.";
			link.l1.go = "belinda_3";
		break;
		
		case "belinda_3":
			dialog.text = "Sie sind sehr gut informiert, Senor. Nun, wenn ich bedenke, für wen Sie arbeiten, sollte mich das nicht überraschen. Ja, ich habe das Ostensorium gekauft, es hätte sicherlich nicht in einem Händlerladen neben gestohlenen Krimskrams und verpfändeten Waren wie irgendeinem unbedeutenden Kinkerlitzchen liegen dürfen.";
			link.l1 = "Haben Sie das Monstranz, Madame?";
			link.l1.go = "belinda_4";
		break;
		
		case "belinda_4":
			dialog.text = "Ja. Ich hatte vor, es unserer Pfarrkirche zu schenken, aber hier ist so viel auf mich zugekommen... ich konnte nicht... oh, es tut mir leid...";
			link.l1 = "Sind Sie am Weinen, Madame? Haben meine Worte Ihnen Kummer bereitet? Wenn ja, bitte verzeihen Sie mir.";
			link.l1.go = "belinda_5";
		break;
		
		case "belinda_5":
			dialog.text = "Oh, bitte senor... Lassen Sie uns zu unserem Gespräch zurückkehren. Wie ich verstehe, braucht Vater Vincento dieses Ostensorium? Sie möchten, dass ich es Ihnen gebe?";
			link.l1 = "Dieses kostbare Gefäß war für die Kathedrale in Santiago bestimmt, wurde aber von einem gemeinen Piraten erobert und zusammen mit mehreren anderen heiligen Objekten an einen Wucherer verkauft. Meine Aufgabe ist es, das Gestohlene dorthin zurückzubringen, wo es hingehört. Natürlich werde ich Ihnen Ihre Ausgaben vollständig erstatten.";
			link.l1.go = "belinda_6";
		break;
		
		case "belinda_6":
			dialog.text = "Oh, das darfst du nicht! Glaubst du wirklich, dass mir dieses Geld so viel bedeutet? Ich habe dieses Ostensorium für die Heilige Mutter Kirche gekauft und werde nicht zögern, es seinem wahren Besitzer zu übergeben, ganz zu schweigen von einem Mitglied der Gesellschaft Jesu, das dem Vater Vincento dient. Aber, eine andere Sache beunruhigt mich zutiefst. Könntest du bitte einer treuen Tochter der Kirche in ihrer Not helfen?";
			link.l1 = "Sie sind eine edle Frau, Madame. Welche Sorgen plagen Sie? Wie kann ich Ihnen helfen?";
			link.l1.go = "belinda_7";
		break;
		
		case "belinda_7":
			dialog.text = "Oh, aber senor... Ich würde es nicht wagen, einen Jesuitenbruder selbst um Hilfe zu bitten. Sie sind immer so sehr beschäftigt...";
			link.l1 = "Du hast es bereits getan. Was ist los?";
			link.l1.go = "belinda_8";
		break;
		
		case "belinda_8":
			dialog.text = "Können Sie mir versprechen, als Vertreter der Heiligen Kirche, dass niemand jemals herausfinden wird, wofür ich Sie bitte?";
			link.l1 = "Ich gebe Ihnen mein feierliches Versprechen, senora. Es ist nicht das Siegel des Beichtstuhls, aber ich werde kein Wort davon zu einer Seele atmen.";
			link.l1.go = "belinda_9";
		break;
		
		case "belinda_9":
			dialog.text = "Sehr gut. Ich vertraue Ihnen. Mein sehr lieber Freund Esteban Sosa ist in Schwierigkeiten geraten. Er wurde von Banditen gefangen genommen, während er reiste, und sie verlangen ein Lösegeld von hunderttausend Pesos. Ich besitze nicht so viel Geld und habe nur etwa die Hälfte der Summe aus meiner Zulage zusammenkratzen können. Ich kann niemanden um Hilfe in einer solchen Angelegenheit bitten, weil sie geschworen haben, ihn zu töten, wenn ich das tue.\nAußerdem mache ich mir Sorgen um meinen lieben... Freund und fürchte das Schlimmste. Sie könnten ihn töten, sobald sie das Geld bekommen, um sicherzustellen, dass er den Wachen nichts von ihnen erzählt. Vielleicht könnten Sie, ein mutiger Kapitän, ein Christ und ein Bruder der Gesellschaft, die Banditen dazu überreden, das Geld, das ich habe, anzunehmen und ihm nicht zu schaden...";
			link.l1 = "Wann und wo findet der Austausch statt?";
			link.l1.go = "belinda_10";
		break;
		
		case "belinda_10":
			dialog.text = "Ihr Anführer ist ein Mann namens Bartie der Schlächter. Er sagte, er würde jede Nacht von elf Uhr bis Mitternacht am Höhleneingang im Dschungel auf Estebans Lösegeld warten...";
			link.l1 = "Das sind ungewöhnlich spezifische Bedingungen...";
			link.l1.go = "belinda_11";
		break;
		
		case "belinda_11":
			dialog.text = "Anscheinend wollten sie, dass ich das ganze Lösegeld schnell zusammenstelle und niemanden um Hilfe bitte... aber ich kann solches Geld nicht finden, ich werde nie in der Lage sein!";
			link.l1 = "Weine nicht, Madame. Ich werde versuchen, Ihnen zu helfen. Ein Bruder der Gesellschaft Jesu würde niemals eine rechtschaffene christliche Frau in Not lassen.";
			link.l1.go = "belinda_12";
		break;
		
		case "belinda_12":
			dialog.text = "Ich muss mein Vertrauen in dich setzen...Aber Kapitän, Bartie der Knacker sagte auch, dass wenn der Lösegeldbringer nicht alleine kommt oder wenn ich zu den Wachen gehe, er den armen Estaban sofort töten wird!";
			link.l1 = "Ich werde das im Hinterkopf behalten.";
			link.l1.go = "belinda_13";
		break;
		
		case "belinda_13":
			dialog.text = "Hier, nimm das. Es sind die fünfzigtausend Pesos, die ich zusammenkratzen konnte. Überrede diese Schurken zumindest dazu, das zu nehmen. Sag ihnen, ich habe keinen einzigen Peso mehr! Bring Esteban zurück! Sobald du das tust, gebe ich dir gerne das Ostensorium für Vater Vincento.";
			link.l1 = "Ich werde alles tun, was ich kann, gnädige Frau. Hoffen wir das Beste.";
			link.l1.go = "belinda_14";
		break;
		
		case "belinda_14":
			dialog.text = "Möge Gott Ihnen helfen, tapferer Kapitän! Ich werde für Sie beten!";
			link.l1 = "Hello, friend.";
			link.l1.go = "belinda_15";
		break;
		
		case "belinda_15":
			AddMoneyToCharacter(pchar, 50000);
			DialogExit();
			NextDiag.CurrentNode = "belinda_16";
			AddQuestRecord("Guardoftruth", "31");
			bQuestDisableMapEnter = true;//закрыть карту
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", true);
			LAi_LocationDisableOfficersGen("Cumana_Cave", true);
			pchar.quest.GuardOT_gotocave.win_condition.l1 = "location";
			pchar.quest.GuardOT_gotocave.win_condition.l1.location = "Cumana_CaveEntrance";
			pchar.quest.GuardOT_gotocave.win_condition.l2 = "HardHour";
			pchar.quest.GuardOT_gotocave.win_condition.l2.hour = 23.00;
			pchar.quest.GuardOT_gotocave.function = "GuardOT_InCaveEntrance";
		break;
		
		case "belinda_16":
			dialog.text = "Haben Sie Neuigkeiten, Kapitän?";
			link.l1 = "Noch nicht. Warten Sie nur, Senora. Ich werde Sie nicht enttäuschen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "belinda_16";
		break;
		
		case "belinda_17":
			dialog.text = "Haben Sie Neuigkeiten, Kapitän?";
			link.l1 = "Ja, Senora. Ich fürchte, es sind keine guten Nachrichten.";
			link.l1.go = "belinda_18";
		break;
		
		case "belinda_18":
			dialog.text = "Sag es mir, lass mich nicht warten! Hast du dich mit den Banditen getroffen?";
			if (sti(Pchar.money) >= 50000)
			{
				link.l1 = "Hier, nimm deine fünfzigtausend zurück. Ich brauchte es nicht. Nimm auch diesen Ring. Ich glaube, du wirst ihn bekannt finden.";
				link.l1.go = "belinda_19_1";
			}
			link.l2 = "Hier, nimm diesen Ring. Ich glaube, du wirst ihn bekannt finden.";
			link.l2.go = "belinda_19_2";
		break;
		
		case "belinda_19_1":
			RemoveItems(pchar, "jewelry29", 1);
			PlaySound("interface\important_item.wav");
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Es... ja, es kommt mir bekannt vor. Was ist mit Esteban passiert?";
			link.l1 = "Ich habe die Briganten in der Höhle gefunden, wie du mir gesagt hast. 'Bartie der Schlächter' und Esteban Sosa sind ein und derselbe Mann. Er hat die Entführung inszeniert, um dich zu erpressen. Er hat mir von eurer... Beziehung erzählt. Er sagte auch, dass er dich nicht mehr sehen will. Ich habe den Ring genommen, den du ihm als Beweis gegeben hast.";
			link.l1.go = "belinda_20";
		break;
		
		case "belinda_19_2":
			dialog.text = "Das... ja, ja ich weiß es. Was ist mit Esteban passiert?";
			link.l1 = "Ich habe die Banditen in der Höhle gefunden, wie du es mir gesagt hast. Sie haben mich angegriffen, gefesselt und dein Geld genommen. 'Bartie der Schlachter' und Esteban Sosa sind ein und dieselbe Person. Er hat die Entführung inszeniert, um dich zu erpressen. Er hat mir von eurer... Beziehung erzählt. Esteban hat mich gehen lassen und mir diesen Ring als Beweis gegeben. Er sagte, dass du ihn nie wieder sehen wirst.";
			link.l1.go = "belinda_20";
			npchar.quest.nomoney = true;
		break;
		
		case "belinda_20":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "I taught him a lesson, but I didn't kill him out of respect to you.";
			dialog.text = "Mein Gott! Ich kann meinen Ohren nicht trauen! Warum passiert mir das alles, warum?! Was habe ich getan, damit er....";
			link.l1 = "Senora, ich flehe Sie an, quälen Sie sich nicht so. Dieser Taugenichts ist keine einzige Ihrer Tränen wert. "+sTemp+"";
			link.l1.go = "belinda_21";
		break;
		
		case "belinda_21":
			if (CheckAttribute(npchar, "quest.nomoney")) sTemp = "";
			else sTemp = "And besides that, here's a gift to keep up your courage.";
			dialog.text = "Oh... Ich werde versuchen mich zu beruhigen. Senor, ich muss Ihnen für Ihre Hilfe danken. Hier, nehmen Sie Ihr Ostensorium. "+sTemp+"Geh mit Gott.";
			link.l1 = "Danke, Senora. Machen Sie sich keine Sorgen, niemand wird herausfinden, was in der Höhle passiert ist. Wir Jesuiten halten immer unser Wort. Jetzt, wenn Sie gestatten, muss ich gehen.";
			link.l1.go = "belinda_22";
		break;
		
		case "belinda_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "33");
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 3;
			GiveItem2Character(pchar, "jewelry33");
			Log_Info("You've received a gold ostensory");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.nomoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				OfficersReaction("bad");
			}
			else
			{
				Log_Info("You've received an amulet");
				GiveItem2Character(pchar, "amulet_7");
				ChangeCharacterComplexReputation(pchar, "nobility", 5);
				OfficersReaction("good");
				ChangeCharacterNationReputation(pchar, SPAIN, 3);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
			}
		break;
		
		// бандит Эстебана
		case "bandos_mush":
			PlaySound("Voice\English\other\OZGi-04.wav");
			dialog.text = "Halt, Kumpel!";
			link.l1 = "Ich stehe genau hier.";
			link.l1.go = "bandos_mush_1";
		break;
		
		case "bandos_mush_1":
			dialog.text = "Hast du das Geld mitgebracht?";
			link.l1 = "Welch dämliche Frage. Nein, ich bin hier, um Manga Rosas zu pflücken... Warum denkst du sonst, wäre ich hierher gekommen?";
			link.l1.go = "bandos_mush_2";
		break;
		
		case "bandos_mush_2":
			dialog.text = "Oh ho ho! Ein Komiker! Weg mit dir in die Höhle, Bartie wartet auf dich.";
			link.l1 = "Sie sind offensichtlich ein erfahrener Wächter ... mit dieser Einstellung wären Sie geeignet, König Philipp selbst zu bewachen. Ich werde mich vorzeigen.";
			link.l1.go = "bandos_mush_3";
		break;
		
		case "bandos_mush_3":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", true);
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.GuardOT_incave.win_condition.l1 = "location";
			pchar.quest.GuardOT_incave.win_condition.l1.location = "Cumana_Cave";
			pchar.quest.GuardOT_incave.function = "GuardOT_InCumanaCave";
		break;
		
		// Эстебан-Барти
		case "barty":
			PlaySound("Voice\English\other\OZGi-03.wav");
			dialog.text = "Du hast mich warten lassen... Hast du das Geld dabei?";
			link.l1 = "Bist du Bartie der Knacker? Du siehst für mich nicht wie ein gewöhnlicher Bandit aus.";
			link.l1.go = "barty_1";
		break;
		
		case "barty_1":
			dialog.text = "Warum interessiert es dich, wie ich aussehe? Hast du verdammt nochmal das Geld oder nicht?";
			link.l1 = "Wo ist die Geisel?";
			link.l1.go = "barty_2";
		break;
		
		case "barty_2":
			dialog.text = "Du bekommst deine Geisel. Los, gib mir die Münze. Mach mich nicht wütend, Junge.";
			link.l1 = "Bartie, sehe ich aus wie ein Narr? Bis ich Esteban Sosa lebendig und aktiv sehe, wirst du keinen einzigen Peso sehen. Wo ist er?";
			link.l1.go = "barty_3";
		break;
		
		case "barty_3":
			dialog.text = "Oh, du stemmst dich also gegen uns, hm? Gut, wir werden dir eine gute Lektion erteilen... Jungs, lasst uns diesem Scheißfresser ein neues Loch reißen!";
			link.l1 = "Drecksack!";
			link.l1.go = "barty_4";
		break;
		
		case "barty_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			GuardOT_InCumanaCaveEnemyAdd();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GOT_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CumanaCaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			// офицеров насильно
			LAi_LocationDisableOfficersGen("Cumana_Cave", false); //офицеров пускать
			DoQuestFunctionDelay("GuardOT_SetOfficerCumanaCave", 3.0);
		break;
		
		case "barty_5":
			PlaySound("Voice\English\other\Plennie-02.wav");
			dialog.text = "";
			link.l1 = "Ist das genug Tanzen für dich? Wo ist Esteban Sosa? Komm schon, sag es mir oder ich halte deinen Kopf unter Wasser, bis die Blasen aufhören!";
			link.l1.go = "barty_6";
		break;
		
		case "barty_6":
			dialog.text = "Nein... Bitte tut mir nicht weh! Ich bin Esteban Sosa.";
			link.l1 = "Was?";
			link.l1.go = "barty_7";
		break;
		
		case "barty_7":
			dialog.text = "Ja, ja. Ich bin kein Bartie der Schinder. Ich bin einfach nur...";
			link.l1 = "Du Schurke! Also hast du dich dazu entschlossen, hunderttausend Pesos von Senora de Ribero zu 'erpressen', indem du dich selbst 'entführst'?!";
			link.l1.go = "barty_8";
		break;
		
		case "barty_8":
			dialog.text = "Du musst mich verstehen, Mann zu Mann. Belinda... Ihre obsessive Liebe hat mich wirklich abgeschreckt. Sie ist rund um die Uhr bei mir, Mann! Selbst ihr Ehemann begann, Verdacht zu schöpfen, und er ist halb blind!";
			link.l1 = "Nun, wie wäre es damit! Also seid ihr Liebende?";
			link.l1.go = "barty_9";
		break;
		
		case "barty_9":
			dialog.text = "Nicht mehr. Ich bin gerade vor ihr weggelaufen.";
			link.l1 = "Und du hast beschlossen, ein paar Münzen für den Weg zu nehmen, hm? Nun, was soll ich jetzt mit dir anfangen? Deinen Körper im Dschungel verstecken, wie du es bei mir versucht hast?";
			link.l1.go = "barty_10";
		break;
		
		case "barty_10":
			dialog.text = "Nein! Ich wollte kein Blut, ich schwöre es!";
			link.l1 = "Ist das der Grund, warum du deine Hunde auf mich gehetzt hast?";
			link.l1.go = "barty_11";
		break;
		
		case "barty_11":
			dialog.text = "Wir wollten nur deine Taschen leeren, das ist alles!";
			link.l1 = "Und mich nackt im Dschungel zurücklassen? Ich sollte dich aufknüpfen und dich vom höchsten Ausguck meines Schiffs hängen lassen, du Schurke! Aber das werde ich nicht tun, rein aus Respekt vor der guten Frau, die das Unglück hatte, sich mit dir einzulassen. Weißt du was? Ich sollte dich zu ihr bringen und sie entscheiden lassen, was sie mit dir anfangen soll.";
			link.l1.go = "barty_12";
		break;
		
		case "barty_12":
			dialog.text = "Nein, alles nur das nicht! Ich gehe nicht zurück nach Cumana!";
			link.l1 = "Du würdest lieber für immer in dieser Höhle bleiben?";
			link.l1.go = "barty_13";
		break;
		
		case "barty_13":
			dialog.text = "Verschone mich, senor! Lassen Sie mich gehen und ich werde von hier segeln und nie wieder nach Cumana zurückkehren! Ich werde nicht darauf warten, dass Belindas Ehemann mich in einem Duell zerschneidet oder einen Mörder auf mich ansetzt!";
			link.l1 = "Gut. Um der Senora de Ribero willen, werde ich dich nicht zu ihr bringen. Aber denke nicht für eine Sekunde, dass das alles unter den Teppich gekehrt wird. Sie wird herausfinden, mit welchem erbärmlichen Stück Scheiße sie sich entschieden hat zu flirten. Welche Zeichen hast du, dass sie erkennen könnte?";
			link.l1.go = "barty_14";
		break;
		
		case "barty_14":
			dialog.text = "Hier. Dieser türkise Ring hier. Sie gab ihn mir selbst.";
			link.l1 = "Perfekt. Gib es mir und verschwinde aus meinen Augen!";
			link.l1.go = "barty_15";
			// belamour legendary edition -->
			link.l2 = "Perfekt. Und wissen Sie, Sosa, ich habe meine Meinung geändert - jetzt diene ich der Gesellschaft Jesu. Wie die Schrift sagt, 'Du musst die böse Person aus deiner Mitte ausmerzen.' Und Sie sind ein verdorbener Narzisst, ein Verbrecher und ein nutzloses Stück Scheiße. Ich glaube, ich werde dich in dieser Höhle ertränken. Requiesce in pace.";
			link.l2.go = "barty_15a";
		break;
		
		case "barty_15a":
			DialogExit();
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Sosa", 1.0); 
		break;
			
		case "barty_15":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			// <-- legendary edition
			GiveItem2Character(pchar, "jewelry29");
			Log_Info("You received a turquoise ring");
			PlaySound("interface\important_item.wav");
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("Cumana_CaveEntrance", false);//офицеров пускать
			locations[FindLocation("Cumana_CaveEntrance")].DisableEncounters = false; //энкаутеры открыть
			locations[FindLocation("Cumana_Cave")].DisableEncounters = false; // patch
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_CaveEntrance")], false);//разрешить драться
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			LocatorReloadEnterDisable("Cumana_CaveEntrance", "reload2_back", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("GOT_Belinda");
			sld.dialog.currentnode = "Belinda_17";
			AddQuestRecord("Guardoftruth", "32");
		break;
		
		// охотники
		case "spa_hunter":
			dialog.text = "Du hast, was wir brauchen, Kamerad...";
			link.l1 = "Wirklich? Und was wäre das?";
			link.l1.go = "spa_hunter_1";
		break;
		
		case "spa_hunter_1":
			dialog.text = "Ich habe nicht gefragt, reicher Bursche. Mir wurde befohlen, all deine Habseligkeiten zu nehmen, absolut alles, was du bei dir hast. Machen wir das auf die leichte oder die harte Weise? Die Wahl liegt bei dir.";
			link.l1 = "Du denkst, du bist ein Krieger, hm? Du hast keine Ahnung, mit wem du es zu tun hast. Ich frühstücke Abschaum wie dich zum Frühstück.";
			link.l1.go = "spa_hunter_2";
		break;
		
		case "spa_hunter_2":
			dialog.text = "Du bist ein richtiger Spaßvogel, nicht wahr, Frosch? Nun, dann lass uns mal sehen, wie dein Blut auf dem Boden aussieht!";
			link.l1 = "Es wird genauso aussehen wie deins, Idiot. Lass mich dir eine Anatomiestunde geben!";
			link.l1.go = "spa_hunter_3";
		break;
		
		case "spa_hunter_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for(i=1; i<=5; i++)
			{
				sld = characterFromID("GOT_santiagoband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_SantiagoBandDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "cabin_hunter":
			dialog.text = "Haw haw, gut gemacht Kamerad... Leere deine Taschen doppelt so schnell aus! Wenn du ein braver kleiner Junge bist und zuhörst, bleibst du heil, kapiert?";
			link.l1 = "Verdammt, ihr schon wieder? Ihr seid auch bis hierher gekommen? Wer zum Teufel hat euch angeheuert?!";
			link.l1.go = "cabin_hunter_1";
		break;
		
		case "cabin_hunter_1":
			dialog.text = "Geht dich nichts an. Jetzt ergib dich und lebe oder wehre dich und wir nehmen einfach deine Beute von deinem toten Körper. Wie wäre das für ein Angebot?";
			link.l1 = "Ich habe einen Gegenvorschlag. Wie wäre es, wenn ich deine Beute von deinem toten Körper nehme?";
			link.l1.go = "cabin_hunter_2";
		break;
		
		case "cabin_hunter_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for(i=1; i<=2; i++)
			{
				sld = CharacterFromID("GOT_cabinband_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_CabinBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// командир абордажников
		case "batabano_officer":
			dialog.text = "Auf Befehle warten, Kapitän!";
			link.l1 = "Bewegt euch durch den Dschungel in Richtung San Antonio Kap. Nehmt den Pfad links und geht geradeaus weiter. Haltet die Köpfe unten und bereitet euch auf einen Hinterhalt am Ufer vor. Seid bereit. Ich werde dort auf dem Seeweg hinkommen und euch dort treffen. Wie lange werdet ihr brauchen, um dort anzukommen?";
			link.l1.go = "batabano_officer_1";
		break;
		
		case "batabano_officer_1":
			dialog.text = "Wir werden in sechs Stunden da sein, Kapitän!";
			link.l1 = "Gut. Beweg dich!";
			link.l1.go = "batabano_officer_2";
		break;
		
		case "batabano_officer_2":
			DialogExit();
			LocatorReloadEnterDisable("Shore13", "boat", false);
			for(i=1; i<=10; i++)
			{
				sld = characterFromID("GuardOT_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 20.0);
			}
			AddQuestRecord("Guardoftruth", "48");
			// на мыс
			pchar.quest.GuardOT_sanantonio.win_condition.l1 = "Ship_location";
			pchar.quest.GuardOT_sanantonio.win_condition.l1.location = "Shore15";
			pchar.quest.GuardOT_sanantonio.function = "GuardOT_SanantonioArrive";
			// на время, специально для дебилов, не читающих диалоги и СЖ
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1 = "Timer";
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.hour  = sti(GetTime()+6);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.GuardOT_sanantoniotimer.function = "GuardOT_SanAntonio_Timer";
		break;
		
		// наёмник Патерсона
		case "housemercen":
			dialog.text = "Hartnäckiger Bastard! Er ist immer noch am Leben... Ich wusste, wir hätten mehr Schießpulver verwenden sollen! Na gut, ich werde dich erledigen, du Hurensohn...";
			link.l1 = "...";
			link.l1.go = "housemercen_1";
		break;
		
		case "housemercen_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			bDisableCharacterMenu = false;//разлочим F2
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			if (MOD_SKILL_ENEMY_RATE < 5) LAi_group_SetCheck("EnemyFight", "GuardOT_HouseMercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
