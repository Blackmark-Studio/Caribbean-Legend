// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony, sld;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Ne istiyorsun? Ah, sen regatta katılımcısısın! Doğru mu?";
				link.l1 = "Aynen öyle, efendim. Kurallara göre burada kaydımı yaptırmam gerekiyor.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormayı denedin "+GetAddress_Form(NPChar)+"...","Bu soruyu bugün üçüncü kez gündeme getiriyorsunuz...","Bak, eğer liman işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boş ver.","Gerçekten de, üçüncü kez oldu...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Beliz") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Efendim! Regatta kurallarını ihlal ettiniz ve sizi diskalifiye etmek zorundayım. Üzgünüm. Bir sonraki yolculuğa katılamayacaksınız. Port Royal'a zaten bir rapor hazırladım.";
			link.l1 = "Eh... ne yazık! Ama burada yapabileceğim bir şey yok, fazla dikkatlisin. Elveda!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.SecondTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2 переход
			dialog.text = "Sizi kaydedelim, Kaptan "+GetFullName(pchar)+", gemi şu anda "+pchar.Ship.Name+"... Regatta süresinin saat cinsinden ifadesi "+sti(pchar.questTemp.Regata.SecondTransitionTime)+". Tamam, sonucun kaydedildi, yoluna devam edebilirsin.";
			link.l1 = "Rütbemi söyle.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Buradasınız ama geminizi göremiyorum. Nerede?";
			link.l1 = "Üzgünüm efendim. Gemimi hemen limana çekeceğim.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
				if (pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.SecondTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
					pchar.questTemp.Regata.ContraIndex = sTemp;
				}
			}
			if (n==1)
			{
			dialog.text = "Öndesin. Tebrikler! Böyle devam et!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "10");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Sen sonuncusun. Acele etmelisin.";
				link.l1 = "Yoldayım!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "15");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Sen ikincisin. Lider ise "+sName+" gemide "+sShip+". Sanırım hâlâ ondan hızlı olabilirsin.";
					link.l1 = "Teşekkürler! Denerim!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "11");
					}
					else
					{
					dialog.text = "Rütbeniz "+n+". En yakın rakibiniz "+sName+" gemide "+sShip+".";
					link.l1 = "Teşekkürler!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "12");
					if (n==4) AddQuestRecord("Regata", "13");
					if (n==5) AddQuestRecord("Regata", "14");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Portpax = "true";//отметка Порт Принса
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Hispaniola1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Antigua";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "PuertoRico";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "PuertoRico";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//вторая засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Nevis";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Невиса
			pchar.questTemp.Regata.Town = "Sentjons";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			log_info(pchar.questTemp.Regata.ContraIndex);
			pchar.questTemp.Regata.Index = n;
			pchar.quest.Regata_Contra.win_condition.l1 = "location";
			pchar.quest.Regata_Contra.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_Contra.function = "Contra_Regata";//контрики с пушками
			pchar.quest.Regata_Padre.win_condition.l1 = "location";
			pchar.quest.Regata_Padre.win_condition.l1.location = "Sentjons_town";
			pchar.quest.Regata_Padre.function = "Padre_Regata";//падре в Сент Джонсе
			sld = characterFromId("SentJons_Priest");
			LAi_RemoveLoginTime(sld);
		break;
		//регата

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
