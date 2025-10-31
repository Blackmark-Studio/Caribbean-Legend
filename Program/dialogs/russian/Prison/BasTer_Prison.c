// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			// --> Тичингиту
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
            {
                link.l1 = "У вас под стражей содержится некий индеец, которого схватил Фадей Московит. Можно мне взглянуть на него?";
                link.l1.go = "Tichingitu";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
            {
                link.l1 = "Скажите, вы действительно собираетесь повесить этого индейца? Не слишком ли суровое наказание за столь мелкое прегрешение?";
                link.l1.go = "Tichingitu_3";
            }
			if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
            {
                link.l1 = "Это опять я, комендант. Фадей Московит написал прошение о помиловании индейца. Вот оно.";
                link.l1.go = "Tichingitu_6";
            }
			// <-- Тичингиту
			//Jason --> Бесчестный конкурент
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Я приш"+GetSexPhrase("ёл","ла")+" к вам по просьбе хозяина местного магазина, его зовут "+pchar.questTemp.Shadowtrader.Tradername+". Он просил передать вам вот это письмо.";
				link.l1.go = "Shadowtrader_prison";
			}
			
			if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
			{
				link.l1 = "Это опять я. У меня есть веские доказательства того, что "+pchar.questTemp.Shadowtrader.Tradername+" прав.";
				link.l1.go = "Shadowtrader_prison2";
			}
			//Jason <-- Бесчестный конкурент
			//Sinistra --> Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
            {
                link.l1 = "Я ищу человека по имени Лонгвэй. Я слышал, что вы тоже его разыскиваете, месье офицер. Вам ещё не удалось его найти? Или, может, у вас есть какие-нибудь зацепки?";
                link.l1.go = "PZ_IshemLongway_1";
            }
			//Sinistra <-- Путеводная звезда
		break;
		
		// --> Тичингиту
		case "Tichingitu":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			dialog.text = "А-а, Фадей и вам рассказал свою историю? Не вижу причин препятствовать вам, месье. Вы не первый, кто приходит смотреть на этого краснокожего. Хотя дней через десять на него смогут полюбоваться все жители нашего города, когда мы его вздёрнем сушиться на солнышке...";
			link.l1 = "Так я могу пройти в казематы?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Я же говорю - не вижу причины отказывать вам. Проходите.";
			link.l1 = "Спасибо!";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "Tichingitu_3":
			DelLandQuestMark(npchar);
			dialog.text = "Месье, вы, наверное, недавно прибыли к нам из Европы? Вы не понимаете ситуации в наших колониях. Эта казнь послужит уроком всем остальным краснокожим негодяям, осмелящимся посягнуть на имущество французских колонистов. Кроме того, на этом настаивает Фадей, а он очень уважаемый человек в нашем городе и близкий друг губернатора.";
			link.l1 = "Неужели никак нельзя смягчить наказание? Я всё равно считаю, что это неоправданно сурово...";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ох, молодой человек, не вдавайтесь в философию! Если вас так задел этот вопрос - отправляйтесь к Фадею Московиту и просите за индейца именно его. Если Фадей напишет ходатайство о помиловании - мы удовлетворим его.";
			link.l1 = "Я всё понял, офицер. Отправляюсь к Фадею.";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Sharlie.Tichingitu = "fadey";
			AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
			QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
			RemoveItems(pchar, "letter_1", 1);
			dialog.text = "(читает) Хм... Странный этот Фадей: сначала требует показательной казни, а теперь просит отпустить индейца... Ну да ладно, видимо, у всех губернаторских друзей подобные причуды. Хорошо, можете идти к камере и забирать этого краснокожего.";
			link.l1 = "Благодарствую, офицер!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			AddQuestRecord("Tichingitu", "3");
			pchar.questTemp.Sharlie.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- Тичингиту
		
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_prison":
			dialog.text = "Опять этот "+pchar.questTemp.Shadowtrader.Tradername+" со своими жалобами! Давайте прочтём, что он на этот раз пишет... (читает)";
			link.l1 = "...";
			link.l1.go = "Shadowtrader_prison_1";
			RemoveItems(PChar, "letter_1", 1);
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison_1":
			dialog.text = "Опять эти абсурдные домыслы и ни одного чёткого доказательства! Так. Передайте ему, что этого недостаточно для того, чтобы я поднял стражу на уши и заставил прочёсывать город.";
			link.l1 = "Так и передать?";
			link.l1.go = "Shadowtrader_prison_2";
		break;
		
		case "Shadowtrader_prison_2":
			dialog.text = "Да, именно так, и желательно дословно. Он поймёт, о чём речь. Марать бумагу ради ответа на этот пасквиль я не буду.";
			link.l1 = "Я понял"+GetSexPhrase("","а")+". Всего доброго.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.Trouble = "true";
			NextDiag.TempNode = "First_officer";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "Shadowtrader_prison2":
			dialog.text = "Интересно, и какие же это такие 'веские' доказательства вам удалось добыть?";
			link.l1 = "Я договорил"+GetSexPhrase("ся","ась")+" с контрабандистами о закупке товаров через их неофициальный магазин. Их агент придёт сегодня ночью к портовому управлению, для того, чтобы провести меня в свою так называемую 'лавку'.";
			link.l1.go = "Shadowtrader_prison2_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
			pchar.quest.Shadowtrader_SMG.over = "yes";//снять оба прерывания
			sld = characterFromID("ShadowAgent_1");
			sld.lifeday = 0;
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_prison2_1":
			dialog.text = "Кхм... Отличная работа, капитан! Дальше действовать будем мы - пошлём на встречу своего человека, найдём их убежище и всех арестуем. Благодарю за проявленную инициативу!";
			link.l1 = "Всегда рад"+GetSexPhrase("","а")+" помочь. Уверен"+GetSexPhrase("","а")+", ваша операция пройдёт успешно.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.End.Fort = "true";
			AddQuestRecord("Shadowtrader", "7");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			NextDiag.TempNode = "First_officer";
		break;
		// <-- мини-квест Бесчестный конкурент
		
		// Sinistra - Квест "Путеводная звезда" ==>
		case "PZ_IshemLongway_1":
			DelLandQuestMark(npchar);
			dialog.text = "Кто? Лонг... вэй? Не припомню в последнее время англичан в нашем городе.";
			link.l1 = "Нет, Лонгвэй это... китаец.";
			link.l1.go = "PZ_IshemLongway_2";
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
			DeleteQuestCondition("PZ_BasTerPeshera");
		break;
		
		case "PZ_IshemLongway_2":
			dialog.text = "Так, так. И почему же вы ищете этого вашего Лонгвэя, сударь?";
			link.l1 = "Он мой друг. Я уже слышал о том, что произошло. Это печальное недоразумение, уверяю вас.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Я его ищу, потому что он - известный на Архипелаге преступник.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_IshemLongway_Zashita_1":
			dialog.text = "Ах, недоразумение. Мы не пытались расправиться с ним на месте, если что. Однако этот ваш агрессивный желтокожий порубил в капусту не только нескольких городских стражников, но и вырезал отряды, посланные за ним в погоню в сельве.";
			link.l1 = "Планируете ли вы послать ещё один отряд? Я мог бы пойти вместе с вашими людьми - поговорить с ним, успокоить, чтобы не произошло нового несчастья. Вам ведь было бы достаточно, если эти убийства прекратятся, и Лонгвэй навсегда покинет город?";
			link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;
		
		case "PZ_IshemLongway_Zashita_2":
			dialog.text = "В обычных условиях я бы с вами согласился. На произошедшее можно было закрыть глаза за достойную компенсацию за погибших ребят, вот только среди убитых был один офицер\nМолодой юноша, перспективный младший лейтенант, любимец Его Светлости. А на светских мероприятиях едва ли не все дамы хотели потанцевать с ним. Сказать, что город сейчас в небольшом трауре будет не слишком-то и большим преувеличением. И вот на это уже не получится ни закрыть глаза, ни компенсировать. Понимаете меня?";
			link.l1 = "Понимаю прекрасно. Приношу извинения за действия своего друга. Не смею больше беспокоить.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
			link.l2 = "Вы же и сами знаете, что одному только Богу ведомо, что творится в сельве. Перебить парней там мог кто угодно.";
			link.l2.go = "PZ_IshemLongway_Blef_1";
		break;
		
		case "PZ_IshemLongway_Blef_1":
			dialog.text = "И кто же, по-вашему, мог перебить целый отряд патрульных во главе с офицером?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Вызывающий доверие) Разбойники, кто ж ещё. Стыдно признаться, не хотел вам говорить, но недавно еле ноги унёс от какой-то огромной банды.";
				link.l1.go = "PZ_IshemLongway_Blef_2";
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Но мне-то откуда знать? Кто угодно - разбойники, пираты, лазутчики...";
				link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
			}
		break;
		
		case "PZ_IshemLongway_Blef_2":
			dialog.text = "Хех, оно и немудрено - с вашей-то комплекцией, сударь. Да, есть у нас такие мерзавцы нынче на острове...";
			link.l1 = "Ну вот! Так что они вполне могли толпой расправиться с патрульным отрядом и бедным младшим лейтенантом.";
			link.l1.go = "PZ_IshemLongway_Blef_3";
		break;
		
		case "PZ_IshemLongway_Blef_3":
			dialog.text = "К сожалению, это действительно могли бы быть они.";
			link.l1 = "Именно. Поэтому я ещё раз прошу вас позволить мне присоединиться к новому поисковому отряду - Лонгвэй послушает меня, и так нам удастся избежать новых смертей.";
			link.l1.go = "PZ_IshemLongway_Blef_4";
		break;
		
		case "PZ_IshemLongway_Blef_4":
			dialog.text = "Ну хорошо. Вот только всё равно остаётся одно 'но', сударь.";
			link.l1 = "И какое же?";
			link.l1.go = "PZ_IshemLongway_Blef_5";
		break;
		
		case "PZ_IshemLongway_Blef_5":
			dialog.text = "В отличие от того, что было в сельве, вина вашего... друга в городе очевидна и полностью доказана. Это не останется безнаказанным. Так что эти смерти необходимо компенсировать, если вы хотите, чтобы он покинул город живым.";
			link.l1 = "Справедливо. Сколько это будет стоить, месье офицер?";
			link.l1.go = "PZ_IshemLongway_Blef_6";
		break;
		
		case "PZ_IshemLongway_Blef_6":
			dialog.text = "Триста. Дублонов, само собой - эти деньги будут принадлежать городу, а не дельцам с рыночной площади.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Ну само собой. Пожалуйста, триста дублонов.";
				link.l1.go = "PZ_IshemLongway_Blef_7";
			}
			link.l2 = "Я не брал с собой на этот раз в город дублоны. Но если вы позволите мне за ними сбегать, то...";
			link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;
		
		case "PZ_IshemLongway_Blef_7":
			dialog.text = "Замечательно. Вы доказали свою ответственность. Мы как раз заканчиваем подготовку следующего отряда. Я разрешаю вам к нему присоединиться.";
			link.l1 = "Благодарю! До свидания, сударь.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.PZ_DrugOtryad = true;
		break;
		
		case "PZ_IshemLongway_NetDublonov_1":
			dialog.text = "Я не вчера родился. И не первый день служу. Очевидно же, что вы и правда собираетесь сбегать. Но не за дублонами, а за вашим дорогим китайцем.";
			link.l1 = "Даю вам слово, что не сбегу из города вместе с Лонгвэем.";
			link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;
		
		case "PZ_IshemLongway_NetDublonov_2":
			dialog.text = "Слова, слова... Я устал от вашего трёпа, капитан. Вы никуда отсюда не уйдёте, пока мы сами не поймаем этого проклятого желтокожего.";
			link.l1 = "Что же, я подчинюсь вашему приказу, если пообещаете не убивать Лонгвэя на месте, месье офицер.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Но разве я лично нарушил законы города сегодня?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_1":
			dialog.text = "Значит, не знаете. Тогда я буду придерживаться текущей догадки. Китайца нужно поймать в любом случае.";
			link.l1 = "Текущей догадки? Но ведь у вас нет никаких доказательств того, что в сельве всех перебил именно Лонгвэй.";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;
		
		case "PZ_IshemLongway_Blef_netVD_2":
			dialog.text = "А доказательства его невиновности у вас есть, в свою очередь? Нет? Тогда прекратите делать из вашего желтокожего святого. Поняли меня?";
			link.l1 = "Понимаю прекрасно. Приношу извинения за действия своего друга. Не смею больше беспокоить.";
			link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;
		
		case "PZ_IshemLongway_Uiti_1":
			dialog.text = "Боюсь, что я не могу позволить вам пока что отсюда выйти, сударь.";
			link.l1 = "В каком это смысле? Что вы имеете ввиду?";
			link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;
		
		case "PZ_IshemLongway_Uiti_2":
			dialog.text = "А имею я ввиду то, что, поскольку этот Лонгвэй - ваш друг, то нет никаких гарантий, что вы не побежите за ним на самостоятельные поиски и не попытаетесь скрыться вместе с ним\nА потому я вынужден задержать вас, пока мы самостоятельно не изловим этого желтокожего мясника.";
			link.l1 = "Что же, я подчинюсь вашему приказу, если пообещаете не убивать Лонгвэя на месте, месье офицер.";
			link.l1.go = "PZ_IshemLongway_Arest_1";
			link.l2 = "Но разве я лично нарушил законы города сегодня?";
			link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;
		
		case "PZ_IshemLongway_Arest_1":
			dialog.text = "Не могу ничего обещать. Кто знает, что у вашего друга на уме, и не захочет ли он устроить очередную бойню, едва завидев нас. А пока что - прошу в вашу роскошную комнату на ближайшее время, капитан.";
			link.l1 = "Очень смешно...";
			link.l1.go = "PZ_IshemLongway_Arest_2";
		break;
		
		case "PZ_IshemLongway_Arest_2":
			DialogExit();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;
		
		case "PZ_IshemLongway_Pobeg_1":
			dialog.text = "Поймите, против вас лично я ничего не имею. И вы правы - вы ничего не совершили. Но мы хотим удостовериться, что желтокожий от нас не сбежит.";
			link.l1 = "Поймите тогда и вы, что я не позволю вот так облыжно себя задержать.";
			link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;
		
		case "PZ_IshemLongway_Pobeg_2":
			if (pchar.location.from_sea == "BasTer_Town")
			{
				dialog.text = "В таком случае нам придётся вас утихомирить, сударь.";
			}
			else
			{
				dialog.text = "Мне это всё уже совершенно осточертело! Сержант, ведите отряд к этой треклятой пещере и найдите китайца!!! А этим хлыщом я лично займусь...";
			}
			link.l1 = "Чёрта с два.";
			link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;
		
		case "PZ_IshemLongway_Pobeg_3":
			DialogExit();
			
			LAi_SetHuberType(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
			LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			if (pchar.location.from_sea == "BasTer_Town")
			{
				PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
				PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
				AddQuestRecord("PZ", "10");
				LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
				Island_SetReloadEnableGlobal("Guadeloupe", false);
			}
			else
			{
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
				PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
				AddQuestRecord("PZ", "5");
				
				// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";
				
				LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
				LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
				//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			}
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_1":
			dialog.text = "Охотник, значит? Обычно я не люблю иметь дело с вашим братом, но в данном случае мне как никогда на руку, что наши интересы сходятся. Видимо, это и правда известный малый, чёртов желтокожий. Положил кучу моих ребят - как в городе, так и в сельве, уже не первый отряд отправляем по его душу.";
			link.l1 = "Он и от меня уже не первый раз сбегает - гоняюсь за ним по всему Архипелагу уже некоторое время.";
			link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;
		
		case "PZ_IshemLongway_OhotnikOtryad_2":
			dialog.text = "Проклятый шельмец! Вот как мы тогда поступим. Я собираю очередной отряд, а вы отправляетесь с ними - на этот раз ему некуда бежать, а с вашей помощью шансы на успех будут повыше, полагаю\nОт меня на награду, впрочем, можете не рассчитывать - поскольку вы охотник за головами, сами потом обратитесь к тому, кто вас нанял. Вы и так должны быть благодарны, что я решил позволить вам сотрудничать с нами.";
			link.l1 = "Что ж, ваша правда. До встречи, офицер - если никто из ваших людей не переживёт очередную встречу с нашим китайцем, то я сам сообщу вам, как всё прошло.";
			link.l1.go = "PZ_IshemLongway_BeryomOtryad";
			pchar.questTemp.PZ_OhotnikOtryad = true;
		break;
		
		case "PZ_IshemLongway_BeryomOtryad":
			DialogExit();
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
			DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;
		
		case "PZ_BasTer_ComendantDialog_1":
			dialog.text = "Правильно полагаете. Вы, я так понимаю, знакомы? Кем вы являетесь друг другу?";
			link.l1 = "Он офицер-штурман на моём корабле, и...";
			link.l1.go = "PZ_BasTer_ComendantDialog_2";
			if (pchar.location.from_sea != "BasTer_Town")
			{
				link.l2 = "Я его ищу, потому что он - известный на Архипелаге преступник.";
				link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
			}
		break;
		
		case "PZ_BasTer_ComendantDialog_2":
			dialog.text = "С оружием он управляется явно лучше, чем с картами. Вы хоть представляете, что натворил ваш ручной китаец?!";
			link.l1 = "Если честно, нет, ведь я только причалил и начал поиски. Я уверен, это было недоразумение.";
			link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_1":
			dialog.text = "Именно. Кем вы ему приходитесь, раз он вам так нужен? Хотя... это уже неважно, главное - с какой целью вы прибыли в город, раз уж ищете его.";
			link.l1 = "Ничего противозаконного, сударь. Но что вы имели ввиду под 'это уже неважно'? Неужели он...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_2":
			dialog.text = "Да. Похоронили его за одним из холмов - на кладбище или неподалёку от него святые отцы не разрешили, ибо нехристь. Мы не стали с ними спорить - как-то всё равно.";
			link.l1 = "Как это произошло, если не секрет?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_3":
			dialog.text = "Очень просто - прибыл в город, вынюхивал что-то без конца. Мы пытались поговорить с ним, узнать, что он тут забыл, но он перебил несколько ребят и бежал в сельву\nЯ отрядил за ним несколько поисковых отрядов, один за другим, но он уничтожил их все! Нам пришлось загнать его в ловушку у пещеры и расстрелять.";
			link.l1 = "А вы не знаете, что он искал-то? Видите ли, раньше он подобного не совершал - он когда-то был штурманом на моём корабле. Но затем обокрал меня и сбежал.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_4":
			dialog.text = "Да как-то вылетело из головы, м-да\nЗначит, вы тоже пострадали от его действий? Будет вам урок, капитан - будете знать, кого явно не стоит брать себе на судно. Никогда не доверяйте желтокожим, попомните мои слова!";
			link.l1 = "Да уж, буду иметь ввиду. А вы ничего не находили у него при себе?";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_5":
			dialog.text = "А-а-а, хотите вернуть украденное? Было у него в карманах немного серебра - так что если он вас обокрал основательно, то уже успел всё растратить\nДа бумажки ещё какие-то... Из вашего судового журнала? Мы всё равно ничего не поняли - шифр какой-то, видимо? Всё было залито кровью, разгадать неповреждённые участки не смогли.";
			link.l1 = "Э, да, как раз из него, спасибо вам. Всегда беспокоился, что будет, если мои журналы и дневники возьмёт в руки кто-то другой...";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_6":
			dialog.text = "И придумывать полноценный сложный шифр из-за этого? И не жалко вам было времени и сил? Держите. А насчёт серебра - не обессудьте, вернули городу - уж больно много ребят этот китаец положил.";
			link.l1 = "Тогда не смею настаивать. До свидания.";
			link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;
		
		case "PZ_BasTer_ComendantDialog_Opozdal_7":
			DialogExit();
			
			LAi_SetHuberType(npchar);
			AddQuestRecord("PZ", "9");
			CloseQuestHeader("PZ");
			bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
