// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Я ищу своего старого приятеля Фернана Люка. У меня к нему есть пара вопросов. Слышал, он тут неплохо проводил время неделю назад...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Мы с другом договаривались здесь встретиться, но я его нигде не вижу. Может, ты знаешь, куда он пошёл? Он всё ещё в городе или хотя бы на острове? Его зовут Лонгвэй, он китаец.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Хорошие новости, "+npchar.name+". У меня есть то, что спасёт ваше положение: сто бутылок отличного вина и сто бутылок рома. С такой партией ваши посетители снова будут купаться в реках выпивки. Вы готовы раскошелиться?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Ну что, "+npchar.name+", вы готовы обсудить условия сделки?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Итак, "+npchar.name+". С моей стороны все дела улажены, и товар уже на пути в таверну. Перейдём к расчёту?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Возможно, он и сейчас его неплохо проводит, только в окружении чертей. Склеил ласты твой приятель. Так что ты малость припоздал, капитан. Вон тот господин, за самым дальним столиком, оплатил его похороны, хотя сдаётся мне, что он и стал их причиной. Уж больно рожа у него бандитская. Его зовут Робер Мартэн, если хочешь, можешь задать ему свои вопросы. ";
			link.l1 = "Спасибо, приятель. Пойду, потолкую с месье Робером. Выпьем за упокой души несчастного Люка...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "А что тут обсуждать? Он напал на вас с приятелем, вы отбились, чуть ли не каждый день такое вижу. Хорошая работа. Вот только залу теперь опять отмывать...";
			Link.l1 = "Отмоешь, думаю, к этому ты тоже уже привык. Что ты знаешь об этом человеке?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Да ничего особенного толком. Появился буквально пару-тройку дней назад. Нравилось ему у нас, даже дом снимал на окраине города. Частенько захаживал, исправно платил. И, что самое главное, всё это время он прилично себя вёл, никому и слова дурного не сказал. До сих дивлюсь тому, что он напал на вас с другом\nДумал уже, что он осядет здесь навсегда.";
			Link.l1 = "В каком-то смысле так оно и оказалось. Ну, негусто, конечно, но спасибо и на этом, приятель. До встречи.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			Return_KnippelOfficer();
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Это имя мне ни о чём не говорит, да и вообще я таких в своё заведение не пускаю и не интересуюсь подобными людьми, знаешь ли - себе дороже.";
			Link.l1 = "Справедливо. Ладно, до встречи.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Ох, "+GetAddress_Form(NPChar)+", тут всё куда хуже. Мой поставщик из Антигуа лишился винокурни - пираты налетели, всё сгорело дотла. Теперь он говорит, что раньше, чем через два месяца ни рома, ни вина можно не ждать.";
			link.l1 = "Так найдите нового поставщика. Не будете же вы сидеть сложа руки и ждать два месяца?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Найти хорошего поставщика - дело непростое. Я пытался договориться с мелкими дельцами, но они ненадёжны. Порой товар приходит, а порой нет. С крупным же поставщиком всё как по часам - и поставки стабильные, и качество на высоте.";
			link.l1 = "Ну, если с обычными поставщиками такие проблемы, может, стоит поискать у тех, кто работает в тени? Они обычно не подводят, и товар всегда будет в наличии.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Вы же понимаете, "+GetAddress_Form(NPChar)+", таверна на виду у всех. Я не хочу проблем с властями. Если бы товар привёз кто-то с хорошей репутацией, я бы не только купил партию, но и с радостью закрыл глаза на происхождение товара\nВ конце концов, когда проблема настолько серьёзная, кто будет обращать внимание на такие мелочи? Главное - чтобы со стороны не возникло подозрений. Но в долгосрочной перспективе я буду работать только с серьёзными и честными торговцами.";
			link.l1 = "Понимаю. Ну что ж, возможно, я ещё загляну к вам. Любые проблемы решаемы, если подходить к делу с умом.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Капитан, это просто невероятно! Как вам это удалось? Впрочем, не важно. Скажите лучше, что вы хотите за столь роскошную партию алкоголя? И всё ли будет в порядке с документами?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "С документами? Разумеется, всё в полном порядке. Вы же не собираетесь в них заглядывать?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Проверка чести пройдена", "None");
			}
			else
			{
				link.l1 = "С документами?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Капитан, поймите, мне жизненно важно заполучить эту партию спиртного. Но свобода и репутация для меня не менее ценны. Губернатор беспощаден к теневым дельцам, даже к самым мелким. Если бы о вас отзывались положительно, я мог бы закрыть глаза на отсутствие документов, но сейчас... вы привлекаете слишком много ненужного внимания...";
			link.l1 = "Похоже, пора взяться за добрые дела. Ждите меня, я скоро вернусь.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "На этот раз, пожалуй, я поверю вам на слово. Итак, сколько вы хотите за эту партию?";
			link.l1 = "За каждую десятку бутылок вина я хочу получить по тридцать дублонов, за ром - по пять дублонов. Вся партия из ста бутылок рома и такого же количества вина обойдётся вам в триста пятьдесят дублонов.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Позвольте, капитан! Это же чистой воды грабёж! Да, моё положение и правда безнадёжно, но я всё равно не стану работать себе в убыток!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Пожалуй, я смогу сделать вам скидку. Но это ещё не всё. Я хочу стать вашим поставщиком на постоянной основе. Гарантирую - никаких накладок с поставками не будет. Я арендую склад в Бас-Тере, и вы будете получать товар прямо оттуда, без задержек. Там всегда будет достаточно спиртного, чтобы предвосхитить любого рода перебои. Что до суммы - с учётом скидки она составит двести сорок дублонов. Что скажете?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Проверка пройдена", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Что ж, я готов"+GetSexPhrase("","а")+" уступить в цене до двухсот сорока дублонов за партию, ведь я настроен на долгосрочное сотрудничество. В дальнейшем я смогу полностью удовлетворить все ваши потребности и обеспечить бесперебойные поставки. Что скажете?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Недостаточно развит навык (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "Это всё ещё больше, чем я платил раньше. Но я усвоил урок - стабильность стоит дороже. Я согласен на ваши условия, но знайте: одна оплошность - и я найду другого поставщика. Я должен понимать, за что плачу больше. И ещё. Как вы намерены уладить вопрос с властями острова?";
			link.l1 = "Этим я займусь прямо сейчас. Как только всё будет улажено, вернусь к вам с товаром.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Прошу вас, не затягивайте. Мне не терпится поскорее наполнить кружки моих посетителей.";
			link.l1 = "Не волнуйтесь, я не заставлю вас долго ждать.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "TPZ_Tavern2_7":
			dialog.text = "Всё равно слишком дорого, капитан. Эта цена выше, чем у моего предыдущего поставщика. Даже если я сейчас соглашусь, через пару месяцев мне всё равно придётся вернуться к нему, когда производство будет восстановлено. Я не вижу причин переплачивать.";
			link.l1 = "Понимаю. Хорошо. Моё последнее предложение - двести дублонов. Если вас и это не устроит, значит, нет смысла продолжать разговор.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Ладно, по рукам. Двести меня устроит. Но скажите, как вы намерены уладить дело с властями острова? Как я уже говорил, губернатор крайне бдительно оберегает остров от контрабанды, и не позволит проводить сделки у себя под носом.";
			link.l1 = "Ха-ха, ну, с этим я бы поспорил. Но можете быть спокойны - все бюрократические издержки я намерен"+GetSexPhrase("","а")+" уладить в кратчайшие сроки.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Прошу вас, не затягивайте. Мне не терпится поскорее наполнить кружки моих посетителей.";
			link.l1 = "Не волнуйтесь, я не заставлю себя долго ждать.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Конечно, капитан! Итак, сколько вы хотите за вашу партию?";
				link.l1 = "За каждую десятку бутылок вина я хочу получить по тридцать дублонов, за ром - по пять дублонов. Вся партия из ста бутылок рома и такого же количества вина обойдётся вам в триста пятьдесят дублонов.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Проверка чести пройдена", "None");
			}
			else
			{
				dialog.text = "Сожалею, капитан, но ваша репутация всё ещё оставляет желать лучшего.";
				link.l1 = "Дьявол...";
				link.l1.go = "exit";
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Конечно, капитан, конечно! 240 дублонов, как и договаривались. Возьмите!";
				link.l1 = "Приятно иметь с вами дело! Теперь в таверне снова будет царить изобилие рома и вина.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Конечно, капитан, конечно! 200 дублонов, как и договаривались. Возьмите!";
				link.l1 = "Приятно иметь с вами дело! Теперь в таверне снова будет царить изобилие рома и вина.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Вы мой спаситель, капитан! Я буду ожидать такие же партии каждые две недели. Надеюсь, вы будете строго придерживаться своих обязательств. Второй такой засухи моя таверна не переживёт...";
			link.l1 = "Извольте не волноваться, "+npchar.name+". Мой представитель в городе - Кристиан Делюш. Он будет следить за тем, чтобы ваша таверна не знала недостатка в вине и роме.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Кристиан? Я его знаю, он человек ответственный, но, кажется... Впрочем, не важно. Раз вы всё уладили с властями, думаю, я смогу ему довериться.";
			link.l1 = "Вот и славно. За сим, прошу простить, мне нужно завершить ещё одно дельце в этом городе.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Заходите к нам почаще!";
			link.l1 = "Непременно.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

