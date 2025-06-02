// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Святой отец, я хочу поговорить о дочери Томаса Моррисона.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Святой отец, Томас просил передать, что он примет покаяние, посвятит себя благим поступкам и обеспечит приход новым колоколом - чего бы ему это ни стоило.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Говори, дитя моё, я тебя слушаю.";
			link.l1 = "Я знаю, что вы против того, чтобы цыганка помогала девочке. Но разве можно заставлять отца отвергать хотя бы малейшую возможность спасти свою дочь? Пусть её методы и кажутся сомнительными, но у неё есть знания, которые могут помочь.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_2":
			dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", только Господь в состоянии исцелить девочку. Вера в Его промысел - вот что ведёт нас сквозь испытания. Если Томас будет прилежно молиться, следовать слову Божьему и щедро жертвовать храму, Господь услышит его молитвы и явит свою милость.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Вызывающий доверие) Но ведь даже вы должны признать, что Господь действует через людей. Что, если цыганка - лишь инструмент в руках Божьих? Что если замысел Его так глубок, что нам, простым людям, не дано понять? Пути Господни неисповедимы, ведь так?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Вызывающий доверие", "Trustworthy");
			}
			else
			{
				link.l1 = "Вы вынуждаете отца смотреть, как его дочь медленно угасает, вместо того чтобы позволить ему попытаться её спасти. Разве это милосердие?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Не открыта способность", "Trustworthy");
			}
		break;
		
		case "dwh_pastor_VD_1":
			dialog.text = "Ваши речи, капитан, действительно мудры. Но всё же, я не могу позволить, чтобы ересь проникла в самое сердце нашей паствы и пошатнула веру одного из самых преданных её сыновей.";
			link.l1 = "Ничто не сможет сильнее пошатнуть его веру, чем смерть родной дочери. Если же вы позволите ему использовать любые средства, пусть даже те, которые можно назвать грехом, его вера не ослабнет - напротив, она станет крепче, чем прежде.";
			link.l1.go = "dwh_pastor_VD_2";
		break;
		
		case "dwh_pastor_VD_2":
			dialog.text = "Но... Какой пример это подаст остальным членам паствы?";
			link.l1 = "Пример того, что церковь не карает слепо, а наставляет и ведёт к истинному покаянию. Разве не учит нас Писание, что истинное раскаяние и добрые дела способны искупить грех? Первым шагом к искуплению может стать щедрое пожертвование в казну церкви.";
			link.l1.go = "dwh_pastor_VD_3";
		break;
		
		case "dwh_pastor_VD_3":
			dialog.text = "Быть может, вы и правы, капитан. Я готов дать Томасу этот шанс. Но знайте, если он свернёт с пути истинного, утратив твёрдость своей веры, ответственность падёт и на вас! Что до пожертвований - церковь не нуждается в богатстве, у нас есть всё необходимое. Разве что колокол был повреждён во время нападения испанцев...";
			link.l1 = "Я передам Томасу ваши слова. Благодарю за разговор, святой отец. Да хранит вас Господь.";
			link.l1.go = "dwh_pastor_VD_4";
		break;
		
		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;
		
		case "dwh_pastor_bez_VD_1":
			dialog.text = "Это не бесчувственность, капитан, это вера. Мы отдаём судьбу девочки не на произвол, но в руки Господа Бога. Если Томас будет молиться, верить и смиренно ждать, я уверен, Господь услышит наши мольбы и дарует ей исцеление.";
			link.l1 = "Вам ведь известно, что услугами цыганки пользовалась даже знать этого острова, включая губернатора. И они не отлучены от церкви. Так почему же в случае Томаса вы так категоричны?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;
		
		case "dwh_pastor_bez_VD_2":
			dialog.text = "Конечно, ведаю я об этом, "+GetSexPhrase("сын мой","дочь моя")+". Но они - души заблудшие, не познавшие истинного света Господня. А Томас - опора нашей паствы, один из лучших. Позволить лукавому подточить его веру - значит подставить под удар всю церковь, и я не могу допустить столь тяжкого греха.";
			link.l1 = "Значит, вы отвергаете возможность дать даже маленький шанс? Разве это праведный путь?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;
		
		case "dwh_pastor_bez_VD_3":
			dialog.text = " То, что вы называете спасением, может стать прямой дорогой к гибели. Я знаю это не понаслышке. Когда-то, против моей воли, такая же целительница лечила мою племянницу. Совсем маленькая девочка скончалась в муках, и лишь Господь ведает, не обрекли ли колдовские обряды её душу на вечные страдания. Так что не пытайтесь меня переубедить - это бесполезно.";
			link.l1 = "Хорошо. Если это ваш окончательный ответ, спорить не стану. Да хранит вас Господь.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;
		
		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "dwh_pastor_VD_5":
			dialog.text = "Прекрасно, "+GetSexPhrase("сын мой","дочь моя")+". Новый колокол станет символом его преданности Господу и церкви. Пусть делает что нужно, но помнит, что око Всевышнего бдит над каждым его поступком, и нет в этом мире места, сокрытого от взора Его.";
			link.l1 = "Да будет так, святой отец. До свидания.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



