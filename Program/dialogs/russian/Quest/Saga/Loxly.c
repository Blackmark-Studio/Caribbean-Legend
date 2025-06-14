// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Я адвокат Альберт Локсли. Представляю своих клиентов в разного рода судебных разбирательствах. Мои услуги недёшевы, но, смею вас уверить, они того стоят.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "У меня возникли серьёзные неприятности с английскими властями.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "У меня возникли серьёзные неприятности с французскими властями.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "У меня возникли серьёзные неприятности с испанскими властями.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "У меня возникли серьёзные неприятности с голландскими властями.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Я крупно переругался с контрабандистами.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Спасибо, к счастью помощь адвоката мне пока без надобности.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "Спасибо, к счастью помощь адвоката мне пока без надобности.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "Вы мне и нужны. Я доверенное лицо некой юной особы по имени Элен МакАртур, родной внучки небезызвестного Николаса Шарпа. После смерти её матери и дяди она единственная наследница своего деда, и претендует на право владения островом Исла-Тесоро, согласно его завещанию. У нас есть обе половины карты покойного, что является условием вхождения в наследство. Сколько вы хотите за то, чтобы помочь Элен стать владелицей острова по закону?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Вам потребовались мои услуги, сэр? Уверяю, вы останетесь довольны результатом.";
						link.l1 = "Да, потребовались. Я доверенное лицо некой юной особы по имени Элен МакАртур, родной внучки небезызвестного Николаса Шарпа. После смерти её матери и дяди она единственная наследница своего деда, и претендует на право владения островом Исла-Тесоро. Сколько вы хотите за то, чтобы помочь Элен стать владелицей острова по закону?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Сэр, я ещё не ознакомился с материалами вашего дела. Приходите позже, как я вам и говорил.";
						link.l1 = "Хорошо.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Сэр, к сожалению, мне потребовалось больше времени, чтобы разыскать нужные бумаги в архивах. Я ещё не готов к разговору. Пожалуйста, приходите позже.";
						link.l1 = "Хорошо.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Сударь, ну что же вы так долго! Теперь всё для вашей доверительницы потеряно. Срок действия завещания истёк, и Исла Тесоро теперь по закону принадлежит английской короне. Теперь там будет военная база."
							link.l1 = "Вот это да!.. Получается, все старания пошли прахом...";
							link.l1.go = "saga_l3";
						}
						else
						{
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							dialog.text = "А, вот и вы, сэр. Я ознакомился с материалами, так что теперь дело за авансом. Принесли деньги?";
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Да, принёс. Вот ваши дублоны.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Прошу простить мою забывчивость - оставил в сундуке на корабле. Сейчас принесу.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Сударь, ну что же вы так долго! Теперь всё для вашей доверительницы потеряно. Срок действия завещания истёк, и Исла Тесоро теперь по закону принадлежит английской короне. Теперь там будет военная база."
							link.l1 = "Вот это да!.. Получается, все старания пошли прахом...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Сэр, вам удалось отыскать что-нибудь доказывающее происхождение вашей доверительницы?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Пока нет. Но я работаю над этим.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Да. Причём у меня на руках доказательства более, чем исчерпывающие.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "А-а, вот и вы, сэр. Рад вас видеть. Признаться, я вас уже заждался. Это и есть ваша доверительница?";
						link.l1 = "Да. Позвольте представить - Элен МакАртур.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Вам потребовались мои услуги, сэр? Уверяю, вы останетесь довольны результатом.";
					link.l1 = "Спасибо, но пока я справляюсь со своими делами сам.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Здравствуйте, сэр. Вы, как я полагаю, принесли мне мой гонорар?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Да, принёс. Вот ваши дублоны.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Знаете что, мистер Локсли, я тут прикинул... В общем, с моей точки зрения, 900 дублонов за вашу работу - это более, чем достаточно.";
					link.l2.go = "saga_38";
					link.l3 = "Мистер Локсли, я всё помню. Принесу немного позже...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Вам потребовались мои услуги, сэр? Уверяю, вы останетесь довольны результатом.";
				link.l1 = "Спасибо, но пока я справляюсь со своими делами сам.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Сударь, вы, наверное, давно не были на суше и не узнавали новостей? Исла Тесоро теперь - военная база английского флота! Да, завещание Шарпа существовало, однако срок, указанный в нём для предъявления прав на остров, истёк, и Исла Тесоро отошёл английской короне. Увы!"
				link.l1 = "Вот это да!.. Получается, все старания пошли прахом...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Девушка претендует на владение целым островом? Гм... Похоже, дело обещает быть непростым. Исла Тесоро - это уже практически английская колония...";
				link.l1 = "Ещё нет. Согласно завещанию, человек, предъявивший обе половинки карты Исла Тесоро руки Николаса Шарпа, становится владельцем острова. У нас есть обе половины карты покойного, что является условием вхождения в наследство. ";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Николас Шарп... Так-так. Прежде чем приступить к делу, мне нужно предварительно посетить архив и ознакомиться с материалами, касающимися Исла Тесоро. Карта при вас?";
			link.l1 = "При мне, но я её вам дам только после того, как мы заключим с вами соглашение. Так что касательно оплаты ваших услуг?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Ваша многоуважаемая персоналия тоже не облегчит дело. Картахена... Будут вопросы.";
			dialog.text = "Как я уже сказал - дело не из лёгких. Доказать права на остров - не то же самое, что отсудить старое корыто или лачугу на берегу. К тому же, Николас Шарп был пиратом, а дела пиратов и их родственников оплачиваются дороже."+sTemp;
			link.l1 = "Вы назовёте мне конкретную сумму, чтобы я наконец знал, из чего мне исходить?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "четыреста пятьдесят";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "тысяча";
			dialog.text = "Сударь, окончательная сумма определится в процессе. Я пока не знаю, насколько сложным он будет. Но размер аванса назову сразу: "+sTemp+" дублонов. В зависимости от того, как пойдут наши дела, эта сумма удвоится или утроится\nПриходите через неделю с деньгами - я изучу архивы и буду во всеоружии. Тогда и заключим с вами соглашение. Вас устраивает?";
			link.l1 = "Мне рекомендовали вас как лучшего адвоката, поэтому устраивает. До встречи через неделю!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("Вы отдали 1450 дублонов");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("Вы отдали 450 дублонов");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Очень хорошо. Я готов вести ваше дело и представлять интересы в суде. Теперь конкретика. Я хорошо поработал в архиве и пообщался с важными людьми. Дело о наследстве Шарпа обещает быть непростым. Хорошо, что вам удалось найти обе половинки карты. Но этого может быть недостаточно\nПосле того, как стало ясно, что Тортуга Англии не по зубам, у полковника д'Ойли большие планы на остров Исла-Тесоро, как на хорошо укреплённую естественным образом будущую военную базу в этом районе.";
			link.l1 = "Но согласно законам Англии при наличии карты у Элен все права на этот остров!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Возможно вы не в курсе, но к своему завещанию покойный Шарп сделал приписку. Наследник, или наследники, обязательно должны носить его фамилию. А у вашей девушки, как я помню, фамилия другая. МакАртур - вы так сказали?";
			link.l1 = "Это фамилия её приёмного отца, но Элен может носить фамилию Шарп, так как является родной дочерью покойной Беатрисс Шарп, дочери Николаса.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Прекрасно! Но кто это сможет подтвердить под присягой? Приёмные родители Элен были лично знакомы с Беатрисс Шарп?";
			link.l1 = "Насколько я понял - нет. Мистер МакАртур считал её дочерью Глэдис, а Глэдис имела дело только с отцом девочки.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Это плохо. Видите ли, в архиве нет даже упоминания о том, что у Беатрисс Шарп были прямые наследники. Возможно, что о рождении ребёнка нет вообще никакой официальной записи. Эдак любой может назваться внуком Шарпа и претендовать на право носить его фамилию.";
			link.l1 = "Но только у Элен есть полная карта Николаса!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Это сильный козырь в её пользу, и его, возможно, было бы достаточно, не имей местная администрация планов на Исла-Тесоро. Образец почерка Беатрисс Шарп есть в архиве, и в идеале нужен какой-то документ, написанный её рукой, который бы подтверждал факт рождения дочери, переданной на воспитание этой самой Глэдис... э-э-э, как её?";
			link.l1 = "Чандлер. Глэдис Чандлер, уроженка Белиза.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Вот именно. Есть у вас возможность найти что-либо подобное? ";
			link.l1 = "Навряд ли. Столько лет прошло. Если верить легенде, отцом Элен мог быть сам капитан Бучер. Быть может, бывший палач Сент-Джонса смог бы что-то сказать по этому поводу. Он был последний, кто видел её отца.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Хм. Это был весьма занятный тип. Звали его, помнится, Раймонд Бейкер. Я имел удовольствие с ним общаться. Весьма неглупый и образованный человек. Ну что же, попытайте счастья на Антигуа, а я продолжу изучение архивов - может, что-нибудь да и всплывёт.";
			link.l1 = "Хорошо. Так и поступим.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Давайте карту Шарпа, и поторопитесь к Бейкеру - возможно, с его помощью вы сможете найти какие-то бумаги отца вашей доверительницы. Может, даже обнаружите подтверждение её родословной. ";
			link.l1 = "Эх, если бы так действительно оказалось. Ладно, до встречи, мистер Локсли.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Вот как? Давайте посмотрим, что же это за доказательства.";
			link.l1 = "Это личное письмо Беатрисс Шарп своему брату, в котором она однозначно утверждает, что родила дочь от Лоуренса Белтропа, известного, как капитан Бучер, и отдала её на кормление молодой вдове Глэдис Чандлер. Вот это письмо, держите...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Сама Глэдис готова подтвердить факт передачи ей малышки под присягой. А также то, что отец девочки представился ей именно как капитан Бучер.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Минуточку! Злостный пират и убийца английских подданных капитан Бучер был повешен в форте Сент-Джонса двадцать лет назад. А Лоуренс Белтроп, протеже Эдварда д'Ойли, трагически погиб совсем недавно. Более того именно его д'Ойли и планировал назначить губернатором Шарптауна!";
				link.l1 = "Ха! Конечно, никто не в курсе... У меня есть письменные показания Раймонда Бейкера, бывшего палача Сент-Джонса, о том, что он под угрозой смерти вынужден был устроить инсценировку казни Бучера! Вот, ознакомьтесь...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Минуточку! Злостный пират и убийца английских подданных капитан Бучер был повешен в форте Сент-Джонса двадцать лет назад. А Лоуренс Бэлтроп жив и здоров, занимает один из лучших особняков Порт-Ройаля. Более того именно его д'Ойли и планировал назначить губернатором Шарптауна!";
				link.l1 = "Ха! Конечно, никто не в курсе... У меня есть письменные показания Раймонда Бейкера, бывшего палача Сент-Джонса, о том, что он под угрозой смерти вынужден был устроить инсценировку казни Бучера! Вот, ознакомьтесь...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Хм. Так-так...";
			link.l1 = "Ловко придумано, правда? Таким образом, Бучер остался жив, вернулся в Англию, где снова стал называться Лоуренсом Белтропом. Под этим именем он и прибыл сюда снова, не узнанный никем.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Но это... Это в корне меняет дело! Если мы предадим гласности письмо Беатрисс, то это фактически означает, что всё это время военный губернатор Ямайки укрывал беглого пирата Бучера, которого должен был немедленно арестовать и предать суду за прошлые преступления!\nА показания Бейкера просто уничтожат любые доводы против! Вот это да! С такими козырями мы обыграем д'Ойли вчистую!";
			link.l1 = "Я очень рад. Полностью полагаюсь в ведении процесса на вас. Да, скажите, а как погиб Лоуренс Белтроп?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Это жуткая история, сэр. Его нашли в собственной спальне с лицом, перекошенным от ужаса. Трудно даже представить, что могло так напугать этого бесстрашного человека. Говорят, он был весь покрыт инеем, как будто месяц лежал на леднике. А всё тело его было в страшных рваных ранах. И ни капли крови! Вы представляете?! Ни капли!";
			link.l1 = "Да, кошмар. Получается, его убили... Но кто?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Неизвестно. К тому же тут всё так запутанно... Гарнизонный лекарь, осматривавший тело, сказал, что ни одна рана не была смертельной. Белтроп умер или от страха, или от боли, или от чего-то ещё. В общем, загадочная смерть.";
			link.l1 = "Понятно... Когда состоится суд?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Тут многое зависит от вас, сэр. Как только вы выплатите мне вторую часть гонорара - 450 дублонов, я подам документы в суд и максимально ускорю начало процесса. Не позже, чем через неделю после вашего взноса, Элен войдёт в права наследства.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Очень хорошо. Держите ваши дублоны.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Да, конечно. Я принесу вам нужную сумму.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Сударь, вы меня поразили! Вы сделали почти всё, остров был у нас практически в руках, но из-за вашей проволочки с оплатой теперь всё для вашей доверительницы потеряно! Срок действия завещания истёк, и Исла Тесоро теперь по закону принадлежит английской короне. Теперь там будет военная база."
				link.l1 = "Вот это да!.. Получается, все старания пошли прахом...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Вы принесли вторую часть гонорара, сэр?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Да, конечно. Держите ваши дублоны.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Прошу простить мою забывчивость - оставил в сундуке на корабле. Сейчас принесу.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Но это... Это в корне меняет дело! Если мы предадим гласности письмо Беатрисс, то это автоматически означает, что Лоуренс Белтроп должен быть арестован, как беглый пират, и вновь осужден на казнь за прошлые преступления!\nА показания Бейкера просто уничтожат его! Вот это да! С такими козырями мы обыграем д'Ойли вчистую!";
			link.l1 = "Я очень рад. Когда состоится суд?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("Вы отдали 450 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Прекрасно, сэр. С вами приятно вести дела. Теперь договоримся так: прибудьте ко мне завтра. Да-да, вы не ослышались - завтра! Я всё-таки лучший адвокат на архипелаге, и у меня большие связи\nПриходите обязательно вместе со своей доверительницей - как вы понимаете, без её участия суд не может состояться. Не опаздывайте и не покидайте город. И если сможете - прихватите последнюю часть гонорара - я полностью уверен в нашей победе.";
			link.l1 = "Хорошо. Мы будем в вашей конторе завтра, мистер Локсли.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "МакАртур? Нет, пожалуй - Шарп! Ну что же, следуйте за мной!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Ну что же, позвольте мне поздравить вас, сэр, и вашу доверительницу. Теперь она полноправная владелица Исла Тесоро. За это стоит выпить шампанского!";
			link.l1 = "Безусловно, мистер Локсли. Ваша речь была просто великолепной. Я думал, полковника д'Ойли хватит удар, когда вы сообщили суду, что капитан Бучер и Лоуренс Белтроп - одно и то же лицо.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Да, мистеру д'Ойли придётся распрощаться с мечтой о военной базе на Исла Тесоро. А что же поделать? Закон - есть закон, и он обязателен для всех, включая уважаемого полковника.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Все бумаги, подтверждающие права Элен на остров в порядке?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Я слышал, как судья отдал распоряжение об аресте Лоуренса Белтропа. Как я понимаю, его теперь ждёт виселица?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Конечно, сэр. Я лично проверил каждую запятую в них. Можете быть уверены - комар носа не подточит.";
			link.l1 = "Очень хорошо...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Что же, я выполнил свою работу. Дело было сложным, но совместными усилиями мы справились. Теперь, сэр, вам остаётся только произвести окончательный расчёт со мной. Я вас не тороплю - понимаю, что сейчас вам было немного не до этого. Но, думаю, в течение недели вы найдёте возможность принести мне 450 дублонов\nКроме того, такой клиент, как вы, может теперь всегда рассчитывать на большие скидки. А сделать я могу немало: у меня связи в столицах всех наций на архипелаге, включая враждебные, так что любая проблема может быть улажена.";
			link.l1 = "Отлично. Буду знать, к кому обращаться.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Положительный результат гарантирую, даже в очень сложных ситуациях.";
			link.l1 = "Вот и славно. А теперь разрешите откланяться - у нас с Элен ещё очень много дел.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "До встречи, сэр.";
			link.l1 = "До свидания, мистер Локсли.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Думаю, да - ведь он же капитан Бучер, разбойник и пират. Однако сейчас его нет в Порт-Рояле - он, на своё счастье, отбыл в глубь острова. Но охота за ним уже началась, и он будет схвачен при первой же возможности.";
			link.l1 = "Понятно... Все бумаги, подтверждающие права Элен на остров в порядке?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("Вы отдали 450 дублонов");
			PlaySound("interface\important_item.wav");
			dialog.text = "Превосходно! Очень приятно вести с вами дело, сэр! Теперь вы можете обращаться ко мне по любым вопросам и рассчитывать на скидки. Проблемы с законом вплоть до награды за голову... Пожалуйста, приходите. Всегда буду рад вас видеть.";
			link.l1 = "Лучше, конечно, обойтись без неприятностей с законом, но... мало ли. Спасибо и до свидания, мистер Локсли.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Вы это сейчас о чём, сударь? Вы решили нарушить условия нашего договора?";
			link.l1 = "Именно. Всю основную работу сделал я. Вы даже не представляете, чего мне стоило достать письменные доказательства. А вы просто подшили бумажки к делу и выступили в суде. Девятисот дублонов за это, я уверен, более, чем достаточно.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Вы разговариваете, как настоящий пират, сударь! Что же, я не обеднею от этих четырёхсот пятидесяти дублонов, а вы не обогатитесь. Но потеряли вы намного больше! А возможно, и ещё потеряете... Немедленно покиньте мой дом и больше никогда здесь не показывайтесь!";
			link.l1 = "Это я и собираюсь сделать. Всего доброго, мистер Локсли.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Я не желаю с вами разговаривать. Убирайтесь, пока я не вызвал стражу!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Сэр, если бы вы пришли ко мне пораньше - мы бы могли выиграть дело, завещание потеряло силу совсем недавно. Мне очень жаль.";
			link.l1 = "Эх, а мне-то как жаль! Ладно, прощайте, мистер Локсли.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+". Рад вас видеть. Вам потребовались мои услуги?";
			link.l1 = "Да. Именно за этим я к вам и явил"+GetSexPhrase("ся","ась")+".";
			link.l1.go = "loxly_1";
			link.l2 = "Нет, к счастью, пока ничего не нужно. Я просто заш"+GetSexPhrase("ёл","ла")+" поздороваться с вами.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Я готов вас выслушать. Какого рода помощь вам нужна?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "У меня возникли серьёзные неприятности с английскими властями.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "У меня возникли серьёзные неприятности с французскими властями.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "У меня возникли серьёзные неприятности с испанскими властями.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "У меня возникли серьёзные неприятности с голландскими властями.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Я крупно переругался с контрабандистами.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Простите, но я передумал"+GetSexPhrase("","а")+"...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Я уже работаю над вашим делом. Всё будет в порядке, уверяю вас.";
			Link.l1 = "Спасибо. Буду ждать!";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Ну, серьёзными неприятностями это никак не назовёшь. Незначительный пустяк. Я без труда улажу ваши разногласия";
			if (iRate > 10 && iRate <= 30) sTemp = "Да, ваша репутация подпорчена, но ничего критичного я не вижу. Я без труда улажу ваши разногласия";
			if (iRate > 30 && iRate <= 60) sTemp = "Да, насолили вы властям изрядно. Придётся постараться, но я уверен, что смогу без сучка и задоринки уладить ваши разногласия";
			if (iRate > 60 && iRate <= 90) sTemp = "И как же это вы так умудрились, сэр? Неприятности не просто серьёзные - они очень серьёзные. Власти так и жаждут заполучить вас в свои лапы. Мне придётся очень постараться, чтобы уладить ваши разногласия";
			if (iRate > 90) sTemp = "Да уж... Ситуация катастрофическая - вы объявлены врагом нации номер один. Это будет крайне сложно, но я всё-таки лучший адвокат на Карибах - я улажу ваши разногласия";
			dialog.text = ""+sTemp+" с "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+". Это обойдётся вам в "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Хорошо, мистер Локсли, я соглас"+GetSexPhrase("ен","на")+". Вот ваши деньги и решите проблему поскорее.";
				link.l1.go = "relation";
			}
			link.l2 = "У меня сейчас нет требуемой суммы. Я зайду позже!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "Приятно иметь с вами дело, "+GetAddress_Form(NPChar)+". Можете спать спокойно - не позже, чем через две недели вы сможете забыть об этой проблеме. Единственная просьба - избегайте ненужных стычек и столкновений с "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl") +", пока я решаю вопрос, чтобы не испортить дело.";
			link.l1 = "Хорошо, я учту ваше предупреждение. Спасибо и до свидания!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "Ну и зачем же вы так сделали? Контрабандисты - неплохие ребята, по-своему честные. А жить-то всем надо, и кушать всем хочется... Ладно, проблема ваша невелика, и обойдётся вам всего в "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Хорошо, мистер Локсли, я согласен. Вот ваши деньги.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "У меня сейчас нет требуемой суммы. Я зайду позже!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Замечательно, я всё улажу. Они будут иметь с вами дела.";
			Link.l1 = "Спасибо!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}