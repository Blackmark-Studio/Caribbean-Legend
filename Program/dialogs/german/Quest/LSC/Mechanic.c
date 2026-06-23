// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
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
				dialog.text = "Guten Tag, Herr. Ich habe Sie noch nie gesehen. Sind Sie ein Neuling? Und ist es das erste Mal, dass Sie sich entschieden haben, diese Plattform zu besuchen?";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Ich bin neu hier und schau mich nur um, lerne Leute kennen...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "Hör zu, "+pchar.name+", wenn du mich weiterhin ablenkst, werde ich die Reparaturen nie beenden.";
					link.l1 = "Ja, ja, ich erinnere mich daran. Es tut mir leid, dass ich Sie belästige!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "Ach! Schau nur! Der ertrunkene Mann ist zurück aus der anderen Welt! Nun, sag mir, wie hast du so einen Trick geschafft? Sie haben dir ein Begräbnis gehalten und dich in deiner Abwesenheit begraben, falls du es nicht wusstest...";
					link.l1 = "Schade, ich werde noch nicht sterben. Der Trick ist einfach - ich habe nur das Idol von Kukulcan am Boden berührt. Es teleportierte mich nach Dominica, direkt ins Dorf der Kariben...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "Ach, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "Henrik, ich habe ein Geschäft für dich. Ein sehr wichtiges Geschäft. Ole Christiansen hat mir von dir erzählt. Er wird auch der Weiße Junge genannt.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "Henrik, ich habe dir genug 'Silber' gebracht. Genau wie du gefragt hast: eins von dir plus zehn Extra-Stücke. Hier, nimm sie.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "Ich bin's wieder, Henrik. Wie steht's um deinen Anzug? Konntest du ihn reparieren?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= int(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "Ich habe genug von dem Metall, nach dem du gefragt hast. Nimm es.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "Guten Tag, Henrik. Also, ist der Anzug bereit für einen Tauchgang?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "Es ist vorbei, ich habe meine Probleme gelöst und bin bereit zu tauchen. Wann fangen wir an?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "Hallo, Henrik. Also was, ist der Anzug bereit für einen Tauchgang?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "Ich möchte Ihnen Ihren Anzug zurückgeben.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die letzten Klatsch und Tratsch erzählen?");
				link.l1.go = "rumours_LSC";
				link.l3 = "Ich wollte nur wissen, wie es dir geht.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Und ich bin Henrik Vedecker. Obwohl, die Mehrheit der Einheimischen kennen mich als den Mechaniker und das ist tatsächlich eine sehr wahre Definition.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "Bist du der Henrik Vedecker? Freut mich, dich zu treffen! Ich habe nach dir gesucht.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "Du musst der Tausendsassa sein, richtig?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "Oh, ja, die Narwale schätzen meine Fähigkeiten sehr. Meine Werkzeuge ermöglichen es ihnen, viele Wertsachen von den verlorenen Schiffen des äußeren Rings zu erhalten, so dass sie Proviant vom Admiral Dodson kaufen können\nEigentlich sind Wissenschaft und Forschung meine Leidenschaft. Deshalb entschuldige ich mich, falls ich nicht genug Zeit für dich aufbringen kann - meine Experimente nehmen fast meine ganze Zeit in Anspruch.";
			link.l1 = "Ich verstehe. Ich werde Sie nicht ohne Grund belästigen, Herr Vedecker, das versichere ich Ihnen. Ich bin sehr froh, Sie kennenzulernen!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "Wartest du? Und warum?";
			link.l1 = "Ole Christiansen hat mir von dir erzählt. Er wird auch der Weiße Junge genannt.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "Ach, dieser lustige Kerl! Ja, ja, ich kenne ihn. Und was hat er dir erzählt?";
			link.l1 = "Es tut mir leid, wenn meine nächste Frage dumm klingt, aber... ich frage dich trotzdem. Ole hat mir gesagt, dass du mir vielleicht beibringen könntest, wie man auf den Grund taucht, unter Wasser. Bitte lach nicht über mich, wenn das nur seine Einbildung ist.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "Es ist wahr. Ich war selbst mehrmals auf dem Grund. Allerdings tauche ich nicht mehr, das Riff wimmelt heutzutage von riesigen Krabben und, wie du sicherlich sehen kannst, bin ich nicht in der Lage, gegen sie zu kämpfen, ich bin ein Wissenschaftler, ich kann gegen diese Dinger nicht kämpfen.\nAußerdem gab es noch zwei andere Männer, zwei Narwale, die tauchten, aber sie hörten schließlich auf - das Plündern der Schiffsfrachten des äußeren Rings erwies sich als sicherer als das Tauchen an Orten, die von riesigen Krabben befallen sind.\nJetzt benutzen sie meine Ausrüstung selten, seit Monaten kein einziger Tauchgang wegen des Risses im Anzug...";
			link.l1 = "Hast du wirklich einen Anzug, mit dem du auf den Grund tauchen kannst? Habe ich dich falsch verstanden?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "Deine Ohren sind am rechten Fleck, junger Mann. Ich habe den Anzug selbst erfunden und gefertigt. Er besteht aus dickem, vollkommen wasserdichtem Segeltuch, Metallteilen und einem von mir und Jurgen in seiner Schmiede geschmiedeten Stahlhelm\nIch habe den Anzug auch mit einer Metallbrustplatte, Knieschützern, Bruststücken und Stiefeln verstärkt, um besser vor Krabben zu schützen und zusätzliches Gewicht zu bieten\nSpezielle Tanks, gefüllt mit komprimierter Luft, bieten Lebenserhaltungsfunktionen und die Möglichkeit, eine gewisse Zeit unter Wasser zu verbringen. Der Anzug ist einzigartig und ich bin ziemlich stolz darauf.";
			link.l1 = "Das ist großartig. Aber haben Sie erwähnt, dass der Anzug beschädigt ist?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "Leider ist es so. Mehrere Teile des Anzugs waren durch Metallplatten verbunden, um Flexibilität und zusätzlichen Schutz zu gewährleisten, aber das Seewasser hat ihnen stark zugesetzt. Die Platten sind durch jahrelangen Gebrauch verrostet und haben ihre Wasserresistenz verloren.\nEs ist gut, dass ich den Schaden bemerkt und die Menschen vor dem Tod bewahrt habe. Selbst der Trockenanzug enthielt etwas Salz und Wasser, sie hatten ihre schändliche Aufgabe vollständig erfüllt.";
			link.l1 = "Nun.. Aber du kannst den Anzug reparieren! Du kannst die alten rostigen Teile durch neue ersetzen... Richtig?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "Wozu? Um sie ein Jahr später wieder zu ersetzen? Weißt du, wie schwierig diese Arbeit ist? Den Anzug mit flexiblen Gelenken zu komponieren und wasserdicht zu machen? Es ist mindestens eine Woche Arbeit ohne Pause.";
			link.l1 = "Und das ist der Grund, warum Sie bereit sind, Ihre Erfindung wegzuwerfen?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "Nein, natürlich nicht. Ich habe eine Idee. Ich muss die Gelenke aus einem Metall herstellen, das nicht durch Wasser und Salz zerstört werden kann. Und ich weiß, welches Metall helfen kann...";
			link.l1 = "Also, was ist das Problem?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "Das Problem ist, dass dieses Metall sehr selten ist. Ich habe nur ein Stück, was sicherlich nicht genug ist. Ich brauche mindestens zehn weitere Stücke oder sogar fünfzehn.";
			link.l1 = "Und was ist das... Metall, von dem du redest?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "Oh, das ist ein einzigartiges Metall, wirklich von vielen unterschätzt. Es hat eine hohe Haltbarkeit, Plastizität und ist absolut immun gegen Einflüsse - weder Wasser noch Salz können es beschädigen\nVielleicht haben Sie das Metall schon einmal gesehen. Es ist weiß, sieht aus wie Silber, deshalb nannten es die Spanier 'Silber'. Ha! Es ist hundertmal besser als Silber! Sogar besser als Gold! Eines Tages werden sie das verstehen, aber die richtige Zeit ist noch nicht gekommen.";
			link.l1 = "Hör zu, warum kannst du keine anderen Metallarten verwenden? Warum benutzt du kein Gold, um diese Platten herzustellen? Ich habe noch nie gehört, dass Gold rosten oder verfallen kann.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "Sie haben einen flexiblen und lebendigen Verstand, junger Mann. Das ist gut zu wissen. Leider wird Ihr Vorschlag nicht funktionieren. Der Gedanke an Gold war das Erste, was mir in den Sinn kam. Aber das Gold ist zu weich, um verschiedene Teile des Anzugs zu verbinden\nLeider ist Platin das einzige Material, das funktionieren wird. Ich werde Teile nur daraus herstellen, auch wenn es Jahre dauern wird, genug zu sammeln. Aber ich habe schon Stücke des Metalls auf der Insel gesehen - es wird oft mit Silber vermischt wegen seines Aussehens.";
			link.l1 = "Hm. Und wenn ich Ihnen helfe, genug von diesem... 'Silber' zu finden, würden Sie mir dann den Anzug leihen, damit ich unter Wasser tauchen kann?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "Keine Notwendigkeit zu fragen! Sicher, ich werde. Ich habe dir schon gesagt, dass ich dort wegen der Krabben nicht tauchen würde und niemand sonst will das auch tun.";
			link.l1 = "Dann zeig mir dieses Stück Metall, um mir zu helfen zu verstehen, was ich finden muss.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "Also wirst du danach suchen? Hervorragend. Hier, nimm dieses Stück als Beispiel. Such es unter dem Silbererz und den Nuggets. Es wird nicht einfach sein, es zu finden, aber du wirst es schaffen. Auf Silber gibt es kleine Verdunkelungen, aber unser Metall ist klar und viel härter als Silber. Der einfachste Weg, es zu testen, wäre, die Silbermünze darauf zu kratzen, wenn die Münze beschädigt wird, dann hast du es gefunden.";
			link.l1 = "Gut. Ich werde sofort danach suchen. Hast du Vorschläge, wo ich danach suchen sollte?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "Ach, ich weiß es nicht. Wenn ich wüsste, wo ich es finden könnte, würde ich es selbst tun. Aber ich kann dir einen Ratschlag geben. Suche in den Schiffen der Rivados. Ich besuche sie nicht, also ist es sehr wahrscheinlich, dass sie es haben könnten.";
			link.l1 = "Ich werde es bedenken, Henrik. Ich hoffe, dass ich Glück haben werde.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "Sammle zehn weitere Stücke. Es ist das Minimum, um den Anzug zu reparieren. Viel Glück!";
			link.l1 = "Danke. Auf Wiedersehen, Mechaniker!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "Nun, nun, zeig mir... Ausgezeichnet! Gut gemacht, junger Mann! War es schwierig?";
			link.l1 = "Eigentlich nicht...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "Nun, jetzt kann ich mit den Reparaturen beginnen. Ich werde keine Zeit verschwenden und morgen anfangen. Du bist wirklich begierig zu tauchen, oder?";
			link.l1 = "Tatsächlich. Ich möchte wirklich den Unterwasserbereich erkunden.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "Das ist sehr gut, denn ich werde eine Bitte an dich haben, wenn wir deinen Tauchgang organisieren. Aber darüber sprechen wir später. Komm in fünf Tagen vorbei, ich hoffe, ich werde die Reparaturen beenden.";
			link.l1 = "Gut. Ich wünsche dir Glück!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "Sicherlich braucht man Glück, aber die Reparatur des Anzugs erfordert vor allem Fähigkeiten. Außerdem muss ich einen Tag mit Jurgen am Ofen verbringen, um aus dem Metall, das du mir gebracht hast, eine Platte zu machen.";
			link.l1 = "Dann werde ich dich nicht belästigen. Bis in fünf Tagen. Tschüss!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (int(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "Ja. Jurgen und ich haben verdammt gute Arbeit geleistet und die Menge an Teilen, die du gebracht hast, war ausreichend. Der Anzug ist repariert und vorbereitet. Ich muss nur noch einige Tests durchführen, aber ich bin sicher, dass alles in Ordnung ist. Komm morgen um 10 Uhr - ich werde die Tanks mit Luft füllen und du kannst tun, was du willst.";
				link.l1 = "Ausgezeichnet! Ich freue mich darauf. Bis morgen, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Ich muss Sie enttäuschen, "+pchar.name+". Wie ich vermutet habe, gibt es nicht genug Metall. Ich brauche "+FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty))+" mehr Teile, um die Reparatur abzuschließen. Ich muss Sie erneut um Hilfe bitten.";
				link.l1 = "Nun, ich habe solch eine Wendung der Ereignisse nicht erwartet. Gut, ich werde versuchen, die Nuggets zu finden, die dir fehlen.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "Ich werde auf dich warten. Du kannst sicher sein, dass dieser Betrag sicherlich ausreichen wird. Bring sie einfach und ich werde die Arbeit in einem Tag erledigen.";
			link.l1 = "Ich hoffe es... Bis dann!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(int(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", int(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "Herrlich! Jetzt wird der Anzug wiederhergestellt. Ich muss nur noch einige Tests durchführen, aber ich bin sicher, dass alles in Ordnung ist. Komm morgen um 10 Uhr - ich werde die Tanks mit Luft füllen und du kannst tun, was du willst.";
			link.l1 = "Ausgezeichnet! Ich freue mich darauf. Bis morgen, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "Ja, der Anzug ist bereit und mit Luft gefüllt. Sie können tauchen.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "Gut. Aber ich kann jetzt nicht tauchen, ich muss ein Problem mit meinem... Freund, Nathan Hawk, lösen. Ich kann ihn nicht finden. Kann der Anzug ein bisschen warten?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "Prächtig! Wann fangen wir an? Jetzt?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "Sicher. Es kann warten. Wirst du nicht ein Jahr lang nach deinem Freund suchen?";
			link.l1 = "Sicher, ich werde es nicht tun. Vielleicht finde ich ihn sogar heute noch. Ich werde dich besuchen, gleich nachdem ich meine Geschäfte mit ihm abgeschlossen habe.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "Ja bitte. Komm, wenn du bereit bist zu tauchen.";
			link.l1 = "Danke!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "Jetzt gleich, wenn du möchtest. Aber lass mich dir zuerst eine kleine Anleitung geben. Du wirst deinen Tauchgang von der Plattform 'Phoenix' aus beginnen, du kommst dorthin vom Heck des San Gabriel. Es gibt einen Hebezeug, der dich nach unten und wieder zurück bringt. Das ist der einzige Weg zurück\nAlso merk dir besser den Standort des Hebezeugs unter Wasser und verirre dich nicht. Die Tanks des Anzugs haben genug Luft für zwanzig Minuten Tauchen. Pass auf deine Zeit auf oder du wirst ersticken\nGeh nicht zu weit vom Hebezeug weg oder du wirst es nicht rechtzeitig zurück schaffen und Gott bewahre dich davor, unser Riff zu verlassen - du wirst flach wie ein Plattfisch gedrückt\nSei vorsichtig und achte auf Krabben. Wenn du ihnen zu nahe kommst, werden sie dich angreifen. Geh kein Risiko ein, wenn du nicht musst, du wirst nicht in der Lage sein, ein ganzes Rudel von ihnen zu töten und schnell weglaufen ist dort unten keine Option.";
			link.l1 = "Ich werde mich um die Krabben kümmern. Ich kümmere mich um den Rest. Tauche nicht tiefer, gehe nicht weit weg von der Winde und vergiss nicht die Zeit. Wann kann ich tauchen?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "Wann immer Sie wollen, aber nur von 7 Uhr morgens bis 21 Uhr abends. Im Dunkeln werden Sie nichts sehen können.";
			link.l1 = "Hab's verstanden.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "Genau das ist es. Nimm den Anzug aus dem Raum an der Plattform. Zieh ihn nach dem Tauchen aus und bring ihn zu mir. Ich werde ihn wieder mit Luft füllen. Aber versuche nicht, mehr als einmal am Tag zu tauchen, selbst die 20 Minuten Tauchen und das Atmen der komprimierten Luft ist schlecht für deine Gesundheit.";
			link.l1 = "Nun, dann werde ich nicht mehr als einmal pro Tag tauchen.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "Ich bin froh, dass du verstehst. Jetzt geh und viel Glück!";
			link.l1 = "Danke!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "Also, warum bist du noch hier? Der Anzug wartet auf dich.";
				link.l1 = "Ja, ja. Ich bin unterwegs.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Also, wie war der erste Tauchgang?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "Äußerst exzellent und ich bin mit den Ergebnissen zufrieden. Ich habe ein Steinidol im versunkenen Galeonen gefunden. Ich habe gehört, dass Rivados ihm zuvor einige Opfergaben dargeboten hat. Sag mal, Henrik, kennst du jemanden, der mir mehr darüber erzählen könnte?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "Gut. Ich habe es getan! Es war wirklich interessant, wenn auch ein bisschen aufregend.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "Haben Sie Interesse an unserer Geschichte? Gehen Sie zu Antonio Betancourt. Er wurde hier geboren. Er lebt in der Flöte Pluto. Wenn er nichts darüber weiß - weiß es niemand.";
			link.l1 = "Ausgezeichnet! Ich werde ihm auf jeden Fall einen Besuch abstatten.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "Lassen Sie den Anzug hier. Kommen Sie morgen oder an jedem anderen Tag zurück, ich werde ihn mit Luft füllen.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sicher. Hier ist dein Anzug. Danke!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Sicher. Ich bringe es sofort!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "Nun, hast du mir meine Ausrüstung gebracht?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sicher. Hier ist dein Anzug. Danke!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "Ich werde es sofort tun!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "Ja, sicher. Der Anzug wurde getestet und mit Luft gefüllt. Hast du das Pfand dabei? 500.000 Pesos?";
				if (int(pchar.money) >= 500000)
				{
					link.l1 = "Ja, sicher. Hier, nimm es.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "Ups! Ich habe es vergessen. Ich bringe es sofort...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ja, sicher. Der Anzug wurde getestet und mit Luft gefüllt. Überprüfen Sie die 'Phoenix'-Plattform wie immer.";
				link.l1 = "Dann werde ich tauchen. Danke!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "Gut. Komm morgen oder später wieder. Ich werde den Anzug vorbereiten.";
			link.l1 = "Danke, Mechaniker!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "Sie bekommen Ihr Geld zurück, wenn Sie den Anzug zurückgeben. Faires Geschäft.";
			link.l1 = "Danke, Mechaniker! Ich werde jetzt tauchen gehen.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "Warten Sie bitte einen Moment! Welche Statue? A-ah, jetzt verstehe ich. Sie meinen dieses Idol im gesunkenen Schiff 'San-Geronimo', nicht wahr? Also sind diese Rivados-Geschichten wahr?";
			link.l1 = "Genau! Und es gibt keine Geschichten. Ich kenne noch zwei weitere Idole im Archipel, die Menschen, die sie berühren, von einem zum anderen teleportieren, im Kreis.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ich sehe, ich sehe. Ich werde dir vertrauen müssen, obwohl deine Worte der antiwissenschaftliche Unsinn sind. Teleporte, Statuen... ha! Und wer könnte darüber nachdenken, wie funktionieren solche Dinge überhaupt?";
			link.l1 = "Vertraue mir einfach und versuche nicht, hier irgendeine Logik zu finden. Ich lüge nicht.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Gut. Aber ich hoffe, dass Sie während dieser Teleportation von Ihnen den Anzug nicht verloren haben?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "Sicher, das habe ich nicht. Es hat mich sozusagen vor den Kariben gerettet. Hier ist es.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "Sicher, das habe ich nicht. Es hat mich sozusagen vor den Kariben gerettet. Aber jetzt habe ich es nicht bei mir.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "Also bring es mir, verdammt! Wir reden nicht, bis du es mir zurückgegeben hast, wisse das!";
			link.l1 = "Beruhige dich, Mechaniker. Ich werde es dir zurückgeben!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "Ach, du hast tatsächlich meinen Anzug gebracht! Danke, ich habe angefangen, mir Sorgen zu machen.";
				link.l1 = "Es gab keinen Grund zur Sorge. Ich habe Ihnen versprochen, es zurückzugeben.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "Komm nicht mal hierher, bis du nicht meinen Anzug hast.";
				link.l1 = "Gut, gut.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "Sehr gut. Ich habe darüber nachgedacht, einen neuen zu machen, aber das wäre eine Arbeit für ein Jahr, wenn nicht weniger... Ich bin froh, dass du eine feine Sparsamkeit gezeigt und mein Eigentum in einem Stück zurückgebracht hast. Ich werde dir sogar ein Geschenk machen.";
			link.l1 = "Bist du ernst?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "Sicher, das bin ich! Du hast mir geholfen, den Anzug zu reparieren und hast ihn nicht bei der ersten Gelegenheit weggeschmissen. Du hast dich darum gekümmert und ihn schließlich zu mir zurückgebracht. Hier ist jedenfalls eine feine Werkzeugkiste. Lerne, wie man sie benutzt. Du wirst in der Lage sein, mit ihrer Hilfe viele nützliche Dinge zu machen.";
			link.l1 = "Und was könnte ich sonst vom Mechaniker erwarten! Sicher, die Werkzeugkiste! Vielen Dank, Henrik, ich bin gerührt... Ich habe ein solches Geschenk nicht verdient.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich weiß besser, was du verdient hast und was nicht. Nimm es! Es wird dir nützlich sein. Aber ich gebe dir den Anzug nur zurück, wenn du 500 000 Pesos versprichst, wegen deiner Gewohnheit, dich über Idole zu teleportieren.";
			link.l1 = "Wahnsinn! Nun, ich verstehe das... Vorsichtsmaßnahmen...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "Sicher. Und was ist, wenn Sie eines Tages damit fliehen? Dann wird das Geld meine Entschädigung sein.";
			link.l1 = "Gut, Henrick. Ich stimme zu. Ehrlich gesagt, dachte ich, dass du es mir nie wieder geben würdest.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "Keine Chance. Versprich eine halbe Million und es gehört dir.";
			link.l1 = "Abgemacht! Kann ich es dann wie gewohnt zum Tauchen nehmen? Vom morgigen Tag an?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "Genau.";
			link.l1 = "Danke! Auf Wiedersehen, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Was machst du dort, hm? Dieb!","Schau dir das an! Kaum war ich in Gedanken verloren, hast du dich entschieden, meine Truhe zu überprüfen!","Entschieden meine Kisten zu überprüfen? Das wirst du nicht ungestraft tun!");
			link.l1 = "Verdammt!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Was?! Hast du beschlossen, meine Kisten zu durchsuchen? Das wirst du nicht ungestraft lassen!";
			link.l1 = "Dummes Mädchen!...";
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
			dialog.text = LinkRandPhrase("Hör zu, du solltest besser deine Waffe weglegen. Sie macht mich nervös.","Weißt du, hier wird nicht geduldet, dass man mit einer Klinge herumläuft. Nimm es weg.","Hör zu, spiel nicht den mittelalterlichen Ritter, der mit einem Schwert herumrennt. Leg es weg, es steht dir nicht...");
			link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, dein Schwert zu scheiden.","Hör zu, ich bin ein Bürger der Stadt und ich bitte dich, deine Klinge zu scheiden");
				link.l1 = LinkRandPhrase("Gut.","Sicher.","Wie du sagst...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sei vorsichtig, Kumpel, wenn du mit einer Waffe herumläufst. Ich kann nervös werden...","Ich mag es nicht, wenn Leute mit gezückter Waffe vor mir herlaufen. Es macht mir Angst...");
				link.l1 = RandPhraseSimple("Habs verstanden.","Ich nehme es weg.");
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
