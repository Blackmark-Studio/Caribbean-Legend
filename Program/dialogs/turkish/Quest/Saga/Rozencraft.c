// Михаэль Розенкрафт - голландский капитан, квестовый покупатель бакаута
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "rozencraft":
			if (pchar.questTemp.Saga.Oyster == "cantalk")
			{
				dialog.text = "Hm... Molligan nerede peki? Hani kendisi benimle görüşmek istemişti?";
				link.l1 = "Zavallı Paul'umuz ateşler içinde. Ticaret yapacak hali yok. Onun yerine ben buradayım.";
				link.l1.go = "rozencraft_1";
			}
			else
			{
				dialog.text = "Ne istiyorsunuz, efendim?";
				link.l1 = "Sanırım demir ağacı almak için bekliyorsunuz?";
				link.l1.go = "rozencraft_no";
			}
		break;
		
		case "rozencraft_no":
			dialog.text = "Kim söyledi sana bu saçmalığı, Bayım? Ben kimseyi ya da hiçbir şeyi beklemiyorum. Gemim Willemstad valisinin emriyle bu bölgeyi devriye geziyor. O yüzden, lütfen gemimden ayrılır mısın, bir yanlışlık olmalı.";
			link.l1 = "Hm... Anlıyorum. Sizi rahatsız ettiğim için üzgünüm.";
			link.l1.go = "rozencraft_no_1";
		break;
		
		case "rozencraft_no_1":
			DialogExit();
			AddQuestRecord("Testament", "8");
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_no_repeat":
			dialog.text = "Bu konuşmayı zaten yapmadık mı, Bayım?";
			link.l1 = "Evet, evet. Zaten gidiyorum ve gemime biniyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "rozencraft_no_repeat";
		break;
		
		case "rozencraft_1":
			dialog.text = "Sen kimsin?";
			link.l1 = "Kiminle ticaret yaptığın umurumda değil mi? Satmak için demir ağacı getirdim. Ne kadar?";
			link.l1.go = "rozencraft_2";
		break;
		
		case "rozencraft_2":
			dialog.text = "Anlaşmaya göre - her biri için kırk dublon.";
			link.l1 = "Hm...";
			link.l1.go = "rozencraft_3";
		break;
		
		case "rozencraft_3":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Dostum, Molligan'la bir anlaşmamız vardı. Bu iyi bir fiyat, daha iyisini bulamazsın. O yüzden pazardaki köylü gibi davranma. Ne kadar demir ağacın var?";
			link.l1 = ""+FindRussianQtyString(sti(npchar.quest.bakaut))+".";
			link.l1.go = "rozencraft_4";
		break;
		
		case "rozencraft_4":
			iTemp = sti(npchar.quest.bakaut);
			if(iTemp >= 90)
			{
				dialog.text = "Harika. Beklediğimden fazlası bu. Al, altın burada. Eğer daha fazla demir ağacı bulursan, Saint Martin'deki meyhaneye git ve... kiminle konuşacağını biliyorsun. Bizim için bir buluşma ayarlayacak. Senin o aptal Molligan'dan çok daha iyi bir ortak olduğunu görüyorum.";
				link.l1 = "Pekâlâ. Anlaştık.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Güzel. Al, altın burada. Eğer daha fazla demir ağacı bulursan, Philipsburg'daki meyhaneye git ve... kiminle konuşacağını biliyorsun. O, benimle iletişime geçer. Görüyorum ki seninle de o aptal Molligan'la olduğu kadar iyi iş yapabiliriz.";
				link.l1 = "Pekâlâ. Anlaştık.";
				link.l1.go = "rozencraft_5";
				pchar.GenQuest.Bakaut = "true"; // генератор сбыта бакаута
				break;
			}
			if(iTemp >= 40 && iTemp < 70)
			{
				dialog.text = "Hm... Daha fazlasını bekliyordum. Peki. Al altınları. Ve Molligan'a söyle, bir dahaki sefere yüz parçadan az getirmesin.";
				link.l1 = "Pekala. Ona söyleyeceğim.";
				link.l1.go = "rozencraft_5";
				break;
			}
			dialog.text = "Benimle dalga mı geçiyorsun? Molligan'la bir anlaşmamız vardı, parti elli parçadan az olmamalı! Defol git ve yeterince toplayana kadar geri dönme.";
			link.l1 = "Pekala, pekala, sakin ol.";
			link.l1.go = "rozencraft_5";
		break;
		
		case "rozencraft_5":
			DialogExit();
			npchar.DontDeskTalk = true; // чтоб не доставал, в генераторе - снимаем
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp < 40) DeleteAttribute(npchar, "quest.bakaut");
			else 
			{
				TakeNItems(pchar, "gold_dublon", iTemp*40);
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
				// считаем, сколько мы должны Свенсону
				int ibak = makeint((iTemp*40-2000)/2);
				sld = characterFromId("Svenson");
				sld.quest.bakaut_sum = ibak; // доля Яна
				AddQuestRecord("Testament", "9");
				AddQuestUserData("Testament", "sSum", iTemp*40);
				AddQuestUserData("Testament", "sSum1", ibak);
				if (CheckAttribute(pchar, "GenQuest.Bakaut")) AddQuestUserData("Testament", "sText", "In addition, if I get ironwood, I will be able to sell it to Michael Rosencraft by having a meeting arranged with his man at the tavern in Philipsburg.");
				pchar.questTemp.Saga = "removebakaut";
				// корабль Розенкрафта сохраняем, в АИ на него будет стоять проверка на попадание
				pchar.quest.Saga_Rozencraft_GetOut.over = "yes"; //снять прерывание
				pchar.quest.Saga_Rozencraft_AfterBattle.over = "yes"; //снять прерывание
				// ставим новое прерывание на потопление Розенкрафта
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1 = "Group_Death";
				pchar.quest.Bakaut_Rozencraft_Die.win_condition.l1.group = "Rozencraft_Group";
				pchar.quest.Bakaut_Rozencraft_Die.function = "Bakaut_RozencraftDie";
				pchar.quest.Bakaut_Rozencraft_Remove.win_condition.l1 = "MapEnter";
				pchar.quest.Bakaut_Rozencraft_Remove.function = "Bakaut_RozencraftRemove";
			}
			NextDiag.CurrentNode = "rozencraft_no_repeat";
		break;
		
	// ------------------------------------генератор сбыта бакаута-----------------------------------------------
		case "bakaut":
			dialog.text = "Ah, eski dostum! Satacak biraz demir ağacın var mı?";
			link.l1 = "Aynen öyle, Michel. Hadi takas yapalım.";
			link.l1.go = "bakaut_0";
		break;
		
		case "bakaut_0":
			dialog.text = "Ne kadarın var? Bana bundan daha az olmayan bir parti lazım "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+".";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Bunu biliyorum. Benim var "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SANDAL))+"  almak için bu kadar hevesli olduğun demir ağacından.";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Maalesef, o kadarım yok.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			if (!CheckAttribute(npchar, "quest.bakaut_angry"))
			{
				dialog.text = "Kahretsin, sana söylemediler mi? Yoksa fareler tahtayı mı yedi? Benim ihtiyacım var "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" ve bir parça bile eksik olmasın. Bir dahaki sefere, ajanım sana ne kadar odun söylerse o kadar getir. Umarım beni bir daha hayal kırıklığına uğratmazsın, yoksa hizmetlerinden vazgeçmek zorunda kalacağım.";
				link.l1 = "Pekala, Efendim, bundan sonra daha dikkatli olacağım.";
				link.l1.go = "bakaut_no_1";
			}
			else
			{
				if (sti(npchar.quest.bakaut_angry) == 1)
				{
					dialog.text = "Beni ikinci kez kandırıyorsun. Bundan hoşlanmıyorum. Bil ki bu son uyarım, bir dahaki sefere hizmetlerinden vazgeçeceğim.";
					link.l1 = "Şu lanet fareler mallarıma zarar vermiş! Sana söz veriyorum, Michael, bu son olacak.";
					link.l1.go = "bakaut_no_1";
				}
				else
				{
					dialog.text = "Ve artık sabrım tükendi! Seninle daha fazla iş yapmak istemiyorum. Defol ve beni unut.";
					link.l1 = "Ama Mösyö...";
					link.l1.go = "bakaut_no_2";
				}
			}
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
		break;
		
		case "bakaut_no_1":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			if (!CheckAttribute(npchar, "quest.bakaut_angry")) npchar.quest.bakaut_angry = 1;
			else npchar.quest.bakaut_angry = sti(npchar.quest.bakaut_angry)+1;
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			AddQuestRecord("Bakaut", "3");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_no_2":
			DialogExit();
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			pchar.quest.Bakaut_Rozencraft_Fail.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Fail.function = "Bakaut_RozencraftDie";
			AddQuestRecord("Bakaut", "4");
			CloseQuestHeader("Bakaut");
		break;
		
		case "bakaut_1":
			iTemp = GetSquadronGoods(pchar, GOOD_SANDAL);
			if (iTemp > sti(pchar.GenQuest.Bakaut.Value)+20)
			{ // перебор
				dialog.text = "Vay canına! Üzgünüm dostum, ama sadece satın alabilirim "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+",   tüm yükünü almak için yeterli param yok. Bir parti daha bekliyordum "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+" parça, her biri kırk dublon...";
				link.l1 = "Pekâlâ. Al "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)+20)+" şimdi, kalanını ise bir dahaki sefere sana satarım.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = sti(pchar.GenQuest.Bakaut.Value)+20;
			}
			else
			{
				dialog.text = "Pekala. Fiyat her zamanki gibi, her parça için kırk dublon.";
				link.l1 = "Bana uyar. Al partini.";
				link.l1.go = "bakaut_2";
				npchar.quest.bakaut = iTemp;
			}
		break;
		
		case "bakaut_2":
			LAi_Fade("", "");
			WaitDate("",0,0,0,1,10);
			dialog.text = "Sizinle iş yapmak bir zevkti. Daha fazla demir ağacı satmak isterseniz yine beklerim.";
			link.l1 = "Tekrar görüşmek üzere, Bayım. İşbirliğimiz benim için oldukça kârlı oldu. Hoşça kalın!";
			link.l1.go = "bakaut_3";
		break;
		
		case "bakaut_3":
			DialogExit();
			iTemp = sti(npchar.quest.bakaut);
			TakeNItems(pchar, "gold_dublon", iTemp*40);
			RemoveCharacterGoods(pchar, GOOD_SANDAL, iTemp);
			npchar.DontDeskTalk = true;
			pchar.quest.Bakaut_Rozencraft_Find.over = "yes"; //снять прерывание
			pchar.quest.Bakaut_Rozencraft_Reset.win_condition.l1 = "MapEnter";
			pchar.quest.Bakaut_Rozencraft_Reset.function = "Bakaut_RozencraftRemove";
			NextDiag.CurrentNode = "rozencraft_no_repeat";
			AddQuestRecord("Bakaut", "2");
			AddQuestUserData("Bakaut", "sQty", iTemp);
			AddQuestUserData("Bakaut", "sDublon", iTemp*40);
			AddQuestUserData("Bakaut", "sDublon1", iTemp*40-iTemp*30);
			CloseQuestHeader("Bakaut");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
