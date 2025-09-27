// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Du hast versucht, mir vor kurzem eine Frage zu stellen, "+GetAddress_Form(NPChar)+"...","Über den ganzen Tag, dies ist das dritte Mal, dass du über irgendeine Frage redest...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Ich habe gehört, dass der Konsum in Ihrer Festung grassiert. Glauben Sie, dass die Epidemie sich auf die Stadt ausbreiten wird?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Was können Sie über den Kommandanten der Festung sagen?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Sag mal, bedeutet der Name 'Juan' dir etwas?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Hör zu, im April 1654 legte eine Fregatte unter dem Kommando von Kapitän Miguel Dichoso in deinem Hafen an und er verschwand danach. Gibt es etwas, was du mir darüber erzählen kannst?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Sag mir, "+npchar.name+", was ist das für ein Vogel, dieser Javier Castillo?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Kehren wir zurück zu dem Gespräch über den Mann, der Einfluss auf Javier haben könnte.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Der Kommandant behauptet, es gibt keine Gefahr. Diejenigen, die zu neugierig sind, landen in den Kasematten eingesperrt. Ich bin keiner von denen, tut mir leid.";
			link.l1 = "Ist das so? Ein Wirt, der keine Lust hat, Gerüchten zu lauschen - das ist etwas Neues! Könnte es sein, dass das Klimpern von Pesos deine Neugier zurückbringt?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Silber ist natürlich verlockend, aber meine eigene Haut ist mir mehr wert. Vielleicht könnte ich Ihnen von etwas anderem erzählen, senor? Ich bin eigentlich immer gerne bereit zu plaudern, beginnen Sie einfach das Gespräch!";
			link.l1 = "So ist also die Sache... Gut, in diesem Beutel sind dreitausend Achtstücke und wir werden ein nettes kleines Gespräch über das Wetter führen, einverstanden?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Oh, Sie sind hartnäckig, Senor. Nur, erinnern Sie sich, dass dieses Gespräch nie stattgefunden hat. (flüstert) Ich habe schon mehrmals im ganzen Jahr gehört, dass Menschen in unseren Gefängnissen verbrannt wurden, an Schwindsucht starben. Sie können die Behörden beschuldigen, Sie können Gott oder den Teufel beschuldigen, aber das meiste davon wird dem Pech zugeschrieben. Diese verfluchte Krankheit stiehlt so schnell Leben. Manchmal stecken sie einen völlig gesunden Mann hinein und in einer oder zwei Wochen ist er weg. Einfach so...";
			link.l1 = "Wie... Ein ganzes Jahr, sagst du? Und was, hat sich niemand dazu entschlossen, etwas dagegen zu unternehmen?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Wen kümmert's, senor? Wer kümmert sich um Gefangene? Der Abschaum der Gesellschaft - so sagen die großen Männer in Seide. Es gab einen Arzt, der in den Verliesen arbeitete. Versuchte, diese armen Seelen zu heilen. Er hat nicht lange durchgehalten, es scheint, dass die Krankheit auch ihn beseitigt hat\nDer Kommandant lässt jetzt keine Leute mehr rein, und unsere Behörden beachten solche Angelegenheiten nicht, besonders wenn sie weniger für Gefängnisrationen zahlen müssen.";
			link.l1 = "Interessant, aber was ist es an dieser Krankheit, die euch so sehr erschreckt, dass wir, eingeschlossen in sicheren Mauern, flüstern wie Nonnen im Beichtstuhl?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Es fällt mir schwer, es Ihnen zu sagen, aber es war einmal ein Kerl hier. Er wurde wegen Schmuggels eingesperrt und etwa ein halbes Jahr lang eingesperrt, bis seine Kumpels ihn herauskauften. Nun, ihr wisst schon - sie maßen Gold ab für jeden, der es brauchte, sie warteten so lange, wie man ihnen sagte, und der Kerl kam heraus. Aber seitdem ist er völlig verrückt geworden.";
			link.l1 = "Verrückter als eine Bilgenratte?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Ich vermute. Seitdem war er für seine Kameraden nutzlos, verbrachte den ganzen Tag hier und trank sich zu Tode. Es sah so aus, als wollte er etwas aus seinem Kopf löschen. Jedes Mal, wenn er betrunken wurde, erzählte er Geschichten über den 'Verzehr', der die Menschen in Stille nimmt\nDas waren seine genauen Worte. Laut ihm ist der 'Verzehr' das Schlimmste, was einem Mann passieren kann.";
			link.l1 = "Das Geschwätz eines Betrunkenen. Was soll's?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Nichts, außer dass er etwas flüssigen Mut gefunden hat und immer mehr zu reden begann und dann hat jemand einfach so seine Kehle durchgeschnitten und ihn in die Gosse geworfen... und wer es getan hat und wofür, ist mir völlig gleich.";
				link.l1 = "Was können Sie über den Kommandanten sagen?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Nichts, außer der Tatsache, dass er mutig wurde und immer mehr zu reden begann und dann, einfach so, schlitzt jemand seine Kehle auf und wirft ihn in den Rinnstein... und wer es getan hat und wofür, ist mir völlig egal. (erhebt seine Stimme) Ja, die Buchten und Riffe sind hier wirklich gefährlich, senor. Sie müssen vorsichtig sein, wenn die Stürme von den Großen Antillen hereinbrechen, verpassen Sie das Wetterlot und Sie sind weg! Haben Sie eine schöne Ruhe, senor, danke für Ihren Besuch!";
				link.l1 = "Stürme... richtig. Danke auch dir.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Was gibt es über ihn zu sagen? Er ist ein Oberst, kam vor ein paar Jahren aus Europa und hat diesen Ort erhalten. Angeblich wurde er in der Alten Welt für einige schmutzige Taten, die er begangen hat, herabgestuft. Ich weiß nicht, ob es wahr ist, aber am Anfang gab es Gerüchte. Aber wer hat keine Gerüchte über sich, richtig?";
			link.l1 = "Schmutzige Geschäfte, sagst du... Das ist interessant. Noch etwas?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Nun, was soll ich sagen... Der Oberst sieht aus wie ein Mann, der sich sehr um seine eigene Sicherheit sorgt. Sicher, diese Orte sind wegen Piraten, Banditen, Indianern und anderem Gesindel nicht sicher, aber Senor Kommandant verlässt sein Haus nie ohne mehrere Leibwächter\nIn dieser Stadt hat er sein Herrenhaus und er hat es zu einer kleinen Festung gemacht - seine Diener sind gut bewaffnet und die Fenster sind verriegelt.";
			link.l1 = "Aber am Tage dient er im Gefängnis, oder nicht?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Ja, aber diese Villa ist im Grunde dort für einen Hinterhalt oder eine Invasion. Jedenfalls kehrt der Señor Kommandant dort anscheinend nicht oft zurück, eine echte Festung ist eher seine Stärke, he-he.";
			link.l1 = "Danke, du warst eine große Hilfe. Bis später, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Welcher? Es gibt viele von ihnen hier, die Leute haben normalerweise auch Nachnamen... oder zumindest einen Spitznamen...";
			link.l1 = "Ich habe gerade gedacht... Vielleicht ist sein Spitzname 'Schwindsucht', hast du das schon mal gehört?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Ach du meine Güte, du redest schon wieder davon! Nein, Gott sei Dank, ich habe nichts gehört. Ich schwöre! Und jetzt lass uns das Thema wechseln. Bitte!";
			link.l1 = "Na gut, bekomm bloß keinen Herzanfall...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier ist ein Kartenspieler, ein Gauner und ein Betrüger. Er hängt ständig in der Taverne herum und sucht jemanden, dem er ein paar Pesos abluchsen kann.";
			link.l1 = "Also war er in anderen zwielichtigen Geschäften nicht auffällig? Hat er vielleicht Feinde?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;

		case "OZ_Tavern_2":
			dialog.text = "Nun, sagen wir es so: Freunde hat er deutlich weniger als Leute, die davon träumen, ihm den Hals umzudrehen. Aber wenn Sie den Namen einer Person wollen, die wirklich Einfluss auf ihn ausüben kann, wird das tausend Pesos kosten. Zahlen Sie – und ich erzähle Ihnen alles.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Na gut, hier hast du dein Geld, alter Erpresser.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Kommen wir später darauf zurück. Momentan habe ich die Summe nicht.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;

		case "OZ_Tavern_2_1":
			dialog.text = "Kapitän, haben Sie die tausend Pesos mitgebracht?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Ja. Hier, alter Erpresser.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Verdammt. Ich komme bald zurück.";
				link.l1.go = "exit";
			}
		break;

		case "OZ_Tavern_3":
			dialog.text = "So reden wir schon ganz anders. Sehen Sie, Javier hat nicht nur Kartenschulden. Einmal versuchte er sich im Antiquitätenhandel, aber wie zu erwarten, endete das nicht gut für ihn. Anfangs lief es sogar ganz ordentlich, doch dann bot sich ihm die Gelegenheit, ein seltenes Stück zu erwerben.\nEr war so begeistert von der Idee, dass er alle Geldverleiher abklapperte. Natürlich gab ihm keiner auch nur einen Peso. Schließlich fand er einen ebenso antiquitätenverrückten Mann und lieh sich bei ihm hundertfünfzigtausend Pesos. Den Rest können Sie sich wohl denken.\nEr wurde hereingelegt, und nun hängt diese Schuld wie ein Mühlstein um seinen Hals. Er hat nur einen lächerlichen Betrag zurückgezahlt und scheint den Rest überhaupt nicht begleichen zu wollen, obwohl sein Gläubiger sogar Leute angeheuert hat, um ihn einzuschüchtern.\nDer Mann, dem er das Geld schuldet, ist Felipe Alarcón. Sein Haus steht gegenüber der Bank – Sie werden es leicht erkennen, es ist ein prächtiges Anwesen mit Säulen am Eingang.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "Ich erinnere mich an ihn. Kam oft in meine Taverne, sprach aber nicht viel. Hatte ein paar Schluck Rum, flüsterte ein paar Worte mit einigen Kunden und ging. Sehr düster und ernst wie alle auf dieser Fregatte. Gefährlich aussehende Söldner, die ihre Klingen bereithielten\nEs gab Gerüchte, dass die Fregatte voller Schätze war, aber ich glaube an solche Geschichten nicht. Wertvolle Ladung wird niemals auf einem einzelnen Schiff ohne Konvoi transportiert. Sie verbrachten einen Tag hier und dann gingen sie. Nach Europa, hörte ich. Das ist alles, was ich weiß.";
			link.l1 = "Ich verstehe. Nun, es ist zumindest etwas...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
