// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "С какой целью вы прибыли на Тортугу, капитан?";
			link.l1 = "Прошу вас! Помогите моему товарищу, и я отвечу на все ваши вопросы!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Такой важный человек - и пришёл без охраны, сразу после того, как вся тюрьма слышала выстрел?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Пока вы тянете с ответом, он будет истекать кровью. Я повторяю вопрос.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Я знаю достаточно о том, что произошло. Я повторяю вопрос.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Последний шанс, капитан.";
			link.l1 = "Я выполняю задание генерал-губернатора!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Вы сами прекрасно знаете, что я - владелец и капитан корабля, и работаю по найму. И на ваш прекрасный остров я захожу несколько раз в год!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Я подозревал, но не был до конца уверен. Вам повезло, что буквально на днях, в Капстервиле, прошла важная встреча. Уважаемые люди нашли компромисс и договорились. И вы мне больше не враг.";
			link.l1 = "Вы поможете нам?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Я отпущу вас немедленно. Вашего товарища перенесут на корабль и окажут первую помощь.";
			link.l1 = "Спасибо...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Вы чуть было не сели на мель, Шарль! Уходите и не возвращайтесь на Тортугу минимум месяц. Пусть осядет пыль, и остынут головы.";
			link.l1 = "Так и поступим. До свидания!";
			link.l1.go = "exit";
			link.l2 = "Совсем ничего не объясните? Хотя бы в двух словах...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "На вас поступил донос. Якобы вы - фанатик-католик, прибыли на наш прекрасный остров, чтобы подло убить его славного губернатора.";
			link.l1 = "Я не фанатик!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Написано грамотно, поверьте. Я хорошо разбираюсь в таких вещах: cамые лучшие доносы - это те, в которых есть хотя бы капля правды.";
			link.l1 = "Кто написал донос?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Кто пропустил убийцу в тюрьму?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Тот, кто хотел, чтобы вас просто помариновали несколько дней в тюрьме, вместо того, чтобы сразу отправить на пыточный стол гугенотов в подвале Ля-Роша\nВсё, Шарль. Уходите. Сначала решите текущие первоочередные проблемы, а потом уже... ну вы поняли!";
			link.l1 = "Да. Решу. Прощайте, комендант.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Я.";
			link.l1 = "Лучше пришлите ещё одного, пока я не вышел отсюда.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Я вас очень внимательно слушаю, комендант.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Я не обязан что-либо объяснять вам, Шарль. Радуйтесь, что вы попали в мои руки, а не в руки моего прямого руководителя. Радуйтесь, что компенсацию за все эти пертурбации мне предоставит ваше начальство, а не вы сами.";
				link.l1 = "А то как же, знаю я своё начальство... Прощайте, комендант.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "А знаете что? Я вам расскажу. В особый пенсионный фонд гарнизона поступило щедрое, не облагаемое налогами, пожертвование. В качестве ответной любезности дарителю было разрешено способствовать скорейшей и законной казни известного преступника!";
				link.l1 = "Моего офицера?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Моего друга?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Я не обязан что-либо объяснять вам, Шарль. Радуйтесь, что вы попали в мои руки, а не в руки моего прямого руководителя. Радуйтесь, что компенсацию за все эти пертурбации мне предоставит ваше начальство, а не вы сами.";
				link.l1 = "А то как же, знаю я своё начальство... Прощайте, комендант.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "А знаете что? Я вам расскажу. В особый пенсионный фонд гарнизона поступило щедрое, не облагаемое налогами, пожертвование. В качестве ответной любезности дарителю было разрешено способствовать скорейшей и законной казни известного преступника!";
				link.l1 = "Моего офицера?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Моего друга?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Уходите, Шарль. И забирайте эту мразь с собой. Ваш выбор спутников... разочаровывает.";
			link.l1 = "Хотя бы скажите, где мне найти вашего... мецената?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "На материке. Прощайте, Шарль.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "На вас поступил донос. Очень нехороший. Вас явно подставили, капитан, но... Я всё равно имею право продержать вас тут ещё пару недель, а товарища вашего оставить подыхать. Если только...";
			link.l1 = "Сколько?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Кто подставил? Это вы впустили убийцу в тюрьму?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Будьте любезны внести пять сотен дублонов в пенсионный фонд гарнизона Тортуги у местного ростовщика.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text + " И ещё добавим сотню дублонов за давние проблемы, которые вы доставили, связавшись с одной высокопоставленной дамой на этом острове.";
			}
			link.l1 = "Откройте уже эту чёртову дверь!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Вы отняли и так слишком много моего времени. Отправляйтесь к ростовщику и внесите пятьсот дублонов в пенсионный фонд гарнизона Тортуги.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text + " И ещё добавим сотню дублонов за давние проблемы, которые вы доставили, связавшись с одной высокопоставленной дамой на этом острове.";
			}
			link.l1 = "Откройте уже эту чёртову дверь!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Средства внесены. Где Эркюль?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Мы оказали ему первую помощь и отправили на ваш корабль. Крепок мерзавец, скорее всего, выкарабкается. Прощайте, капитан, и чтобы духу вашего тут не было какое-то время!";
			link.l1 = "Да уж, после такого приёма, ноги моей здесь ещё долго не будет! Прощайте, комендант.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
