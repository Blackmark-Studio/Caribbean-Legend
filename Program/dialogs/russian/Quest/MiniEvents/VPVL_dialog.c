
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			PlaySound("Voice\Russian\Armo02.wav")
			dialog.text = ""+GetSexPhrase("Месье","мадемуазель")+"! Прошу прощения, вы моря"+GetSexPhrase("к","чка")+"?";
			link.l1 = "Я, капитан "+GetFullName(pchar)+", к вашим услугам.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;
		
		case "Lea First Talk":
			dialog.text = "А я Леа. Леа Карно... "+GetSexPhrase("Месье","Мадемуазель")+" капитан, вы давно прибыли? Вы не видели в море рыбацкий баркас 'Баклан'? Видите ли, мой муж... мой муж, Пьер... он вышел в море два дня назад и не вернулся.";
			link.l1 = "'Баклан'? Нет, подобного баркаса я не встречал"+GetSexPhrase("","а")+". Такое название я запомнил"+GetSexPhrase("","а")+" бы. Мне жаль это слышать, мадам. Надеюсь, с вашим мужем всё в порядке и он просто задержался где-то в пути.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'Баклан'? Ха-ха! Это название баркаса или прозвище его хозяина? Хотя какая разница. Я не встречал"+GetSexPhrase("","а")+" ни одного, ни другого.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;
		
		case "Lea First Talk Rep Plus":
			dialog.text = "Я не знаю, что и думать... Он ведь никогда так не задерживался. Всегда возвращался не позднее полудня. А теперь... Что-то случилось. Я это чувствую.";
			link.l1 = "Обратитесь к властям. Они отправят патрульное судно прочесать прибрежные воды.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;
		
		case "Lea First Talk Rep Minus":
			dialog.text = "Я не знаю, что и думать... Он ведь никогда так не задерживался. Всегда возвращался не позднее полудня. А теперь... Что-то случилось. Я это чувствую.";
			link.l1 = "Обратитесь к властям. Они отправят патрульное судно прочесать прибрежные воды.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;
		
		case "Lea First Talk1":
			dialog.text = "Что вы, "+GetSexPhrase("месье","мадемуазель")+" капитан, конечно, я уже обращалась к коменданту. Но что толку-то? Он только развёл руками... Сказал, что у него сейчас нет свободных кораблей, чтобы отправить их на поиски моего мужа\nА я что могу? Только стоять здесь, смотреть в горизонт, ждать... и надеяться.";
			link.l1 = "Ну что вы, мадам Леа. Не стоит отчаиваться раньше времени. Думаю, я смогу выделить день, чтобы помочь вам в поисках.";
			link.l1.go = "Agree To Help";
			link.l2 = "Ну что же вы так переживаете? Может, утренний бриз отнёс его прямо в объятия какой-нибудь очаровательной дамы. Прогуляется немного, надышится свежим воздухом, и вернётся.";
			link.l2.go = "bad joke";
			link.l3 = "Хотите совет? Хватит ломать глаза, вглядываясь в горизонт. Лучше отправьтесь в таверну Ле Франсуа и поищите своего благоверного там. Уж не обессудьте, но, скорее всего, он просто решил взять паузу от семейных забот, а вы делаете из этого трагедию. Удачи вам в ваших поисках.";
			link.l3.go = "Rejection";
		break;
		
		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Месье","Мадемуазель")+" капитан, я... даже не знаю, как вас благодарить... Вы... вы не представляете, что это значит для меня! Все только разводят руками... Но вы... вы готовы помочь. Спасибо вам!";
			link.l1 = "Благодарить меня пока рано. Лучше расскажите, где ваш муж обычно рыбачил. У него было постоянное место или он часто выбирал новые? ";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Очаровательной дамы?! Вы и вправду считаете, что сейчас подходящая ситуация для шуточек? Я чувствую, что он в беде... А вы смеётесь над моим горем!(плачет) Всё на свете сейчас против меня. Никто не хочет помочь... Никто не понимает, как мне сейчас тяжело.";
			link.l1 = "Мадам Леа, ради всего святого, простите мою бестактность. Я вовсе не хотел"+GetSexPhrase("","а")+" вас обидеть! Обещаю, я займусь поисками вашего мужа. Только скажите, с чего мне начать.";
			link.l1.go = "bad joke1";
		break;
		
		case "bad joke1":
			dialog.text = "Вы...? Вы действительно хотите мне помочь?";
			link.l1 = "Разумеется. Это наименьшее, что я могу сделать, чтобы искупить свою непростительную и неуместную шутку.";
			link.l1.go = "bad joke2";
		break;
		
		case "bad joke2":
			dialog.text = "Спасибо вам, "+GetSexPhrase("месье","мадемуазель")+" капитан. Спасибо... Право, вы застали меня врасплох, даже не знаю, что сказать...";
			link.l1 = "Благодарить меня пока рано. Лучше расскажите, где ваш муж обычно рыбачил. У него было постоянное место или он часто выбирал новые?";
			link.l1.go = "Go To Help";
		break;
		
		case "Go To Help":
			dialog.text = "Ну... Пьер... Он редко говорил, где именно рыбачил. Называл это 'своей тайной'. Но если это поможет его найти... Может быть... Не знаю... Вы ведь действительно хотите помочь, "+GetSexPhrase("месье","мадемуазель")+" капитан? Правда?";
			link.l1 = "Вы сомневаетесь, стоит ли мне говорить о секретном месте вашего мужа? Уверяю, ваш семейный секрет останется между нами, даю вам слово капитана. Мне нужно знать, где это место, чтобы понимать, откуда начинать поиски.";
			link.l1.go = "Go To Help1";
		break;
		
		case "Go To Help1":
			dialog.text = "Вы правы, "+GetSexPhrase("месье","мадемуазель")+" капитан... Простите. Это место было так важно для Пьера. Он всегда говорил, что это его единственная тайна, его маленький секрет\nНо я знаю, где оно. Если это поможет найти его... Он рыбачил у бухты Ле Марен. Это у южного берега, не так далеко от города. Пожалуйста, найдите его, прошу вас!";
			link.l1 = "Не волнуйтесь, Леа, всё будет хорошо. Я сделаю всё, что в моих силах. Возможно, у него были враги? Ему кто-то угрожал?";
			link.l1.go = "Go To Help2";
		break;
		
		case "Go To Help2":
			dialog.text = "Враги? У Пьера? Да он самый добрый человек на свете! Никому бы он не причинил зла... Он ведь всего лишь простой рыбак. Кому он мог помешать? Я просто не понимаю, что могло случиться... Всё это так странно... и страшно...";
			link.l1 = "Не волнуйтесь, мадам Леа. Я немедленно отправлюсь на поиски. Уверен"+GetSexPhrase("","а")+", с вашим мужем всё в порядке. Я обязательно верну его в ваши заботливые руки. Держитесь.";
			link.l1.go = "Return Lea Exit";
		break;
		
		case "Return back to Lea":
			PlaySound("Voice\Russian\Armo03.wav")
			dialog.text = ""+GetSexPhrase("Месье","Мадемуазель")+" капитан, скажите, у вас есть новости? Вы что-нибудь узнали? Хоть что-нибудь?";
			link.l1 = "К сожалению, пока нет, Леа, но я ищу!";
			link.l1.go = "Exit";
			
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			AddQuestUserData("VPVL", "sSex", GetSexPhrase("","ла"));
			AddQuestUserData("VPVL", "sSex1", GetSexPhrase("","а"));
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Чего вам ещё? Не насмеялись вдоволь над бедной женщиной?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;
		
		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Месье","Мадемуазель")+" капитан! Пьер! Как же я рада вас видеть! Вам удалось его найти!";
			link.l1 = "Леа, позвольте представить - Пьер Карно, собственной персоной. Не могу сказать, что цел и невредим, но уверен: вы и ваша забота исцелите его в кратчайшие сроки!";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;
		
		case "Lea second talk1":
			dialog.text = "Пьер! Пресвятая Дева Мария! Я так за тебя переживала! Где же ты был? Да на тебе же лица нет... Ты весь бледный... Ой! А это что?! Что это за... ужасные раны?! Порезы... и ожоги...";
			link.l1 = "Всё хорошо, моя ненаглядная. Это всего лишь царапины. Я так рад снова тебя видеть! Если бы не капитан... я обязан ему жизнью.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
			
		break;
		
		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Месье","Мадемуазель")+" капитан... я... я даже не знаю, как вас благодарить... вы нашли его! Вы спасли моего Пьера! Спасибо вам... спасибо за всё! Пусть Господь хранит вас, "+GetSexPhrase("месье","мадемуазель")+" капитан!";
			link.l1 = "Ну ладно вам, ладно. Сейчас куда важнее, чтобы Пьер хорошенько поел и отдохнул.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			PlaySound("VOICE\Russian\EvilPirates10.wav");
			dialog.text = "Ну наконец-то ты явил"+GetSexPhrase("ся","ась")+", "+GetSexPhrase("пёс","шельма")+"! Ну и где тебя носило? Мы уже три дня торчим на этом пляже, изнывая от жары! Где наш груз?!";
			link.l1 = "Похоже, без меня бал не начнётся, верно, господа? Что ж, немного припозднил"+GetSexPhrase("ся","ась")+", но лучше ведь поздно, чем никогда!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Это вы мне? Хм, может, для начала научитесь вежливости, а уж потом будете задавать вопросы?";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Получен опыт", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Получен опыт", SKILL_FORTUNE);
		break;
		
		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			PlaySound("VOICE\Russian\citizen\Pirati v Gorode-12.wav");
			dialog.text = ""+sld.name+", ты что, совсем дубина безмозглая?! Глаза раскрой, дурень - это вообще не наш человек!";
			link.l1 = "Аргх... Ещё одна губернаторская шавка! Как пить дать! Раз уж эта дурёха сама сюда притащилась, швырнём её в пещеру к её дружку. Развлечёмся как следует! А заодно и вытрясем из неё всё, что она знает о задумках своего хозяина.";
			if (pchar.sex == "man")
			{
				link.l1 = "Аргх... Ещё одна губернаторская шавка! Как пить дать! Раз уж этот мерзавец сам сюда притащился, швырнём его в пещеру к его дружку. Пусть поглядит, как мы пытать умеем. Быстро язык развяжет и выложит все грязные замыслы своего хозяина!";
			}
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			dialog.text = "Ты чего там уже размечтался, животное? Слюни-то подтяни! Лучше загоним её... сам знаешь кому. Он за такую деваху мешок монет отвалит, а мы потом месяц кутить будем!";
			if (pchar.sex == "man")
			{
				dialog.text = "Ну и на кой ляд нам там ещё одна обезьяна? Поднажмём на его подельника, тот и так всё расскажет. А этого, чтоб не мозолил глаза, прикончим прямо здесь!";
			}
			link.l1 = "Тысяча акул тебе в брюхо, Симон! Ты самый хитроумный контрабандист на всём архипелаге!";
			link.l1.go = "Kontr Le Maren2";
		break;
		
		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {	
				notification("Отсутствует пистолет", "NONE");
				link.l2 = "Если этот самый мозговитый, то мне даже страшно представить, какая дурь в головах у остальных!";
				link.l2.go = "Kontr Le Maren3";
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
				link.l1 = " (Про себя)(Пистоли) Пока эти любители поговорить увлечены своей бессмысленной болтовнёй, у меня есть шанс нанести внезапный удар.";
				link.l1.go = "murder";
				notification("Проверка пройдена", SKILL_PISTOL);
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
			notification("Недостаточно развит навык (20)", SKILL_PISTOL);
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			sld = CharacterFromID("VPVL_contr_2");
			CharacterTurnByChr(sld, CharacterFromID("Blaze"));
			locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Если этот самый мозговитый, то мне даже страшно представить, какая дурь в головах у остальных!";
			link.l2.go = "Kontr Le Maren3";
			
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "Сейчас я тебе язык вырву, "+GetSexPhrase("щенок дерзкий","дрянь вшивая")+", чтобы ты больше не тявкал"+GetSexPhrase("","а")+"!";
			link.l1 = "Вырвешь? Ну что ж, попробуй.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			PlaySound("VOICE\Russian\Ransack_1.wav");
			dialog.text = ""+GetSexPhrase("Месье","Мадемуазель")+"... Простите... Я уже ничего не понимаю... Вы пришли меня убить?";
			link.l1 = "Вы Пьер Карно?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;
		
		case "Pier_1":
			dialog.text = "Да, это я. Вы знаете моё имя?";
			link.l1 = "Разумеется, иначе что бы мне здесь делать...";
			link.l1.go = "Pier_2";
		break;
		
		case "Pier_2":
			dialog.text = "Простите, я ничего не понимаю... Боль и голод лишили меня способности ясно мыслить... Почему пришли сюда?";
			link.l1 = "Всё просто. С тех пор, как вы пропали, ваша преданная жена не отходит от пирса, надеясь увидеть паруса 'Баклана'. Её отчаяние было настолько пронзительным, что я не смог"+GetSexPhrase("","ла")+" остаться в стороне и решил"+GetSexPhrase("","а")+" отправиться на ваши поиски.";
			link.l1.go = "Pier_3";
		break;
		
		case "Pier_3":
			dialog.text = "Моя жена... моя дорогая Леа... Я был уверен, что больше никогда не увижу её...";
			link.l1 = "Теперь всё позади. Она ждёт вас у пирса и не теряет надежды. Давайте выбираться отсюда. Я помогу вам встать.";
			link.l1.go = "Pier_4";
		break;
		
		case "Pier_4":
			dialog.text = "Уф-ф-ф... Простите, "+GetSexPhrase("месье","мадемуазель")+"... мне нужно немного времени... ноги совсем не слушаются, затекли до невозможности... спасибо вам огромное, если бы не вы... Спасибо вам огромное... Если бы не вы... сам Господь вас ниспослал!.. Вы не представились. Как я могу к вам обращаться?";
			link.l1 = " Капитан "+GetFullName(pchar)+". Пока приходите в себя, расскажите, как вы оказались здесь? Вы собирались вести дела с этими... людьми?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;
		
		case "Pier_5":
			dialog.text = "Что вы, капитан. Это не моё ремесло, я простой рыбак. Всё начиналось как хороший день. Я рыбачил на западе бухты. Улов был невероятным\nЯ так торопился раскидать рыбу по бочкам, чтобы закинуть сети снова, что совершенно не заметил, как баркас отнесло к рифам. Борта у него, как скорлупа - хватило небольшого удара - и вода хлынула внутрь. 'Баклан', уже прилично гружёный рыбой, быстро пошёл ко дну.";
			link.l1 = "А дальше вы выбрались на берег, и контрабандисты решили, что вы, губернаторская ищейка?";
			link.l1.go = "Pier_6";
		break;
		
		case "Pier_6":
			dialog.text = "Именно так. Я едва доплыл до берега сквозь эти проклятые волны. Нужно было обсохнуть, немного отдохнуть и собраться с силами, прежде чем отправиться в путь. Всё произошло так быстро... Когда я наконец решился отправиться в город, наткнулся на этих мерзавцев\nОни сразу приняли меня за агента губернатора. Я не успел и слова вымолвить, как уже был связан и доставлен сюда. Они пытали меня и морили голодом два дня, требуя, чтобы я раскрыл всех тайных агентов губернатора и его планы. Но как я мог выдать то, чего не знаю?";
			link.l1 = "С умом эти ребята не подружились, потому на тот свет и отправились. Что ж, теперь всё это позади. Вы свободны. Пора обрадовать вашу жену - она наверняка сильно измотана переживаниями.";
			link.l1.go = "Pier_7";
		break;
		
		case "Pier_7":
			dialog.text = "Как же я хочу поскорее её обнять. Кажется, я уже могу идти.";
			link.l1 = "Тогда не будем терять времени.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddQuestUserData("VPVL", "sSex", GetSexPhrase("ся","ась"));
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Капитан, приходите завтра вечером к шести в таверну. Я не прощу себе, если не поблагодарю вас как следует. Сейчас... сейчас я не могу найти всех нужных слов, чтобы выразить свою благодарность должным образом. Пожалуйста, приходите. Для меня это очень важно.";
			link.l1 = "Хорошо Пьер, не волнуйтесь, я приду.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;
		
		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;
		
		case "PierTalkTavern":
			PlaySound("VOICE\Russian\Fisher01.wav");
			dialog.text = "Капитан! Вот и вы! Присаживайтесь.";
			link.l1 = "С удовольствием!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // На всякий случай
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;
		
		case "PierTalkTavern1":
			dialog.text = "Поднимем же кружки за ваше здоровье!";
			link.l1 = "Ну, не только за моё, но и за ваше! Вы уже выглядите куда лучше, чем тогда в пещере. Вздрогнем!";
			link.l1.go = "PierTalkTavern2";
		break;
		
		case "PierTalkTavern2":
			dialog.text = "Капитан, позвольте выразить свою бесконечную благодарность! Вы не прошли мимо, не отвернулись и помогли совершенно незнакомому человеку, обычному рыбаку. Ваше благородство достойно восхищения и я хочу отблагодарить вас всем, что имею. Вот. Возьмите. Здесь двадцать кусочков янтаря и пять кусков редкого голубого янтаря. Их я выловил у одного затонувшего судна. Теперь это ваше. А ещё я хочу отдать вам свои корабельные принадлежности. Пока я не обзаведусь новым судном, они мне ни к чему.";
			link.l1 = "Благодарю вас, Пьер, мне они очень пригодятся. Но главное, что вы снова дома, и ваша жена больше не будет жить в тревоге. Теперь у вас всё наладится.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Пьер, спасибо за щедрость, но оставьте всё это себе. Вам оно сейчас нужнее - лодку чинить, оснастку покупать, сети, бочки. А мне хватит вашей благодарности и того, что вы с женой снова вместе. Берегите друг друга!";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "До сих пор не верится, что всё это случилось со мной. Выпьем за новую главу в жизни моей семьи и за ваше благородство, капитан!";
			link.l1 = "И за удачу, Пьер. Она всем нам не помешает!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;
		
		case "PierWontGift1":
			dialog.text = "Капитан, я просто не могу оставить это так... Вы спасли мне жизнь, и я обязан вам всем. Раз вы отказываетесь принять янтарь и другие подарки, позвольте хотя бы научить ваших людей ловить рыбу на мелководье. Это даст им свежую еду, а вам поможет сэкономить на провианте. Что скажете?";
			link.l1 = "А это отличная идея! Как говорится: не корми хлебом даром, а научи пахать, и сам наестся, и других накормит.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;
		
		case "PierWontGift2":
			dialog.text = "Мудрые слова, капитан! Я рад, что могу быть полезен. Ну, по кружечке?";
			link.l1 = "За ваше здоровье и благополучие, Пьер!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Прошло четыре часа...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
			int foodDays = CalculateShipFood(&pchar);
			dialog.text = "Забористый! Чувствую, ещё чуть-чуть, и я... ик... уже буду готов песню затянуть! Да так, чтоб на весь город слышно было!";
			link.l1 = "Ну, Пьер, песню-то лучше приберечь... на потом, на другую встречу. А то... ик... меня ведь тоже разогреете. А мне... э-э... в путь пора, дела... вроде... ждут! Берегите себя... ик... и жену!";
			link.l1.go = "PierTalkTavern4";
			WaitDate("", 0, 0, 0, 4, 10);
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			notification("Потребление провианта на корабле -15%", "None");
			}
			else
			{
			dialog.text = "Забористый! Чувствую, ещё чуть-чуть, и я... ик... уже буду готов песню затянуть! Да так, чтоб на весь город слышно было!";
			link.l1 = "Ну, Пьер, песню-то лучше приберечь... на потом, на другую встречу. А то... ик... меня ведь тоже разогреете. А мне... э-э... в путь пора, дела... вроде... ждут! Берегите себя... ик... и жену!";
			link.l1.go = "PierTalkTavern4";
			LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
			
		break;
		
		case "PierTalkTavern4":
			dialog.text = "Эх, капитан... ну вы это... спасибо вам за всё! Я вам обязан, слышите? Как вдруг тут будете... мы... мы вам всегда рады, как... как родно"+GetSexPhrase("му","й")+"! Честное слово! Эх... выпьем ещё когда-нибудь!";
			link.l1 = "Ну, Пьер, держитесь тут... а я... ик... я пойду, пока ноги ещё слушаются!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;
		
		case "Exit2":
			DialogExit()
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;
		
		case "RepeatTavern":
			dialog.text = "Пе-е-й, за море-е-е, и за ветер... ик... за рыбацкий  пу-у–уть наш на рассвете!.. Дьявол, а что же там дальше? Капитан!.. Вы всё ещё здесь? Трактирщик... ик... лучший ром на этот стол!";
			link.l1 = "Уже ухожу, Пьер! Ик... пока я в состоянии найти свой корабль!";
			link.l1.go = "Exit";
		break;
		
		case "MeetingInTneCity":
			PlaySound("VOICE\Russian\Fisher03.wav");
			dialog.text = ""+pchar.name+"! Как же рад вас видеть! Ну, может, по кружечке рому, а? За встречу!";
			link.l1 = "И я рад"+GetSexPhrase("","а")+" видеть вас, Пьер. Но, боюсь, в этот раз придётся отказаться. Дел ещё невпроворот, а голова должна быть ясной. Может, как-нибудь в другой раз?";
			link.l1.go = "MeetingInTneCity1";
		break;
		
		case "MeetingInTneCity1":
			dialog.text = "Конечно-конечно, капитан. Сперва дела, потом отдых. Ну, надеюсь, ещё встретимся, и тогда непременно выпьем!";
			link.l1 = "Обязательно, Пьер. До встречи!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;
		
		case "ExitRepeat":
			PlaySound("VOICE\Russian\Fisher02.wav");
			dialog.text = "Капитан! Вы уже освободились?";
			link.l1 = "Увы, Пьер. Дела не отпускают, к сожалению.";
			link.l1.go = "Exit";
		break;
	}
}   