// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Офицер, я тут узнал, что у вас в тюрьме содержится человек по имени Фульк Делюк. Можно ли как-нибудь поспособствовать его освобождению?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Офицер, я снова по поводу заключённого Фулька Делюка. Я купил право на его долг у ростовщика, и теперь хочу, чтобы этого человека передали мне. Вот его долговые бумаги, ознакомьтесь.";
                link.l1.go = "Sharlie_3";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Добрый день, офицер. По поводу месье Делюка...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Держите расписки, и приведите моего человека.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "А, этот моряк? Он взял в долг у нашего ростовщика приличную сумму денег, не вернул её вовремя и, более того - стал скрываться. Однако его быстро нашли. С тех пор он под замком, и пока не выплатит всю сумму - будет сидеть за решёткой.";
			link.l1 = "Хм. Но как же он сможет заработать денег, находясь в тюрьме?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "А это, месье, меня не касается.";
			link.l1 = "Забавно... И сколько же он должен, этот несчастный?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Не знаю. Спросите у ростовщика - он вам подробно всё расскажет.";
			link.l1 = "Понятно. Ну что же, спасибо за информацию, офицер.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("Вы передали долговые расписки");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Хм. Всё верно. Вы действительно хотите, чтобы я освободил этого заключённого?";
			link.l1 = "Да. Иначе как он мне вернёт мои деньги? У меня есть способ заставить его отработать уплаченную сумму.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Хорошо, месье. Я не вижу причин вам отказывать. Делюка сейчас приведут. Но я считаю своим долгом предупредить вас, что этот лис ускользнёт от вас при первой же возможности, так что не питайте на его счёт никаких иллюзий.";
			link.l1 = "Я учту это, офицер. А теперь я бы хотел забрать своего должника.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Да, конечно. Сержант! Привести сюда заключённого Фулька Делюка!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			// замораживаем ГГ
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17"); // 170712
			// создаем штурмана
			ref sld;
			InitFolke("Фульк", "Делюк");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ах-ха-ха! Да уж, теперь в Сен-Пьере ещё долго не иссякнет поток сплетен и анекдотов по поводу идиотской ситуации, в которую вы попали. Однако, я ни в коем случае не смеюсь лично над вами, капитан. Очевидно, что вы стали жертвой стечения обстоятельств. Прошу, проходите. Ваш штурман никуда не денется от непростого разговора, ха-ха!";
			link.l1 = "Смешно. Благодарю вас.";
            link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			pchar.questTemp.jailCanMove = true;
			AddLandQuestMark(characterFromId("Folke"), "questmarkmain");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "(с удивлением смотрит на вас) Ладно, советовать вам что-либо будет явно не к месту. Разумеется, капитан. Сейчас всё сделаем.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("Вы передали долговые расписки");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto17");
			
			sld = CharacterFromID("Folke");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "FolkeStay", -1);
								
			sld = GetCharacter(NPC_GenerateCharacter("Del_Ohranik", "sold_fra_2", "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_prison", "goto", "goto12");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, CharacterFromID("Folke"), "", -1);
			
			StartQuestMovie(true, false, true);
			DoQuestCheckDelay("Del_Turma", 0.1);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
