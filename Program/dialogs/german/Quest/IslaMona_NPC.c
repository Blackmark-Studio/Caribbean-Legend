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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Was brauchen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Sonst noch etwas, Kapitän?";
			link.l1 = "Nichts für jetzt...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha! Senor Hesucristo! Ehre sei Santiago dem Beschützer! Ehre sei der Jungfrau Maria! Wir sind gerettet! Ha-ha-ha!";
			link.l1 = "Spanier! Zu den Waffen!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Hallo. Ich verstehe, Sie haben Probleme? Wer sind Sie?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Also gut-beruhige dich. Es ist nur eine Angewohnheit.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Senor, mein Name ist Rodrigo Jimenez. Ich bin ein Vermesser und, durch des Schicksals Willen, der jefe dieser unglücklichen Menschen.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Wir... wurden hier gelandet. Aber, Senor, wir sind keine Verbrecher! Ha-ha-ha-ha!";
			link.l1 = "Was ist so lustig?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ach... Ich bitte um Verzeihung, Herr! Es ist all meine Anfechtung, seit meiner Kindheit lache ich, wenn ich sehr nervös bin. Ha.";
			link.l1 = "Und Sie wurden als Anführer ausgewählt?.. Gut. Die Leute landen nicht einfach so auf unbewohnten Inseln, senor. Möchten Sie das erklären? Ich gebe Ihnen nur eine Chance.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Entschuldigung, ich fürchte, ich habe Ihren Namen nicht verstanden, Herr. Sind Sie Engländer?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+". Ist das so wichtig? Lass uns meinen Namen vorerst nicht beachten.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "Tatsächlich, als Ketzer von der katholischen spanischen Kirche anerkannt, müssen wir vor dem gerechten Gericht der Heiligen Inquisition erscheinen. Deshalb ist uns Ihre Nationalität so wichtig. Ein spanischer Kapitän wäre verpflichtet, uns den örtlichen Behörden zu übergeben. So etwas würden wir nicht noch einmal überleben! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha! So ist unser Glück, na ja, wir haben sowieso nichts zu verlieren. "+dialog.text;
			link.l1 = "Nun, zum Glück für dich, die Angelegenheiten der Inquisition kümmern mich nicht. Also was? Seid ihr Heiden?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Nein, ich schwöre dir! Unsere Gemeinde war fünfzig Jahre lang in Handwerk und Handel in der glorreichen Stadt Cadiz tätig. Alles lief gut, wir erwarben sogar ein Schiff und eine Lizenz für den Handel mit den Kolonien unseres Reiches. Jetzt verstehe ich, dass wir damals eine Grenze überschritten und völlig unvorbereitet auf unsere neuen Wettbewerber... und ihre Methoden waren.";
			link.l1 = "Du hast den Handel nicht mit jemandem in Europa geteilt und als Ergebnis ist die ganze Gemeinschaft auf einer verlassenen Insel in der Karibik gestrandet? Und ich dachte, ich hätte Lebensprobleme...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Leider ist das der Fall. Unsere Gemeinschaft wurde von Juden gegründet, die zum neuen Glauben konvertierten und die Möglichkeit erhielten, nach Spanien zurückzukehren. Diese alte Geschichte reichte aus für Anschuldigungen und offizielle Untersuchungen.";
			link.l1 = "Und so bist du gerannt...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Ja! Ha-ha-ha! Auf unserem eigenen Schiff! Wir waren auf dem Weg nach Curacao, um ein neues Zuhause und ein neues Geschäft aufzubauen. Allerdings haben wir die Ausdauer der Inquisition unterschätzt und dafür teuer bezahlt. Ihr Kurier hat uns nicht weit von hier abgefangen und den Kapitän befohlen, uns nach Hause zurückzubringen...";
			link.l1 = "Verdammt!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Es gibt noch mehr! Ha! Unser Kapitän wollte sich nicht die Mühe machen, uns zurück über den Atlantik zu bringen oder uns unter seiner Verantwortung im nächsten Hafen freizulassen. Und, wie eine wahrhaft salomonische Entscheidung, gab er uns Essen, setzte uns hier ab, und das war's.";
			link.l1 = "Eine tragische Geschichte in der Tat, daran besteht kein Zweifel. Fassen wir zusammen: Du kannst nicht nach Hause zurückkehren, freundliche Kolonien werden dich verraten, und fremde Häfen werden dich auch nicht willkommen heißen - es gibt kein Ende des Krieges in dieser Region. Was sind Deine Pläne?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Sie haben ein so düsteres Bild gemalt, Herr, dass mir die Worte fehlen. Es ist, als gäbe es keinen besseren Ort für uns als diese Insel.";
			link.l1 = "Ich glaube nicht, es gibt eine bessere Insel.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Wirklich? Ist es Spanisch?";
			link.l1 = "Es ist meins. Durch Schicksal habe ich einen ehemaligen Piratenversteck auf einer unbewohnten Insel geerbt. Jetzt ist es meine Basis, und ich möchte sie erweitern, die Insel erkunden und wenn möglich, dort eine Fabrik bauen..";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Bist du ein Pirat?";
			link.l1 = "Ja.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Nein.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "Neue Welt! Tatsächlich, wir sind hier. Daheim sagen sie, Piraten seien echte Dämonen und nicht einmal Menschen. Sie fressen Kinder, vergewaltigen Frauen und ziehen guten Katholiken die Haut ab. Ist das wahr?";
			link.l1 = "Es hängt vom Wochentag ab. Lass uns ein anderes Mal darüber sprechen. Ich suche Leute. Fleißige und fähige Individuen, die bereit sind, mehrere Jahre weit weg von der Zivilisation zu leben. Würde dich so etwas interessieren?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Schade, da ich schon ein Verbrecher bin, würde ich gerne wenigstens einen Piraten sehen.";
			link.l1 = "Vielleicht bekommst du wieder so eine Gelegenheit. Lass uns ein anderes Mal darüber sprechen. Ich suche nach fleißigen und fähigen Personen, die bereit sind, einige Jahre fern von der Zivilisation zu leben. Wärst du an so etwas interessiert?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Wir haben keinen anderen Ausweg. Aber das ist eigentlich keine schlechte Option. Wir werden es akzeptieren, wenn Sie uns in Frieden leben und arbeiten lassen. Und versprechen Sie uns, uns eines Tages nach Hause zu schicken! Geben Sie uns Ihr Wort, Herr, und nennen Sie uns Ihren Namen..";
			link.l1 = "Ich, Kapitän "+GetFullName(pchar)+", gebe ich dir mein Wort. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! Wir sind gerettet! So sei es! Wir sind mehrere Familien, etwa 30 Leute. Alle sind gebildet, in Handwerken und Handel ausgebildet.";
			link.l1 = "Das Schicksal hat entschieden... Bitte komm an Bord!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Freut mich, Sie kennenzulernen, Senor Rodgar. Es scheint, als müssten wir lange zusammen leben und arbeiten... Meine Güte, wie erträgt man diese Hitze?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Wenn es Ihnen nichts ausmacht, werde ich einschreiten: Kapitän, geben Sie uns einen Tag, um uns einzuleben und schnell das Inventar und das Land zu inspizieren. Ich bin sicher, Senor Rodgar hat viele Ideen, was mit diesem Flecken Land zu tun ist. Ich denke, wir werden ein gutes Team sein.";
			link.l1 = "Du hast wirklich keine Wahl, Hymenese. Ha-ha.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Ja, Kapitän?";
			link.l1 = "Hymenese, gibt es gute Nachrichten für mich?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Kapitän, das ist ein Albtraum. Euer Haus ist natürlich nicht schlecht. Aber sonst... In diesen Hütten, umgeben von Wildwuchs, ist es unmöglich zu leben, und Senor Rodgar weiß nicht einmal, was am anderen Ende der Insel passiert!! Unglaublich! Ha-ha!";
			link.l1 = "Bist du nervös oder lachst du tatsächlich gerade darüber?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Natürlich, das ist lustig! Was haben sie all die Jahre gemacht? Zuerst müssen wir ein paar Häuser fertigstellen und diese Hütten in einen akzeptablen Zustand bringen. Die Leute müssen anständig leben können, um fleißig zu arbeiten. Außerdem werde ich die Piraten bitten, eine vollständige Erkundung der Insel durchzuführen. Vielleicht ist dieser Ort nicht nur reich an Felsen und Sand. Wenn alles erledigt ist, kann ich Ihnen genau sagen, was Sie mit diesem Land machen sollen.";
			link.l1 = "Klingt großartig! Was wird von mir verlangt?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materialien für Häuser, Möbel und provisorische Unterkünfte. Ich habe alles berechnet. Hier, nimm die Liste.";
			link.l1 = "Beeindruckend...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Wirklich? Herr, wir haben Kathedralen gebaut! Das ist beeindruckend....";
			link.l1 = "Ich bin geneigt, Ihnen zu glauben! Bauen Sie nur nicht aus Versehen eine Kathedrale hier. Muss ich jedes Mal viel Material hierher schleppen?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Nein, diese Materialien werden uns eine Weile erhalten, aber wir werden später noch einige Dinge bringen müssen. Wenn du solche Ärgernisse in der Zukunft vermeiden möchtest, bringe doppelt so viele Materialien.";
			link.l1 = "Nun, du hast mich überzeugt. Ich werde sehen, was ich tun kann. Irgendwelche Fristen?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Nein, Herr. Aber ich bitte Sie freundlich, nicht zu zögern - das ist die Arbeit, die erledigt werden muss, um die Dinge voranzubringen. Und die Leute brauchen auch einen Platz zum Leben. Laden Sie die Materialien ins Lager und vergessen Sie nicht, mich zu informieren, wenn alles bereit ist. Oh, ich habe fast vergessen! Sprechen Sie mit Herrn Rodgar über die Erkundung der Insel.";
			link.l1 = "Einverstanden!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Ja, Kapitän?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Hallo, Hymenez. Überprüfe das Lagerhaus.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Hallo, Hymenez. Meine Männer haben die ganze Insel durchsucht. Was sagst du?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Du hast diese Verantwortung mit Bravour gemeistert! Wenn du jemals in Cadiz bist, komm und arbeite für mich als Lagerverwalter!";
			link.l1 = "Ich bin auf dem Weg! Sag mir, Kamerad, was wirst du jetzt tun?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Herr Kapitän, lassen Sie uns zuerst mit dem Unterbringung und Versorgung befassen. Wir werden danach Pläne machen. Ich warte auf die Waren aus Ihrer Liste im Lagerhaus.";
			link.l1 = "Also gut, ich verstehe. Zuerst müssen wir Häuser bauen und diesen Ort aufräumen. Die Waren werden bald hier sein.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Kapitän, kümmern wir uns zuerst um Unterkunft und Vorräte. Wir können später Pläne machen. Ich warte im Lagerhaus auf die Waren aus Ihrer Liste. Und Ihr Piratenfreund wartet auch auf Proviant und Medizin.";
			link.l1 = "Verstanden, ich verstehe. Zuerst müssen wir Häuser bauen und diesen Ort aufräumen. Die Waren werden bald hier sein. Und auch für meinen Piratenfreund.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Geben Sie uns sechs Monate, Kapitän, und Sie werden diesen Ort nicht wiedererkennen.";
			link.l1 = "Sagst du, dass es in sechs Monaten weder dich, noch die Siedlung, noch die Materialien hier geben wird? Bis später!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Wir werden anfangen zu arbeiten, sobald Sie Ihre Geschäfte mit diesem Banditen geklärt haben. Er hat von Ihnen Proviant und Medizin verlangt, und ich stimme ihm zu - es ist eine vernünftige Forderung.";
			link.l1 = "Ich werde ihm deine Worte übermitteln.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Nun, Kapitän? Haben Sie alles getan, was Ihr Pirat gefragt hat?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "Ich habe alle Probleme mit Rodgar geklärt. Die Inselerkundung hat begonnen, Proviant und Medizin sind im Lager. Jetzt bist du dran.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Keine Sorge, wir werden es herausfinden. Ich kümmere mich darum.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Herr Kapitän! Was denken Sie? Ha-ha-ha?";
			link.l1 = "Es ist viel schöner. Bericht, Himenes!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Jetzt kannst du tatsächlich hier leben! Wir haben aufgeräumt und alle Häuser wiederaufgebaut, außer deinem, natürlich. Nicht sehr luxuriös, aber nicht schlechter als in unserem Belize.";
			link.l1 = "Belize gehörte schon lange zu England, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Ich bin nicht sicher, ob die Häuser davon wissen, Käpt'n, ha-ha!";
			link.l1 = "Nun hast du einen Ort zum Leben, und die Siedlung sieht menschlich aus. Was kommt als nächstes?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Schau dich um, sprich mit Senior Janssen und komm dann zu mir zurück. Wir werden die Ergebnisse der Inselerkundung und unsere Pläne besprechen.";
			link.l1 = "Seit wann nennst du Rodgar so? Warst du nicht ständig in Uneinigkeit?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "Und wir haben sie immer noch. Aber wir müssen irgendwie funktionierende Beziehungen aufbauen.";
			link.l1 = "Danke dir, Rodrigo. Ich komme bald zurück.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Kapitän. Senor Janssen.";
			link.l1 = "Los, erzähl mir von den Ergebnissen der Inselerkundung.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Ja, Kapitän. Einige Orte habe ich persönlich mit unserem Prospektor inspiziert. Nun, was soll ich sagen... Isla Mona ist eine arme, winzige und ziemlich uninteressante Insel. Es gibt sehr wenig Platz für den Bau, die Landschaft ist schwierig, steil, und es gibt fast kein fruchtbares Land. Drei Strände, eine überflutete Höhle, dichte Dickichte, ein paar Papageien, eine Herde Ziegen und wir...";
			link.l1 = "Bist du ernst? Sagst du, dass die wertvollste Ressource auf dieser Insel eine Herde Ziegen ist?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha! Ich würde fragen, Senor! Ha-ha! Sie haben mich nicht ausreden lassen!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Na gut, beruhige dich und mach weiter. Du weißt, ich habe viel in diesen Ort investiert.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "Und nicht umsonst! Es gibt genug frisches Wasser in der Höhle, es gibt genug Erde, um fruchttragende Bäume zu züchten, und Ziegen können gezüchtet werden. Mit Angeln und den Anstrengungen deiner Kameraden wird das Nahrungsproblem sehr schnell gelöst werden.";
			link.l1 = "Also, du musst hier kein weiteres Essen mitbringen? Nicht schlecht. Ich hatte gehofft, dass dieser Ort ohne meine ständige Fürsorge auskommen könnte. Lass uns weitermachen.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Sie haben in allem Recht, Senor. Aber das ist noch nicht alle Neuigkeiten! Zuerst hat Senor Rodgar die Idee gehabt, eine Taverne zu bauen. Ich weiß nicht, was es Ihnen bringen wird, aber dieser Schurke ist auf etwas aus.";
			link.l1 = "Er will sich betrinken, das ist es!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Zweitens, die Bucht des Gouverneurs stellte sich als viel tiefer heraus als wir ursprünglich dachten. Wir können einen vollwertigen Pier bauen.";
			link.l1 = "Ich verstehe nicht ganz, wie es mir nützen wird, aber das ist schon gute Nachrichten. Das ist nicht alles, hoffe ich?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Wir haben einen Hain aus Bacote-Bäumen gefunden. Ein idealer Ort für eine Fabrik.";
			link.l1 = "Du machst mich glücklich, Rodrigo! Tatsächlich, ausgezeichnete Neuigkeiten!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "Das ist alles für jetzt, Senor. Vielleicht haben wir in der Zukunft mehr Ideen. Sie verstehen, die besten Ideen kommen beim Arbeiten! Was möchten Sie fragen?";
			link.l1 = "Sag mir mehr über Bacote. Das klingt vielversprechend.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "Nach meiner Einschätzung wird eine kleine Fabrik in der Lage sein, dieses wertvolle Holz mehrere Jahre lang zu gewinnen. Die Reserven sind bescheiden, aber die Ressource ist strategisch. Wir können eine Stelle im Zentrum der Insel räumen und dort ein Haus mit einem Lagerhaus bauen. Das ist ein Anfang. Neben Baumaterialien werden wir auch etwa 15 Sets von Handschellen und Musketen benötigen.";
			link.l1 = "Und warum brauchen wir Handschellen? Und warum genau fünfzehn?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "Es ist harte Arbeit, Herr. Ich würde sogar sagen, es ist Sklavenarbeit.";
			link.l1 = "Ich verstehe. He-he...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Hast du den Verstand verloren? Ich werde kein Sklavenbesitzer!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "Und warum brauchen wir ein Musket? Und warum nur eins?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Ich stimme dem Piraten zu, senor. Ich verstehe Sie nicht, Kapitän. Die gesamte Wirtschaft dieser Region basiert auf Sklavenarbeit, und das wird noch viele Jahre so bleiben. Wie sind wir besser?";
			link.l1 = "Ich werde eine Entscheidung treffen. In der Zwischenzeit, sag mir, warum brauchst du ein Musket? Und warum genau eins?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Natürlich wird die Fabrik Wartung benötigen. Mit ihrem Bau wird diese Insel eine Wirtschaft haben, in der Sie der Hauptgeschäftspartner sind. Wir werden die Sklaven selbst ernähren, aber Sie werden Sicherheit und Produktion aus eigener Tasche bezahlen müssen. Siedler nehmen hundert Dublonen und fünf Flaschen Wein für jede Charge. Verhandeln Sie über Sicherheitsfragen mit Senor Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "vierzig Maßnahmen jeden Monat. Und das Gold ist für die Zukunft. Eines Tages wirst du uns von hier wegbringen, erinnerst du dich an dein Versprechen? Jede Arbeit muss bezahlt werden, und mit deinen Dublonen werden wir Jäger und Handwerker für ihre Arbeit in der Siedlung bezahlen. So werden wir Handel haben, und damit - Zivilisation!";
			link.l1 = "Das ist der Geist! In Ordnung! Für jetzt klingt alles überzeugend genug...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Was interessiert Sie noch?";
			link.l1 = "Also, was ist die Geschichte mit der Taverne? Warum kein Theater bauen?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Kapitän, ich habe ihn gewarnt, dass Ihnen die Idee des Hauses nicht gefallen würde. Aber es ist die einzige Option. Sie haben das größte Haus in... ähem, der Stadt, wir werden das Erdgeschoss in eine Halle umgestalten, Tische und eine Küche aufstellen. Wir werden Getränke und Essen in den Höhlen unter dem Haus lagern. Wir haben Leute zum Kochen und Musik machen. Das zweite Stockwerk bleibt Ihres, und wir werden es nicht anfassen. Wir werden all Ihre Sachen vom Erdgeschoss selbst nach oben bringen.";
			link.l1 = "In Ordnung. Was genau wird uns die Taverne bringen?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Wir werden etwas kulturelles Leben bekommen, und du wirst die Gelegenheit haben, etwa dreihundert Leute in Reserve mitten im Herzen der Karibik zu haben.";
			link.l1 = "Interessant... Ich werde darüber nachdenken.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Was interessiert Sie noch?";
			link.l1 = "Nun, was ist mit dem Pier?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "Es ist einfach. Wir werden die Bucht des Gouverneurs von Riffen befreien, Signalbeleuchtung installieren und einen Pier bauen. Senor Janssen behauptet, dass Sie in der Bucht drei Schiffe oder ein erstklassiges Schiff unterbringen können. Und es wird angenehmer für Sie sein, hierher zurückzukehren, ohne jedes Mal das Beiboot am Strand entlang zu schleppen.";
			link.l1 = "Das wäre schön.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Was möchtest du wissen?";
			link.l1 = "Das ist alles für jetzt. Ich komme wieder, wenn ich entscheide, was ich bauen soll.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Herr Kapitän, nehmen Sie dieses Dokument. Ich habe mir die Freiheit genommen, alle Details niederzuschreiben, um sie nicht dutzendmal zu wiederholen. Studieren Sie es, bringen Sie Materialien mit und stellen Sie die Aufgabe.";
			link.l1 = "Danke dir, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Herr Kapitän, wir brauchen 10 Sklaven, um in der Fabrik zu arbeiten - das habe ich Ihnen gesagt, haben Sie es vergessen?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Bereits geliefert. Entladen Sie sie und beginnen Sie mit der Produktion.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Meine Erinnerung ist intakt. Ich bringe sie bald.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Also, Senor Kapitän, was sagen Sie?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Ich will eine saubere Bucht und einen sicheren Pier. Das wird die Basis für meine Flotte sein.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Geh voran und baue die Taverne. Jeder wird es schätzen, und ich kann hier eine Reserve behalten.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Beginnen Sie mit dem Bau der Plantage. Es ist Zeit, die Investitionen zurückzugewinnen.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, die besonders wertvollen Spezialisten und Ausrüstungen wurden an die Fabrik geliefert. Du kannst anfangen zu arbeiten.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, ich bin wegen meinem Eisenholz gekommen.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, haben wir unseren großen Bau abgeschlossen?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, lass uns deine Kirche bauen.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, ich habe deine Kirchenartikel mitgebracht.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Nichts für jetzt...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Materialien sind verfügbar, alles ist bereit. Der Bau wird 4 Monate dauern.";
				link.l1 = "Du hast es nicht eilig, oder? Nun, viel Glück, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "Ich fürchte, es sind nicht genug Materialien im Lager. Bitte überprüfen Sie die Liste erneut.";
				link.l1 = "Ich kümmere mich darum.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Materialien sind verfügbar, alles ist bereit. Der Bau wird 3 Monate dauern.";
				link.l1 = "Du hast es nicht eilig, oder? Nun, viel Glück, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "Ich fürchte, es gibt nicht genug Materialien im Lager. Bitte überprüfen Sie die Liste erneut.";
				link.l1 = "Ich werde mich darum kümmern.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Materialien sind verfügbar, alles ist bereit. Der Bau wird 6 Monate dauern.";
				link.l1 = "Du hast es doch nicht eilig, oder! Viel Glück, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "Ich fürchte, es sind nicht genug Materialien im Lagerhaus. Bitte überprüfen Sie die Liste erneut.";
				link.l1 = "Ich kümmere mich darum.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Willkommen, Kapitän. Wie gefällt Ihnen Ihr neuer Hafen?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "Es ist dunkel, Rodrigo! Wir hätten fast deinen gelobten Pier zerstört! Gut, dass du ihn wenigstens erleuchtet hast!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Nicht schlecht, Rodrigo! Es scheint eine Kleinigkeit zu sein, aber es ist schön, auf diesen Planken zum Ufer zu laufen. Und die Bucht wurde leichter zu navigieren. Also, ich vermute, jetzt kann ich mehr Schiffe in dieser kleinen Bucht unterbringen?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Ja, Kapitän. Ich muss sagen, es erfüllt mich mit Stolz. Lassen Sie mich wissen, wie Sie unser großes Bauprojekt fortsetzen möchten.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Da wir gerade von Bau sprechen. Meine Fabrik sollte jetzt auch fertig sein. Stimmt's, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic! Käpt'n! Wir feiern hier!";
			link.l1 = "Rodgar. Rodrigo. Oh, verdammt!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Was ist los, K-k-kapitän? Gefällt Ihnen die Farbe der Wände nicht?";
			link.l1 = "Erst jetzt habe ich erkannt, dass ihr beide denselben Namen habt! Ha-ha-ha! Ein Spanier und ein Pirat, mit demselben Namen, haben eine Taverne auf einer verlassenen Insel gebaut und trinken zusammen, als würden die indischen Götter jeden verschlingen und die Welt bis zum Sonnenaufgang beenden! Ha-ha! Ich bin bei dir!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! So wahr! Treffer!";
			link.l1 = "Treffer!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Alles ist bereit. Sollen wir gehen? Lass mich dir deine Fabrik zeigen.";
			link.l1 = "Führe den Weg.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Kapitän, fast alles ist bereit, um den Betrieb aufzunehmen. Unterkünfte für die Arbeiter, Lagerhaus für Rohstoffe, Verarbeitungsbereich - eine würdige Fabrik wurde errichtet. Wir haben bereits die vielversprechendsten Bäume im Dschungel für die Holzfällerei markiert. Bringen Sie fünfzehn Arbeiter und das vereinbarte Inventar - 15 Fesseln und Musketen, und wir werden mit der Arbeit beginnen.";
			link.l1 = "Wir? Du meinst die Sklaven?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Sklave... Sklaven werden schneiden, Siedler werden verarbeiten und Piraten werden bewachen. Jeder wird Arbeit haben - du hast ein ernsthaftes Unternehmen begonnen, Kapitän.";
			link.l1 = "Fast wie das gelobte Land, hm. Warte auf die Ware, es ist Zeit für mich auf die Jagd zu gehen.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Ein trauriges Schicksal... Sie werden diesen Ort nie verlassen.";
			link.l1 = "Rodgar... Ich meine, Rodrigo! Erstens, sie könnten gehen. Und zweitens, wenn du jemand anders auf Terks triffst, wäre dein Schicksal nicht besser.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Ich weiß das sehr gut, Kapitän. Und ich vergesse es nicht. Lassen Sie mich Ihnen von dem Betrieb dieser Fabrik erzählen. Ab nächsten Monat, am fünfzehnten Tag, liefern wir vierzig verarbeitete Bacout-Logs. Natürlich müssen Sie nicht jeden Monat für jede Lieferung kommen - alle Chargen werden hier, in der Fabrik, gelagert und auf Sie warten.";
			link.l1 = "Also, ich kann mehrere Chargen auf einmal aufnehmen?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "In Maßen natürlich - bleib nicht zu lange weg. Die Leute werden nicht jahrelang ohne Bezahlung arbeiten, ohne zu wissen, ob ihr einziger Kunde noch lebt oder nicht. Ich denke, wir werden sechs Chargen liefern, bevor wir den Betrieb einstellen.";
			link.l1 = "Muss ich alle Waren auf einmal abholen? Und wie war das mit dem Preis, erinnere mich?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Ja, alles auf einmal. Der Preis für ein Standard-Bacout-Protokoll beträgt zehn Dublonen. Zusätzlich musst du für jede Charge fünf Flaschen guten Rum und die gleiche Anzahl von Weinflaschen abgeben. Rodgar behauptet, dass du solche Preise nirgendwo anders auf der Welt finden wirst.";
			link.l1 = "Allerdings, ich stimme zu! Danke, Rodrigo. Lasst uns an die Arbeit gehen!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Ausgezeichnet! Jetzt fangen wir wieder an zu arbeiten!";
			link.l1 = "Gut.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Natürlich, Kapitän, nehmen Sie es. Wir haben die folgenden Chargen für das nächste Datum bereit: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", das ist "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" Protokolle. Daher schulden Sie uns "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" Dublonen, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" Flaschen Rum, und "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" Flaschen Wein, hast du das alles?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Natürlich. Hier ist deine Bezahlung.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Es scheint, ich habe nicht alles. Ich bringe es sofort.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Ausgezeichnet. Wir transportieren den Bacout von der Fabrik zu Ihrem Lagerhaus, von wo aus Sie ihn abholen können, wann immer Sie wollen.";
				link.l1 = "Großartig. Bereite die nächste Ladung vor.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Halt ein, Kapitän! Dein Lagerhaus ist voll - wir werden nicht in der Lage sein, den gesamten geernteten Bacout dort zu laden. Räume etwas Platz im Lagerhaus frei - dann komm zurück zu mir.";
				link.l1 = "Gut, ich kümmere mich darum.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Natürlich, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Kapitän, ich fürchte, alles andere zu bauen wäre unnötige Torheit und Verschwendung. Es sei denn...";
			link.l1 = "Außer was?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Kapitän, es ist mir unangenehm, danach zu fragen... Sie haben bereits eine riesige Summe in diesen Ort investiert!";
			link.l1 = "Ein Bordell?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Eine Kirche?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Ich schwöre bei Sankt Santiago, das wäre nicht schlecht! Aber in der ersten Nacht würden unsere Frauen es niederbrennen. Zusammen mit uns. Nein, Kapitän, ich spreche von einer Kirche. Ja, wir haben anständige Unterkünfte und Bezahlung, das Meer und Unterhaltung, Familien und Freunde. Aber dennoch fehlt etwas, verstehst du?";
			link.l1 = "Ich kann es mir vorstellen.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Sie durchschauen mich, Kapitän. Ja, wir haben anständige Unterkünfte und Bezahlung, das Meer und Unterhaltung, Familien und Freunde. Aber trotzdem fehlt etwas, verstehen Sie?";
			link.l1 = "Ich kann es mir vorstellen.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Genau. Ohne deine Hilfe können wir das Haus Gottes nicht bauen. Ein solcher Ort muss besonders sein, er muss nicht von dieser Welt sein. Und daher sollte es teuer sein. Wir werden Kerzen, Goldbarren, Bernstein und natürlich Baumaterialien benötigen, und keine billigen. Es wird dir keinen Gewinn bringen, also wage ich es nicht zu fragen.";
			link.l1 = "Also, müssen Sie einen Priester hierher bringen?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Nein.";
			link.l1 = "Habt ihr schon einen Priester bei euch?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Nein, Kapitän. Und ich denke, du verstehst schon alles.";
			link.l1 = "Also, hatten die heiligen Väter von der Inquisition einen Grund, euch zu verfolgen? Seid ihr Ketzer?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Nach kanonischem Recht sind wir die schlimmsten Ketzer. Wir glauben nicht, dass die Kommunikation mit Gott unbedingt einen Vermittler aus dieser Welt erfordert.";
			link.l1 = "Aus dieser Welt?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Kapitän, wir sind keine Satanisten und unsere Gemeinschaft ist keine Sekte. Wir sind Christen, genau wie Sie, aber wir sehen die Dinge mit einer sehr weitreichenden Sichtweise. Zu weit, laut einigen sehr gebildeten und würdigen Leuten. Solltest du jemals in deinem Herzen Platz für Offenheit und Verständnis finden, dann werde ich dir mehr erzählen. Aber für jetzt, nimm einfach diese Liste. Nur für den Fall.";
			link.l1 = "Du hättest mir früher davon erzählen sollen, Rodrigo. Ich möchte nicht eines schönen Tages zurückkommen und auf meinem Land eine Hexensabbat oder die Geburt eines neuen Glaubens sehen! Während du wartest - werde ich eine Entscheidung treffen.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Beeindruckende Liste. Ich beginne zu verstehen, warum die heiligen Väter so viel Geld brauchen! Ich werde über dein Angebot nachdenken, Rodrigo, und eine Entscheidung treffen.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Wenn es positiv ist, bringe ich alle Waren von Ihrer Liste ins Lager und lege die Schätze für Sie auf den Tisch.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Wenn es positiv ist, bringe ich alle Waren von Ihrer Liste ins Lager und lege die Schätze für Sie auf den Tisch.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "Im Namen unserer gesamten Gemeinschaft danke ich Ihnen, Kapitän. Sie werden es nicht bereuen, das schwöre ich!";
			link.l1 = "Ich werde es nur bereuen, wenn du etwas völlig schäbiges baust.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Kapitän, alle Baumaterialien sind auf Lager! Wir beginnen mit dem Bau, sobald Sie die aufgelisteten Luxusartikel mitbringen. Sie werden für Schmuck und rituelle Werkzeuge verwendet. Nochmals vielen Dank, Kapitän! Muchas gracias!";
			link.l1 = "Bitte sehr!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Vielen Dank, Kapitän! Alles ist bereit, wir beginnen mit dem Bau. Kommen Sie in ein paar Monaten zur ersten Inspektion zurück. Oh, und noch eine Sache, die Trauben sind reif! Wir werden hausgemachten Wein herstellen, eine Feier veranstalten und zu Ihren Ehren ein Festmahl geben!";
				link.l1 = "Ich denke, wir alle verdienen eine Feier. Ich werde in zwei Monaten zurück sein.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Kapitän, es gibt noch "+sAdd+" links.";
				link.l1 = "Sicher, gib mir bitte noch etwas Zeit. Ehrlich gesagt, wenn es nicht für die Kerzen wären, würde ich denken, dass du einen Schatz begraben willst.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Und hier dachte ich, du hättest dich von dieser idiotischen Angewohnheit befreit.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. Das dachte ich auch, Kapitän! Rodgar hat recht, deine Anwesenheit bedeutet bereits, "+sTemp+"";
			link.l1 = "Ich weiß bereits, was passiert ist. Gibt es Verluste?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Mach dir nicht so viele Sorgen, Rodgar. Es ist nicht deine Schuld, die Füsiliere kamen zu schnell. Wir hätten sie sowieso nicht hinter unseren Linien halten können, und es war keine Zeit, sie alle mit dem Schwert zu erledigen.";
			link.l1 = "Was ist mit den Spaniern?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Nur drei von ihnen haben es zu uns geschafft, und nur einer hat überlebt. Der Kapitän selbst! Anscheinend ein sehr ernsthafter Militärsegler. Aber er kann uns noch nicht helfen - er muss mindestens noch ein paar Tage im Bett bleiben. Übrigens, Kapitän, wir haben Schüsse gehört und nach Ihrem Aussehen zu urteilen, Sie auch.";
				link.l1 = "Man könnte sagen, dass. Die ungebetenen Gäste haben offensichtlich keinen so unerwarteten Besuch erwartet und wurden zurück ins Meer geworfen.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Nur drei von ihnen haben es zu uns geschafft, und nur einer hat überlebt. Der Kapitän selbst! Anscheinend ein sehr ernsthafter Militärseemann. Aber er kann uns noch nicht helfen - er muss mindestens noch ein paar Tage im Bett bleiben.";
				if (i >= 50) 
				{
					link.l1 = "Letztes Mal habe ich hier ziemlich viele meiner Leute zur Wache zurückgelassen, also sollte es viel mehr von euch als Füsiliere geben. Warum habt ihr sie nicht einfach alle auf einmal ins Meer zurückgeworfen?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Gut, lass uns dieses Problem lösen. Der Plan ist folgender: Ich werde sie zu einem offenen Angriff herauslocken, und zwar sofort. Es hat keinen Sinn, zu zögern. Bereitet euch mit Schrot und Musketen vor, Piraten an den Toren, der Rest bleibt zu Hause - und hält die Stellung.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Käpt'n, sie sind alle professionelle Soldaten, mit einem Kommandeur. Und wir haben nicht einmal ordentliche Waffen. Ja, natürlich, wir hätten sie mit zahlenmäßiger Überlegenheit überwältigen können, aber wir hätten mindestens doppelt so viele Leute verloren, und jede Person ist hier kostbar und benötigt.";
			link.l1 = "Gut, lösen wir dieses Problem. Der Plan ist folgender: Ich werde sie zu einem offenen Angriff herauslocken, und zwar sofort. Es hat keinen Sinn, zu zögern. Macht euch bereit mit Schrot und Musketen, Piraten vor den Toren, der Rest bleibt zu Hause - und hält die Stellung.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Kapitän, wir sind bereit zu kämpfen!";
			link.l1 = "Ich weiß, Rodrigo. Aber du hast mich nicht ausreden lassen: Wenn auch nur ein Feind es schafft, die Tore zu durchbrechen, müsst ihr alle von allen Seiten auf ihn losstürzen. Und im Kampf sinken eure Chancen, eine Kugel oder einen Splitter abzubekommen. Noch weitere Fragen?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Gut gemacht! Es ist natürlich unangenehm, dass ein so unglückliches Schicksal Ihren Landsleuten widerfahren ist. Aber ich bin dankbar, dass Sie wieder einmal auf unserer Seite stehen.";
			link.l1 = "Es war nicht einfach, Rodrigo. Normale Leute würden es Verrat nennen, und sie hätten recht.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Dies ist mein Land, Rodrigo. Es muss immer und egal von wem verteidigt werden.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Ja, der alte Rodrigo hat nicht erwartet, als er Cadiz verließ, dass ihn in der Neuen Welt solche Abenteuer erwarten würden.";
			link.l1 = "Sag es mir nicht. Manchmal habe ich immer noch genau die gleichen Gedanken.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "Es ist natürlich unangenehm, dass ein so unglückliches Schicksal Ihre Landsleute ereilt hat. Aber ich bin dankbar, dass Sie wieder einmal auf unserer Seite stehen.";
			link.l1 = "Es war nicht einfach, Rodrigo. Normale Menschen würden es Verrat nennen, und sie hätten recht.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "Dies ist mein Land, Rodrigo. Es muss immer und egal von wem verteidigt werden.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Ich verstehe, Kapitän. Erlauben Sie mir dann, Ihnen einen kurzen Überblick über die Situation in unserer Siedlung während Ihrer Abwesenheit zu geben.";
			link.l1 = "Wirklich? Warte mal... Kapitän?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Ich verstehe, Kapitän. Lassen Sie mich Ihnen dann einen kurzen Überblick über die Situation in unserer Siedlung während Ihrer Abwesenheit geben.";
			link.l1 = "Wirklich? Warte mal... Kapitän?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Habe nicht vor zu beleidigen. Es ist nur so, dass Rodgar dieses Wort so köstlich ausspricht, dass ich es auch versuchen wollte. Sehr... Piratenhaft.";
			link.l1 = "Kein Problem, nur überrascht. Was ist hier passiert?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Zuerst haben wir die Kirche erbaut. Es wird einen Moment dauern, komm rein. Es gibt etwas zu sehen. Du hast eine große Tat vollbracht, Kapitän. Es mag dir vielleicht nicht so vorkommen, aber für uns ist die Kommunikation mit Gott sehr, sehr wichtig. Von diesem Tag an nennen wir Isla Mona unser hogar.";
			link.l1 = "Hogar, süßes Hogar? Ich werde definitiv einen Blick darauf werfen. Habe ich all diese Kerzen umsonst getragen?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Nicht umsonst! Zweitens, die Fabrik wurde ruiniert - wir haben die gesamte Arbeitskraft verloren. Du wirst eine neue Charge Sklaven bringen müssen. Glücklicherweise haben wir nach einer Neubewertung der Arbeitseffizienz festgestellt, dass zehn Sklaven mehr als ausreichend sein werden. Also, weniger Ärger für dich.";
			link.l1 = "In Ordnung. Noch etwas?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Alles ist bereit für die Feier. Nun, fast: wir müssen hier aufräumen, die Körper der unglücklichen Seelen begraben... Also komm morgen in die Kirche und wir werden beginnen.";
			link.l1 = "Zur Kirche? Seltsamer Ort, um die Party zu beginnen. Planst du einen Antrag zu machen, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! Nein, Kapitän, obwohl einige unserer Mädchen nichts dagegen hätten. Es macht uns nichts aus, wenn Sie es tun.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Einverstanden, wir kommen morgen zur Kirche. Zum Beten, natürlich.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "Und noch eine Sache, Kapitän. Bevor die Feier beginnt, kümmern Sie sich zuerst um den Gefangenen. Die Entscheidung muss getroffen werden, und ich verstehe, dass es sowieso unangenehm sein wird.";
			link.l1 = "In Ordnung. Ich gehe jetzt gleich.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Alle sind hier! Senor, wir wissen nicht, was Sie ursprünglich von diesem Ort wollten und wie Sie ihn jetzt für sich selbst sehen. Für uns war es zunächst ein erzwungenes Refugium und ist jetzt zu einem echten Zuhause geworden. Ihre Seeleute, Piraten und geflohenen spanischen Häretiker leben hier. An jedem anderen Ort auf der Erde hätten wir uns schon längst die Kehlen durchgeschnitten. Aber hier sind wir Freunde, arbeiten und genießen das Leben. Isla Mona ist für keinen von uns der Endpunkt auf der Karte dieser Welt, aber vielleicht werden wir hier die glücklichsten und fruchtbarsten Jahre unseres Lebens verbringen. Und das ist Ihr Verdienst, Ihr Land und Ihr Volk. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Also gut, also gut. Kapitän, wir haben Geschenke für Sie gesammelt - eine Vielzahl von nützlichen und einfach angenehmen Dingen. Einige haben wir mitgebracht, und einige haben wir selbst gemacht. Nehmen Sie dieses Geschenk mit reinem Herzen an, und den Rest geben wir Ihnen mit unserer harten Arbeit.";
			link.l1 = "Danke dir... Das habe ich nicht erwartet. So wenige helle Momente und einfache Menschlichkeit in meiner Odyssee... Es bedeutet mir viel, glaub mir.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "Und jetzt - zurück zur Arbeit!";
			link.l1 = "Nein, jetzt geht's - zur Taverne! Rodrigo, lass uns gehen!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Ja, lass uns diesen wunderbaren Moment noch ein wenig länger genießen.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hic!";
			link.l1 = "Übrigens, ich sehe, dass du fast aufgehört hast, wild über alles und nichts zu lachen. Die frische Luft der Karibik?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Mehr wie Rodgars korrupter Einfluss. Ihn beobachtend, lernte ich, alles zum Teufel zu schicken.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Ich kenne viele respektable Leute von dort.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Nein, ich trinke lieber weiterhin Rum und starre dich an.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Kapitän! Hicks!";
			link.l1 = "Hallo auch dir, Rodrigo. Hattest einen ereignisreichen Abend, sehe ich?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Besser... frag nicht. Einen Monat... werde nicht trinken. Oh. Ich habe Neuigkeiten! Der Kapitän...er kam zu sich.";
			link.l1 = "Der einzige überlebende Spanier?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hicks! Au! Ja, sie haben ihn in die Factoria gebracht, in ein Haus unter Bewachung.";
			link.l1 = "Richtig. Ich werde zu ihm gehen. Pass auf, dass du es nicht übertreibst.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "Ich bin schwimmen gegangen und alles ist wie neu! Wir werden leben und arbeiten. Ich werde versuchen, die Factoria so lange wie möglich zu betreiben. Nun, und Reparaturen durchführen, kleinere Bauarbeiten. Vielleicht sogar mit meiner über Kinder entscheiden.";
			link.l1 = "Froh für euch alle! Es war ein sehr nervenaufreibendes, kostspieliges... und wunderbares Abenteuer, und ich bin froh, dass es für uns geklappt hat. Viel Glück an alle, und an die von uns, die in See stechen, noch mehr Glück!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Halt! Korporal "+GetFullName(npchar)+". Sie sind in einer Kampfzone gelandet! Identifizieren Sie sich sofort und nennen Sie den Grund Ihrer Anwesenheit hier!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Unteroffizier, treten Sie zurück! "+GetFullName(pchar)+", Kapitän der französischen Marine. Ich befehle Ihnen, mich zu Ihrem Vorgesetzten zu eskortieren. Führen Sie den Befehl aus!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", Kapitän des Schiffes namens '"+pchar.ship.name+"'. Kam ganz zufällig auf dieser Insel an - für mögliche Reparaturen und um die Vorräte an frischem Wasser aufzufüllen.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Ja, Herr Kapitän! Bitte folgen Sie mir. Ich bitte Sie nur, seien Sie vorsichtig! Diese Insel wimmelt von Banditen.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Verzeihung, Kapitän. Sie tragen keine Uniform, daher bin ich verpflichtet, Ihr Offizierspatent zu überprüfen.";
				link.l1 = "Sehen. Zufrieden? Jetzt - beeilen Sie sich, den Befehl auszuführen, Korporal!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Sie müssen mit mir kommen, Kapitän. Unser ranghöchster Offizier wird mit Ihnen sprechen. Von diesem Moment an wird Ihr Schiff vorübergehend für die Bedürfnisse der französischen Marine requiriert. Benachrichtigen Sie sofort die aktuelle Wache und folgen Sie mir.";
			link.l1 = "Das Schiff Charle Prince requirieren? Ich glaube nicht!";
			link.l1.go = "Capral_5";
			link.l2 = "Sieht so aus, als hätte ich keine Wahl. Ich werde tun, was du sagst.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Herr Kapitän, der Weg zum feindlichen Lager liegt zu unserer Rechten. Ich werde Sie begleiten.";
				link.l1 = "Tritt zurück, Korporal. Ich gehe lieber allein.";
			}
			else
			{
				dialog.text = "Kapitän, der Weg zum feindlichen Lager liegt zu unserer Rechten. Du wirst dich nicht verirren.";
				link.l1 = "Danke für Ihre Besorgnis.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Kapitän "+GetFullName(pchar)+"! Gott sei Dank! Darf ich mich vorstellen - Leutnant "+GetFullName(npchar)+". Ein großer Bewunderer von Ihnen! Ich weiß nicht, was Sie auf diesem elenden Stück Land tun, aber Sie sind gerade rechtzeitig!\nIch muss sagen, Kapitän, Sie sind sehr beliebt geworden unter unseren Offizieren. Obwohl viele von Ihrem ... 'besonderen' Dienststil genervt sind, stimmen alle zu, dass Ihr Patent unsere Flotte stärker macht. Wir befinden uns derzeit in einer völlig festgefahrenen Situation, daher wird die Hilfe von jemandem wie Ihnen schwer zu überschätzen sein!";
				link.l1 = "Was kann ich tun? Und was geht hier vor?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Kapitän "+GetFullName(pchar)+". Ihr Name wurde mehrmals in den Flottenberichten erwähnt. Und immer in einem sehr zweifelhaften Licht. Jedoch haben Sie jetzt die Chance, diesen weniger ehrenhaften Trend zu unterbrechen und der Heimat zu dienen.";
				link.l1 = "Was kann ich tun? Und was passiert hier?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Wir waren auf der 'Krieger', eine Routine-Mission - Jagd auf besonders kühne spanische Räuber. Der Fall ist im Allgemeinen sehr einfach: der Spion liefert das Gebiet und Daten zur Zielperson und du fängst sie vom Horizont ab. Es gibt nichts Besonderes zu erzählen, und es endete alles sehr schlecht: die Spanier fanden uns zuerst und griffen an, obwohl sie selbst auf einer Korvette waren. Hätten wir etwas Ernsteres gehabt, wären wir nicht mit uns zum Grund gegangen... aber zumindest gelang es uns, ihren ganzen Rumpf zu sprengen. Nur meine Truppe überlebte. Die Kastilier hatten jedoch auch jemanden, der überlebte. Aber nicht für lange, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "Die Fregatte 'Krieger'? Kapitän Shocke ist gestorben?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Es überrascht mich nicht, dass Sie nach ihm gefragt haben, Kapitän. Ich habe von Ihrer Beteiligung bei der Abfangung der 'Alcantara' gehört. Eine große Leistung, schon damals haben Sie den Grundstein für Ihr Patent gelegt! Kommandant Shocke ist nicht gestorben, ganz im Gegenteil! Er wurde befördert und auf seinen Wunsch hin in das Mittelmeer versetzt. Wir können ihm in unserer jetzigen Situation nur beneiden. Also, eigentlich, über unsere Situation...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Wir haben eine Siedlung auf der Insel gefunden - eine ziemlich bevölkerte Banditenhöhle für - hör nur - Piraten und Spanier. Unglaublich! Du weißt, normalerweise schneiden und hängen sich diese Bastarde nur gegenseitig auf, aber hier - sieh mal: im Zentrum des Archipels arbeiten sie wie eine Familie zusammen, um Freibeuterholz zu gewinnen. Hast du den Pier gesehen, den sie für sich selbst gebaut haben? Gäste kommen nicht mit Ruderbooten zu dieser Rasse. Unsere Aufgabe ist äußerst klar: Mit deiner Hilfe erobern wir die Siedlung, nehmen das Freibeuterholz und Gefangene, und du bringst alle nach Capsterburg. In der Zwischenzeit werden die Behörden die Dinge für sich selbst klären... Und während sie es klären, werden wir uns um das Freibeuterholz kümmern und ordentlich mit anderen Offizieren aus meiner Heimatsquadron feiern!";
			link.l1 = "Was hat Sie bisher daran gehindert, die Siedlung selbst in Besitz zu nehmen?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "Was hat uns aufgehalten?! Wir haben nur zwölf Füsiliere und sieben Matrosen. Alle müde und erschöpft. Wir haben nur fünf Musketen gerettet, mit höchstens einer Patrone jeder! "+sTemp+"";
			link.l1 = "Aber hast du einen Plan?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Hör zu, wir haben keine Zeit verschwendet. Zuerst haben wir diese Fabrik übernommen und dadurch einige Lebensmittel- und Wasservorräte erbeutet und am wichtigsten - ein vollgepacktes Lager mit Freibeuterholz und mehr als ein Dutzend Sklaven! Wir hätten die Sklaven sowieso nicht bewachen können, also haben wir sofort eine Kampferkundung durchgeführt und sie dazu gebracht, ihre ehemaligen Herren unter dem Schutz unserer Musketen anzugreifen. So haben wir herausgefunden, dass die Banditen eine Waffe auf Lager haben.";
			link.l1 = "Verstehe ich richtig, dass Sie mich und meine Männer jetzt damit beauftragen wollen, uns um diese Waffe zu kümmern, anstatt um die Sklaven?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Nein, aber du kannst zu den Banditen als Vermittler gehen. Deine Ankunft bedeutet, dass ihr Versteck enttarnt ist, und nun haben die Soldaten des Königs ein Schiff und Verstärkung. Nun, während sie Ohren hängen lassen und die Tiefe ihrer Situation einschätzen, wirst du dich so nah wie möglich an das Geschütz heranwagen, eine Handgranate darunter werfen und dich nicht töten lassen, bis unsere Leute und deine Leute herankommen. Wenn du dir nicht sicher bist, ob du das schaffen kannst, versuche, einen deiner Männer anstelle von dir zu schicken.";
			link.l1 = "Lass mich zuerst ohne eine Bombe zu ihnen gehen und ihnen anbieten, sich zu ergeben. Ich werde mich umsehen, ihre Stimmung und Stärke verstehen, Zweifel in ihren Seelen säen. Wenn sie sich nicht ergeben, dann gehe ich wieder zu ihnen, aber mit einer Bombe.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... und zu diesem Zeitpunkt werden sie sich bereits an dich gewöhnt haben, also wird es einfacher sein, die Sabotage durchzuführen! Klug! Nun, ich habe nichts anderes von dir erwartet, Kapitän. Fahren Sie fort, wenn Sie bereit sind. Aber trotzdem, hier... Es könnte nützlich sein.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... und zu diesem Zeitpunkt werden sie sich bereits an dich gewöhnt haben, so dass es einfacher sein wird, die Sabotage durchzuführen. Das werden wir tun. Mach weiter!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Es gab eine ausgedehnte Schlacht mit den Spaniern in dieser Gegend. Beide Schiffe gingen unter und die Überlebenden landeten hier. Überwiegend Franzosen, aber einige unserer Feinde haben es auch geschafft zu überleben. Und Sie müssen nicht mehr wissen, entschuldigen Sie, Kapitän. Geheime Informationen, Sie verstehen.";
			link.l1 = "Verstanden.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Wir haben eine Siedlung auf der Insel gefunden - ein ziemlich bevölkertes Banditennest für - hör nur - Piraten und Spanier. Unglaublich! Du weißt, normalerweise schlachten und hängen sich diese Bastarde nur gegenseitig auf, aber hier - sieh nur: im aller Herzen des Archipels arbeiten sie zusammen wie eine Familie, um Freibeuterholz zu gewinnen. Hast du den Steg gesehen, den sie für sich gebaut haben? Gäste kommen nicht mit Ruderbooten zu dieser Brut. Unsere Aufgabe ist äußerst klar: Mit deiner Hilfe erobern wir die Siedlung, nehmen das Freibeuterholz und die Gefangenen, und du bringst alle nach Capsterburg. In der Zwischenzeit werden sich die Behörden selbst um die Dinge kümmern... Und während sie das herausfinden, bin ich vielleicht sogar bereit, dir die Gelegenheit zu geben, etwas wertvolles Holz für deine Bedürfnisse zu nehmen.";
			link.l1 = "Was hat Sie daran gehindert, die Siedlung bis jetzt alleine einzunehmen?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Hier bist du! Gibt es Neuigkeiten?";
			link.l1 = "Ist das eine Ehrengarde?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Offensichtlich wird in Kürze eine Entscheidung über unsere weiteren Aktionen getroffen. Ich möchte nicht meine Leute über die ganze Insel suchen, um neue Befehle zu erteilen.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Ausgezeichnete Initiative! Sie erhalten Ihre Befehle. Ich habe Aufklärung betrieben: der Feind ist schwach und die Kanone hat keine Munition mehr. Ich befehle Ihnen, das Banditennest sofort anzugreifen, Leutnant. Hören Sie auf, Ihre Hände zu pflegen. Nur ein weiterer Tag in der Flotte. Führen Sie aus!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "Meiner Meinung nach hätten wir sie gleich nach der 'Sklaven'-Aufklärung mit Gewalt nehmen können. Ihre Verteidigung ist lächerlich, nur ein paar ernsthafte Kämpfer. Nicht zu viel nachdenken - wir hätten schon den Trophäenwein trinken können, während wir auf einem Berg aus Eisenholz sitzen.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Jawohl, Kapitän!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "Und das sind die Ergebnisse Ihrer Aufklärung? Ich verstehe, dass es seltsam sein könnte, zu viel von einer nicht-militärischen Person zu erwarten, aber ich brauche Fakten! Fakten, Kapitän, nicht Ihre Meinung!";
			link.l1 = "Sie beleidigen mich, Leutnant. Meldung!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Gerade jetzt gibt es einen überlebenden Kapitän eines spanischen Schiffes, das ihr versenkt habt. Ein erfahrener Befehlshaber, der sich bald erholen wird. Wenn ihr zögert, wird er sich erholen und die Verteidigung nach dem Buch der Militärwissenschaft organisieren, und dann werden wir eine harte Zeit haben. Wir müssen uns beeilen - ich wiederhole, sie sind schwach und demoralisiert.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Verstärkungen kommen bald - um das Piratenholz zu nehmen. Ich glaube nicht, dass es ein Bluff ist: Du hast selbst die Docks und einen Haufen lieferbereiter Waren im Fabriklager gesehen. Wir müssen uns beeilen - ich wiederhole, sie sind schwach und demoralisiert. Wenn du zögerst, wirst du auf die Ankunft eines Piratenschiffes warten.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Fast die Hälfte der Bewohner dieses Lochs sind Frauen. Du hast nicht einmal gegen die Miliz gekämpft: Es waren nicht mehr als ein Dutzend Kämpfer die ganze Zeit gegen dich. Sie sind schwach und demoralisiert.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Denken Sie an die Trophäen und den Ruhm, Leutnant! Ein alleiniger Sieg über einen spanischen Plünderer, die Eroberung eines Banditennestes und eine einzigartige Quelle für Seeräuberholz - all das verlangt nach Ihrem eigenen Schiff! Ich wiederhole, sie sind schwach und demoralisiert, es ist Zeit, sie zu zerschlagen!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das sind wertvolle Informationen, und Sie hatten recht, es besteht kein Grund, hier zu zögern. Meine Männer sind alle hier, wir sind stark, ausgebildet und bereit. Alles wird in einer halben Stunde vorbei sein. Kapitän, bereiten Sie sich bitte darauf vor, Menschen, Gefangene und Fracht auf Ihrem Schiff zu empfangen. Wir werden hier nicht lange verweilen.";
				link.l1 = "Alles ist bereit, Leutnant. Wir haben nur auf Sie gewartet. Bis später!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information. In diesem Fall, geh zum Dock und bereite dein Enterkommando vor. Wir werden gemeinsam und sofort das Räubernest stürmen. Die Besten meiner und deiner Männer werden die Vorhut führen - sie werden diejenigen sein, die die Tore erobern. Den Rest besprechen wir nach der gemeinsamen Überprüfung unserer Kräfte. Enttäusch mich und dein Land nicht, "+GetFullName(pchar)+".";
				link.l1 = "...So sei es. Bis später, Leutnant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information, und Sie hatten recht, es gibt keinen Grund hier zu verweilen. Meine Männer sind alle hier, wir sind stark, ausgebildet und bereit. Alles wird in einer halben Stunde vorbei sein. Kapitän, bitte bereiten Sie sich darauf vor, Leute, Gefangene und Fracht auf Ihrem Schiff zu empfangen. Wir werden hier nicht lange verweilen.";
				link.l1 = "Alles ist bereit, Leutnant. Wir haben nur auf Sie gewartet. Bis später!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information. In diesem Fall, begeben Sie sich zum Dock und bereiten Sie Ihr Enterteam vor. Wir werden zusammen und sofort das Banditennest stürmen. Die Besten meiner und Ihrer Männer werden die Vorhut anführen - sie werden diejenigen sein, die die Tore erobern. Den Rest besprechen wir, nachdem wir gemeinsam unsere Kräfte inspiziert haben. Enttäuschen Sie mich und Ihr Land nicht, "+GetFullName(pchar)+".";
				link.l1 = "...So sei es. Bis später, Leutnant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information, und Sie hatten recht, es besteht keine Notwendigkeit hier zu verweilen. Meine Männer sind alle hier, wir sind stark, ausgebildet und bereit. Alles wird in einer halben Stunde vorüber sein. Kapitän, bereiten Sie sich bitte darauf vor, Menschen, Gefangene und Fracht auf Ihrem Schiff aufzunehmen. Wir werden hier nicht lange verweilen.";
				link.l1 = "Alles ist bereit, Leutnant. Wir haben nur auf Sie gewartet. Bis später!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Danke Ihnen, Kapitän. Das sind wertvolle Informationen. In diesem Fall, begeben Sie sich zum Dock und bereiten Sie Ihr Enterteam vor. Wir werden gemeinsam und sofort das Banditennest stürmen. Die Besten meiner und Ihrer Männer werden die Vorhut anführen - sie werden diejenigen sein, die die Tore erobern. Den Rest besprechen wir, nachdem wir unsere Kräfte gemeinsam inspiziert haben. Enttäuschen Sie mich und Ihr Land nicht, "+GetFullName(pchar)+".";
				link.l1 = "...So sei es. Bis später, Leutnant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das sind wertvolle Informationen, und Sie hatten recht, es gibt keinen Grund, hier zu zögern. Meine Männer sind alle hier, wir sind stark, ausgebildet und bereit. Alles wird in einer halben Stunde vorbei sein. Kapitän, bereiten Sie bitte vor, Menschen, Gefangene und Ladung auf Ihrem Schiff zu empfangen. Wir werden hier nicht lange verweilen.";
				link.l1 = "Alles ist bereit, Leutnant. Wir haben nur auf Sie gewartet. Bis später!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information. In diesem Fall, begeben Sie sich zum Dock und bereiten Sie Ihr Enterkommando vor. Wir werden das Banditennest gemeinsam und sofort stürmen. Die Besten meiner und Ihrer Männer werden die Vorhut anführen - sie werden es sein, die die Tore erobern. Den Rest besprechen wir, nachdem wir gemeinsam unsere Truppen inspiziert haben. Enttäuschen Sie mich und Ihr Land nicht, "+GetFullName(pchar)+".";
				link.l1 = "...So sei es. Bis später, Leutnant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das ist wertvolle Information, und Sie hatten recht, es gibt keinen Grund, hier zu verweilen. Meine Männer sind alle hier, wir sind stark, trainiert und bereit. Alles wird in einer halben Stunde vorbei sein. Kapitän, bitte bereiten Sie sich darauf vor, Menschen, Gefangene und Ladung auf Ihrem Schiff zu empfangen. Wir werden hier nicht lange verweilen.";
				link.l1 = "Alles ist bereit, Leutnant. Wir haben nur auf Sie gewartet. Bis später!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Danke, Kapitän. Das sind wertvolle Informationen. In diesem Fall, gehen Sie zum Dock und bereiten Sie Ihr Enterkommando vor. Wir werden gemeinsam und sofort das Räubernest stürmen. Die Besten meiner und Ihrer Männer werden die Vorhut bilden - sie werden es sein, die die Tore erobern. Den Rest besprechen wir, nachdem wir gemeinsam unsere Streitkräfte inspiziert haben. Enttäuschen Sie mich und Ihr Land nicht, "+GetFullName(pchar)+".";
				link.l1 = "...So sei es. Bis später, Leutnant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "Und ich, Idiot, bewunderte dich! A-agh! Der Stolz von Frankreich, Kapitän "+GetFullName(pchar)+"!! Du bist deines Patents unwürdig!!!";
			else dialog.text = ""+GetFullName(pchar)+", Abschaum, Verräter und verfluchter Pirat! Ich hätte ahnen sollen, dass dieses elende Versteck dein stinkendes Reich ist! Frankreich vergisst noch vergibt Männer wie dich nicht!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Bist du bereit, Kapitän? Deine Truppe sieht würdig aus!";
			link.l1 = "Danke, Leutnant. Sollen wir anfangen?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Ja, lasst uns sofort fortfahren!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! "+GetFullName(pchar)+"! Was für eine Begegnung. Hey, schnappt ihn euch! Dieser Bastard besitzt hier alles! Das ist seine Insel!";
			link.l1 = "Was für ein Tag ist das heute...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Cap'n, was sind die Befehle? Es gibt ein Signal, um bereit zu stehen und die Enterpartei zu schicken.";
			link.l1 = "Der Befehl steht. Jungs, folgt mir, wir müssen unser Zuhause von unerwünschten Gästen säubern. Der Preis ist mein, alle Trophäen sind eure!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Hurra!";
			link.l1 = "Zur Schlacht!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Grüße, Senor. Sind Sie der Besitzer dieses Landes? Erlauben Sie mir, mich vorzustellen, Groß Francisco de Alba, ehemaliger Kapitän der Korvette 'Perro Marino'.";
			link.l1 = "Ja, das ist mein Land. Ich bin "+GetFullName(pchar)+", Kapitän des Schiffes '"+pchar.ship.name+"'. Grandios? Wir hatten noch nie so angesehene Gäste hier.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Herr "+GetFullName(pchar)+"! Ihr Name ist gut bekannt. Sehen Sie, in letzter Zeit ist Ihr Name so oft in den Berichten des Casa de Contratacion aufgetaucht, dass ich ernsthaft damit gerechnet habe, Anweisungen zu bekommen, um mich mit Ihnen zu befassen.";
			link.l1 = "Handel mit mir?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Ich glaube, es macht keinen Sinn so zu tun als ob. Meine Aufgabe ist es, die Feinde Spaniens und König Philipps auf allen Meeren der Welt zu suchen und zu vernichten.";
			link.l1 = "Es ist glücklich, dass solche Befehle noch nicht gekommen sind. Ihr seid offensichtlich ein sehr geschickter Marineoffizier.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Die Tatsache, dass ich jetzt ein halbtoter Gefangener auf einer winzigen Insel voller Piraten bin und meine Landsleute auf der Flucht sind, bestätigt nur Ihre Schlussfolgerung, ha-ha! Es war eine sehr gefährliche Angelegenheit, aber Befehle sind Befehle. Wir waren fast erfolgreich! Es ist zutiefst bedauerlich für meine Männer - ich kannte sie alle beim Namen, wir dienten viele Jahre zusammen. Aber mein Land wird mehr Blut seiner Söhne vergießen müssen, um seinen imperialen Status zu bewahren. Unsere Familie weiß das besser als die meisten.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Lassen wir die dringenderen Angelegenheiten für jetzt zurück. Was soll ich mit dir machen, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Übrigens, Monsieur de Mor, der 'Krieger' - dieses kleine Schiff war Ihnen bekannt, nicht wahr? Ihre kühne Operation in Porto Bello blieb nicht unbemerkt. Kühn, sogar selbstmörderisch. Sie brauchten dringend Geld, oder? Ha!";
			link.l1 = "Du weißt viel über mich, Grand. Aber lass uns zu deinem Schicksal übergehen.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Was gibt es da zu überlegen? Wie in jeder guten Geschichte haben Sie drei Optionen: Töten Sie mich, lassen Sie mich hier, oder setzen Sie mich frei. Wenn Sie mich freilassen, gebe ich Ihnen das Wort der Familie de Alba, dass ich niemandem von diesem Ort und Ihrer Beteiligung an meinen Missgeschicken erzählen werde. Darüber hinaus werde ich Ihr Schuldner sein, und bis diese Schuld beglichen ist, werde ich niemals gegen Sie kämpfen.";
			link.l1 = "Ich kann es nicht riskieren, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Du wirst hier einige Zeit verbringen. Du wirst auf gleicher Ebene mit deinen Landsleuten leben und arbeiten.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Willkommen an Bord meines Schiffes, Grand. Ich werde dich am Leuchtturm von Santiago absetzen, wenn die Zeit gekommen ist. Ich hoffe, du wirst dein Wort halten.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Ich verstehe, Senor. Nun, in jedem Fall bin ich bereits in dieser Schlacht zusammen mit meinen Männern gestorben. Es ist ein gutes Ende.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "Ich gebe zu, ich mag es nicht, halbherzig zu sein. Aber es gibt keine Schande darin, ein Gefangener zu sein, also akzeptiere ich dein Geschenk des Lebens und werde in Frieden mit diesen freundlichen und anscheinend sehr glücklichen Menschen leben. Dennoch, wenn ich diesen Ort jemals verlasse, schulde ich dir nichts.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Ich gebe dir mein Wort und das Wort der Familie de Alba! Wir sehen uns auf dem Schiff!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Kapitän "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Ein Stück einer Karte?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "Das ist alles, was ich von Wert bei mir hatte. Ich zweifle nicht daran, dass ihr das andere Stück leicht finden werdet. Lebewohl! Und viel Glück für dich, mein Freund.";
			link.l1 = "Auf Wiedersehen, Grand. Denk an dein Wort, und viel Glück!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Grüße! Wie geht es Ihnen, Kapitän? Uns geht es gut.","Für die Gemeinschaft zu arbeiten, ist die größte Freude!","Ihre Insel ist wunderbar, Kapitän, und wir werden alles für ihren Wohlstand tun.");
			link.l1 = LinkRandPhrase("Schön, das zu hören.","Schön zu hören, dass alles in Ordnung ist.","Ich bewundere deine Begeisterung, Amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Nehmen Sie es nicht als Unverschämtheit, senor, aber hier zu leben ist unmöglich.","Alles ist besser als in den Zellen der Inquisition zu sitzen..."),RandPhraseSimple("Danke, dass Sie uns gerettet haben, Kapitän.","Sind diese... Piraten deine Freunde?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Es ist nicht schlecht hier! Nur ein bisschen langweilig.","Kapitän, schön Sie zu sehen. Schauen Sie mal vorbei!"),RandPhraseSimple("Jemand hat Schädel am Strand gefunden und sie zur Morgenversammlung gebracht. Ist es hier immer so?","Ich verrate Ihnen ein Geheimnis, Senor Himenes profitiert offensichtlich von der frischen Luft und Sicherheit dieses Ortes."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Es ist nicht schlecht hier! Nur ein bisschen langweilig.","Kapitän, schön Sie zu sehen. Schauen Sie mal vorbei!"),RandPhraseSimple("Jemand hat Schädel am Strand gefunden und sie zur Morgenversammlung gebracht. Ist es hier immer so?","Ich verrate Ihnen ein Geheimnis, Senor Himenes profitiert offensichtlich von der frischen Luft und der Sicherheit dieses Ortes."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Gott segne Sie, Kapitän!","Einmal pro Woche veranstalten wir Aufführungen am Strand und in der Taverne. Schau mal vorbei."),RandPhraseSimple("Ihre Matrosen bringen uns ständig allerlei Krimskrams im Austausch für frische Lebensmittel. Danke, dass Sie dies fördern.","Es ist erstaunlich, wie dieser Ort noch nicht entdeckt wurde. Ich hoffe, es bleibt so."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Danke, Senor. Dank Ihnen haben wir die wahre Neue Welt gesehen. Gott segne Sie!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Sicherheit und Frieden - das mag ich hier!","Ein wunderbares Paradies! Nun, fast...","Wir sind glücklich, nach so vielen Strapazen hier ein neues Zuhause gefunden zu haben.");
			link.l1 = LinkRandPhrase("Ich freue mich für dich und deine Gemeinschaft.","Ja, ich mag diese kleine Insel auch.","Es ist schön zu wissen, dass du zufrieden bist.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Hallo.","Herr, wer sind diese... rauen Männer mit Waffen?","Danke, dass Sie uns gerettet haben, Kapitän.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Unsere Männer haben hervorragende Arbeit geleistet - die Häuser sind ausgezeichnet. Aber wir haben auch hart gearbeitet!","Herr Kapitän, machen Sie sich keine Sorgen: die Frauen unseres kleinen Clans fürchten sich nicht vor Schwierigkeiten und vorübergehenden Unannehmlichkeiten.","Solch eine Luft hier! Und das Meer! Man fühlt sich Gott näher!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Unsere Männer haben großartige Arbeit geleistet - die Häuser sind ausgezeichnet. Aber wir haben auch hart gearbeitet!","Herr Kapitän, machen Sie sich keine Sorgen: Die Frauen unseres kleinen Clans haben keine Angst vor Schwierigkeiten und vorübergehenden Unannehmlichkeiten.","Solche Luft hier! Und das Meer! Man fühlt sich Gott näher!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Kommen Sie öfter zurück, Senor Kapitän. Ich freue mich immer, Sie zu sehen.","Herr Rodgar ist ein erstaunlicher Geschichtenerzähler. Man könnte ihm ewig zuhören!","Hehe. Sie sagen, jemand aus unserer Gruppe erwartet schon einen Zuwachs zur Familie. Das Leben geht weiter, sogar auf Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Du... Vielen Dank, Senor! Komm öfter vorbei...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Alles ist in Ordnung, Käpt'n!","Sklaven unter Kontrolle, mach dir keine Sorgen."),RandPhraseSimple("Sie müssen sich keine Sorgen machen, Meuterei ist ausgeschlossen.","Danke für den Rum! Wir machen uns an die Arbeit!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Spanier? Das hätten wir nicht von dir erwartet.","Jetzt müssen wir den ganzen Weg zum Strand laufen, nur um in Ruhe schlafen zu können!"),RandPhraseSimple("Warum hast du dich für all das entschieden - eh, Kap?","Der Boss hat dir damals vertraut - und er hat sich nicht geirrt. Wir werden dir wieder glauben."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Nach harter Knochenarbeit ist es keine Sünde, ein oder zwei Drinks zu haben...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Genieß deinen Trunk, Kumpel, ha-ha!","Entspann dich, Kumpel, übertreib es nur nicht, sonst schimpft die Frau mit dir, ha-ha!","Mach's ruhig, Kumpel, das Leben besteht nicht nur aus Arbeit!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Kapitän, schöner Ort, den Sie hier haben!","Stell dir vor, wir hätten plötzlich keinen Rum mehr. Du würdest sicherlich mehr besorgen, oder?"),RandPhraseSimple("Ich habe schon lange von einem Urlaub wie diesem geträumt. Ein Bordell wäre allerdings toll... nur ein wilder Gedanke, Käpt'n.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Danke für den Urlaub, Kapitän.","Schöner Ort, den Sie hier aufgebaut haben - Sie haben ein Händchen dafür, Dinge in Ordnung zu halten, Kapitän."),RandPhraseSimple("Frisches Essen, Schnaps, fester Boden unter den Füßen. Es ist ein Traum.","Ich würde gerne noch ein bisschen länger hier bleiben."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Ich bin so müde - ich kann kaum stehen.","Keine Kraft mehr, so zu leben!"),RandPhraseSimple("Diese Arbeit ist zu hart für mich.","Die Aufseher haben keine lebende Zelle auf meiner Haut gelassen!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Kann ich Ihnen bei etwas helfen, Kapitän?","Komm rein, probiere etwas lokale Paella. Frag bloß nicht, woraus sie gemacht ist, beim Gott!","Willkommen, Kapitän. Wie gefällt es Ihnen hier?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Herr, willkommen!","Hallo, Kapitän. Bleiben Sie?","Bist du hier für mich? Bitte, komm rein, ignoriere einfach das Durcheinander, senor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}