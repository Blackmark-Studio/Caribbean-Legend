// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Kaybol, dostum. Durduk yere insanlara saldıranlarla konuşacak bir şeyim yok!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Ah! İşte buradasın. Az kalsın seni aramaya çıkacaktım. Sana ihtiyacım var, dostum.";
				link.l1 = "Bugün tuhaf bir şekilde arkadaş canlısısın, Richard. Hadi, söyle bakalım. Ne istiyorsun?";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ne istiyorsun? Açıkçası, bugün pek keyfim yok - aslında, en son ne zaman iyi hissettiğimi bile hatırlamıyorum.";
				link.l1 = "Gerçekten bu kadar kötü mü, dostum?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Ne istiyorsun?";
				link.l1 = LinkRandPhrase("Hey Richard, son zamanlarda bir haber duydun mu?","Adada yeni bir şey oldu mu?","Bana son dedikoduyu anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece moralin biraz düzeldi mi diye bakmak istedim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Kötü mü? Hayır, kötü değil ama iyi de sayılmaz. Yani... ne istiyorsun?";
			link.l1 = "Sadece merhaba demek istedim. Buraya yeni geldim, o yüzden adada dolaşıp insanlarla tanışıyorum.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Gerçekten mi? Peki, öyleyse. Ben Richard Shambon. Uzun zaman önce değerli mallar ticareti yapardım – bazıları yasadışıydı – ama son dokuz yıldır batık gemilerde hurda arıyor, bulduklarımı yiyecek ve altınla takas ediyorum.";
			link.l1 = "Ve ben de "+GetFullName(pchar)+", bir kaptan...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Eski kaptan mı diyorsun, ha-ha!";
			link.l1 = "Well, actually, my ship is in Blueweld now; I sailed here on a barque.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Gerçekten mi? İmkansız! Peki, şimdi teknen nerede?";
			link.l1 = "En altta...";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ah... Ben... Neyse dostum. Biraz rom içmeye gidiyorum...";
			link.l1 = "Bol şans. Seninle konuşmak güzeldi. Bir dahaki sefere görüşürüz.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hey Richard, son zamanlarda bir haber duydun mu?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "Daha önce öyle değil miydim? Hadi ama, herkesin kötü günleri olur! Neyse, adada senin çok iyi bir dövüşçü olduğun konuşuluyor. Söyle bakalım, bu doğru mu?";
			link.l1 = "İnsanlar ne söylüyor bilmiyorum, ama kılıç kullanmayı iyi bilirim.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "İyi. Dinle, "+pchar.name+", sana dış halkadan ve orada bulabileceğin değerli şeylerden bahsettiğimi hatırlıyor musun?";
			link.l1 = "Richard, herkes bana bundan bahsediyor. Görünen o ki, bu adada o yüzüğü aramaktan başka bir eğlence yok - siyasi entrikalar hariç.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Hiçbir söz bundan daha doğru olamazdı, ha-ha! Lafı dolandırmayacağım. (sesini alçaltarak) Dış halkada dokunulmamış bir gemi buldum. Durumu iyi, ki bu burada nadir rastlanan bir şey.\nGemi büyük: bir pinas. Yaklaşık iki ay önce buraya sürüklenmiş. Henüz kimse fark etmedi, bu yüzden onu yağmalayarak güzel para kazanma şansımız var.";
			link.l1 = "Benim seninle gelmemi mi istiyorsun?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Kesinlikle! Pinisin baş kısmı çökmüş, o lanet yengeçler de içeri girip ambarın içinde koca bir yuva kurmuşlar. Onlara fark ettirmeden içeri sızmak imkânsız, su hizasından ana güverteye nasıl tırmanacağımı da hiç bilmiyorum.\nBen iyi bir dövüşçü değilim – yıllardır kılıca elimi bile sürmedim – o canavarları tek başıma asla öldüremem. Bu yüzden sana geldim.";
			link.l1 = "Yani, o geminin içindeki tüm yengeçleri senin için öldürmemi mi istiyorsun...";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Evet. Teklifim şu: Sana geminin yolunu gösteririm, sen yengeçleri temizlersin, orada bulduğumuz ganimeti de paylaşırız.";
			link.l1 = "Hayır dostum, ilgilenmiyorum. Şüpheli bir ödül için yarı batık bir geminin içinde bir yığın yengeçle dövüşmeye değmez. Kendine daha gözü kara bir yardımcı bul.";
			link.l1.go = "ring_exit";
			link.l2 = "İlginç... Uzun zamandır dış halkayı keşfetmeyi düşünüyordum. Anlaştık! Bana enkazı göster, yengeçleri öldüreyim.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Too bad... You're making a mistake; untouched wrecks are a rarity on the outer ring. Oh well, it's your choice. Goodbye...";
			link.l1 = "Hoşça kal, Richard...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Senin hakkında haklı çıktığıma sevindim, dostum. İçeride çok ilginç şeyler bulacağımızı hissediyorum...";
			link.l1 = "Göreceğiz. Orada kaç yengeç olduğunu biliyor musun?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Sanırım dört ya da beş... Yani, gördüklerim o kadar.";
			link.l1 = "Pekala... ne zaman gidiyoruz?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Yarına ne dersin? Hazırlanmak için zamana ihtiyacımız var. Julian Kardeş’ten biraz panzehir al – yengeç çeneleri zehirlidir. Tedbiri elden bırakmamak lazım. Yarın sabah saat sekizde eğik güvertede buluşalım. Nerede olduğunu biliyor musun?";
			link.l1 = "Hayır, nerede?";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "There's an old wreck behind the San Augustine. Her bow is underwater and her rear is raised high; that's why she's called the 'canted deck.' You can only get aboard her by swimming.\nGet into the water on either side of the rop bridge, then swim around either the bow or stern of the San Augustine and climb onto the canted deck. We'll swim to our untouched wreck from there.";
			link.l1 = "Pekala. Yarın görüşürüz!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "Saat sekiz, eğik güverte.";
			link.l1 = "Evet, evet, hatırlayacağım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Ah, işte buradasın, dostum. Biraz yengeç salatası yapmaya hazır mısın?";
			link.l1 = "Tabii!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Pekala. Şimdi başını dış halkaya çevir ve bak. Orada sudan çıkan iki batık gemiyi görüyor musun?";
			link.l1 = "Hm... Evet, onları görüyorum.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Onların arasından dış halkaya bak. Bize doğru burnunu çevirmiş olan kalyonu görüyor musun?";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Evet, sanırım... görüyorum!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "She's our target; our pinnace is hiding behind her. Swim straight and don't turn. I will show you the way from there, and how to get back to the island when we're done.\nThe entrance to the cargo hold is the hole in the pinnace's bow. I won't enter her until you kill all the crabs.";
			link.l1 = "Anlaşmamızı hatırlıyorum. Sen bana yolu göster, ben de yengeçlerle ilgilenirim. Ne dersin?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Yapalım. Seni takip edeceğim.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, aferin sana! Görünüşe göre hepsini hallettin!";
			link.l1 = "Birinin bana açıkça 'dört ya da beş' kişi olduğunu söylediğini çok iyi hatırlıyorum...";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Bak dostum, yoklama yapmadım, sadece delikten baktım. Bilerek yalan söylemem!";
			link.l1 = "Her neyse. Ambarı arayalım mı...?";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Elbette! Zaten bu yüzden buradayız.";
			link.l1 = "Pekala, vakit kaybetmeyelim...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Biraz bekle dostum, bakmak istediğim her yere henüz bakmadım. Daha dikkatli bak, belki daha fazla değerli eşya bulursun.";
			link.l1 = "Peki...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Nothing special. It's a pity that there aren't any high-value goods here; just casks of corned beef and boxes of copra. I did find a case of expensive wine, though. What do you have?";
			link.l1 = "Çok bir şey yok: birkaç değerli eşya, gerisi ise senin de dediğin gibi konserve et ve kopra.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Yeterli değil... Hadi yukarı çıkıp üst güverteleri ve kamaraları kontrol edelim.";
			link.l1 = "Hadi gidelim.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "Lanet olsun! Şuna bak! Şu lanet yengeç pislikleri her yerde! Buraya nasıl çıktılar?!";
			link.l1 = "Sakin ol! Burada kal, kıpırdama ve sessiz ol. Onlarla ben ilgileneceğim...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Ha! Demek kılıç kullanmadaki hünerinle ilgili hikâyeler doğruymuş! Eğer burada tek başıma olsaydım, şimdiye çoktan denize atlamıştım.";
			link.l1 = "Sinirlerin bu kadar çabuk bozuluyorsa, geçmişte nasıl oldu da kaçakçılık yapabildin, ha?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Her şeyden önce, o zamanlar daha genç, daha güçlü ve daha düşüncesizdim. Ayrıca, ben asker değilim – biz kaçakçılar her zaman kan dökülmesinden kaçınmaya çalışırız. Üçüncüsü, benim ustalığım yelken ve dümen kullanmakta, kılıç ya da tabanca değil. Ve dördüncüsü, burada geçirdiğim yıllar beni yumuşattı!\nO yüzden bana kızma. Üst güverteye bakalım. Gemi ciddi bir çatışmaya girmiş gibi görünüyor. Şu hasara bak...";
			link.l1 = "Haklısın. Gemi gerçekten ağır ateş almış. Hadi aramaya devam edelim.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Ve subayların kamaralarına girişleri bulmamız gerekiyor.";
			link.l1 = "O halde vakit kaybetmeyelim. Bir yengeç görürsen bana haber ver!";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Yine hiçbir şey yok! Birkaç parça takı, hepsi bu. Neyse, güvertelerde zaten genelde değerli bir şey bulunmaz. En iyileri mutlaka kamaralarda olmalı. Şurada kaptanın kamarasına bir giriş var. Hadi oraya bakalım.";
			link.l1 = "Dikkatli ol, içeride bizi neyin beklediğini kim bilebilir. Belki de önce benim içeri girmem daha iyi olur?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Hadi gidelim, "+pchar.name+". Artık senin arkana saklanmayacağım.";
			link.l1 = "Devam et o zaman...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "It looks like we got lucky: neither crabs nor other filth in here. But fuck, I'm starting to get angry; I only found a couple dozen doubloons and a few sundries!";
			link.l1 = "Sakin ol. Unutma: değerli eşyalar her zaman kaptanın kamarasında saklanır. Bakalım nelerimiz varmış!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Just as I thought! I know the habits of merchants; they like to create secret stashes around the ship and hide their treasures there! The captain of this pinnace was a cunning rogue, but I won't be so easily cheated! Look what I found!";
			link.l1 = "Göster bana!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Kırk bin peso, iki sandık dolusu altın, bir tomar zümrüt ve bir yığın mücevher! Sahibinin epey zengin olduğu belli. En azından emeğimizin karşılığını alacağız, ama ben daha fazlasını bulmayı umuyordum. Hadi ganimeti paylaşalım.";
			link.l1 = "Harika, Richard. En azından elimiz boş dönmeyeceğiz!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received 25 emeralds");
			Log_Info("You have received  a collection of jewels");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pekâlâ, güvertelerde bulduğumuz şeyleri kendimize saklayalım. Senin için de uygunsa tabii. Sandıklarda ya da dolaplarda güzel bir şey bulabildin mi?";
			link.l1 = "Birkaç Hint eseri, muskalar, belgeler ve benzeri şeyler.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Hepsini kendine sakla. Sonuçta en tehlikeli işi sen yaptın.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Pekâlâ. Ve işte senin gibi bir hazine avcısının işine yarayabilecek bir şey: Kaptanın günlüğünü o masanın üstünde buldum. Anlattığı hikaye çok hüzünlü, ama arayışımızda bize yardımcı olabilir. Ambarın bir yerinde altınla dolu gizli bir sandık varmış! Al, oku!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Pekâlâ. Ama bir şey daha buldum: kaptanın günlüğü.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Buna itiraz etmeyeceğim, ha-ha! O halde, geri dönme zamanı mı?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Yes. Don't tell anyone about the ship; it'll be our secret. Sure, we don't need copra, but all that food will be useful; we won't have to buy from the Admiral anymore.";
			link.l1 = "Pekala, kabul ediyorum. Umarım başkaları bu gemiyi yakın zamanda bulmaz. Hadi gidelim!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Okudun mu?";
			link.l1 = "Henüz değil...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Hadi okuyalım! Belki de önemli bir şey öğreniriz. Ayrıca geminin buraya nasıl geldiğini bilmek de ilginç olurdu. Oku şunu!";
			link.l1 = "Hm. Peki, şimdi okuyacağım...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Okudun mu? İçinde ne yazıyor?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Yaptım. Bak, hikaye çok üzücü ama kargo ambarında altın dolu gizli bir sandık olduğunu ortaya çıkarıyor! Oku, belki nerede olduğunu çözebilirsin.";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Bir saniye bekle. Okuyup sana söyleyeceğim...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Gerçekten mi? "+pchar.name+", ben... şey, pek iyi okuyamam. Orada ne yazıyor, bana söylesene, ha?";
			link.l1 = "Kısaca: Bu pinas, Yeni İspanya kıyılarını takip ederek Karayip Denizi'ni güneyden kuzeye geçiyordu. Yolculuk sırasında kaptan, Aşağı Orinoko kabilesinden bir yerli prensesine âşık oldu ve onunla evlendi. Prenses ona, halkının kurban törenleri yaptığını anlattı...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Kurbanları altın külçeleriydi! Tabii ki kaptanımız, birinci yardımcısı ve çeyrekbaşıyla birlikte altınları çaldı. Altınları ambarın içinde bir sandığa koyup üstünü kopra ile örttüler...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "Ama anlaşılan o kutsal Hintli mekânın yağmalanması cezalandırılmış: gemi rüzgarsız kaldı, suyu tükendi, salgın başladı ve korsanlar saldırdı. Denizciler Hintli kızı - kaptanın karısını - suçladılar ve kaptanın onu denize atmasını istediler. Elbette kaptan reddetti ve isyan çıktı...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "Kaptan dövüşü kaybetti. Son yazdıklarına göre, kendisi ve Hintli karısını kamarasına kapatıp kapıyı kırmaya çalışan herkesi vurmuş. Bir fırtınanın üzerlerine geldiğinden bahsediyor - muhtemelen bu fırtına gemiyi Adalet Adası'na sürükledi. Sonunda karısı vurulmuş ve hiç şüphem yok ki isyancılar eninde sonunda onu da öldürdü.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hmm, evet, evet, hüzünlü bir hikaye... ama altın... gerçekten ambarın birinde altın külçeleriyle dolu bir sandık var mı? Hangisinde?! Hadi bulalım! Gerekirse tüm alt güverteyi altüst ederim!";
			link.l1 = "Pekala, pekala, evet, arayacağız – sakin ol, Richard!";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! Buldum işte! Şu parıltıya bak! Koca bir sandık! Burada en az beş bin külçe vardır! Hayatımda bu kadar altını bir arada görmemiştim!!";
			link.l1 = "Tebrikler, dostum. Görünen o ki, tüm çabalarımız karşılığını buldu! Bunca altınla ne yapacağız?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Ne demek istiyorsun? Onu ikiye böleceğiz!";
			link.l1 = "Yani, onu nereye koyacaksın? Burada mı bırakacaksın?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! No, I'll hide the gold in my own private stashes where no one will ever find them. Hiding is the one thing I know well how to do! Let's put half the gold into this barrel - that'll be my share. I'll take it away before sunset.\nYou do whatever you want with you share, but you'd do well to move it into your own stashes, too. Don't blame me if you find your gold missing; I'm an honest man, in my way, and I won't touch your cut. But very soon, others may find this ship, and they won't hesitate to grab whatever they find.";
			link.l1 = "Teşekkürler. Altınımı ne yapacağıma karar veririm. Bu arada, senin payını şu fıçıya koyalım...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later..."+ NewStr() +"The gold was shared!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Bitti... Teşekkür ederim, "+pchar.name+", benimle geldiğin için. Bunu sensiz başaramazdım. Şimdi bir tartana inşa etmeyi düşünmeliyim... buradan yelken açıp gitmek için...\nAh, bunu sonra düşünürüm. Şimdilik, bu altını sakladığım yerlere taşımak başlı başına bir iş olacak. Elveda dostum, umarım payını akıllıca kullanırsın!";
			link.l1 = "Hoşça kal, Richard. Harika bir gündü. Kendine iyi bak!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Soruların mı var? Peki, madem öyle...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adadan ayrılmak mı istiyorsun?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hiç klanlardan birine katılmayı düşündün mü? Mesela Narvaller'e?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dış halkada ilginç şeyler bulabileceğin doğru mu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorular yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "On yıl boyunca ben ve yoldaşlarım, Küba'dan bu adaya gidip gelerek yerel halkla ticaret yaptık. Adanın yerini sır gibi sakladık, taze et, meyve ve sebzeleri batıkların ambarlarından çıkan mallar ve altınla takas ettik. Ne güzel günlerdi!\nAdalet Adası sakinleri için erzak bulmak hep bir sorun olmuştur, bu yüzden baharatlı, sulu etlere bize Avrupa’da servet değerinde ödediler! Her seferinde, Tortuga’daki bütün fahişeleri satın alacak kadar para kazanırdım.\nAma her şeyin bir sonu var. Bu bölgedeki fırtınalar güçlenip sıklaştı, adaya ulaşmak çok daha tehlikeli hale geldi. Mürettebatımın bir kısmı işi bıraktı ama ben ve bir düzine cesur adam yola devam ettik.\nSonunda bir fırtına bizi adadan iki mil uzaktaki resife savurdu. O çalkantılı denizde nasıl yüzüp kurtulduğumu hâlâ anlamıyorum. Şimdi, eskiden ticaret yaptığım o insanların arasındayım.";
			link.l1 = "İlginç bir hikaye...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! Bir gün buradan çıkacağım, kahretsin, ama bir sefalet içinde değil! Küba'da ne yapardım ki? Hiç dostum kalmadı, ceplerim de bomboş.\nTek ihtiyacım, dış halkada ambarı değerli yükle dolu bir gemi ya da bir yığın doblon bulmak. Sonra yeni bir tartana inşa ederim, fırtınaları aşar, medeniyete geri dönerim.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "Neden yapayım ki? Her üç günde bir güneşin altında kavrulup San Gabriel'den insanları uzak tutmak için mi nöbet tutayım? Hem zaten, yerliler dışarıdan gelenleri işe almayı pek sevmezler... Zenciler de aynı. Yani hayır, ben kendi başıma olmayı tercih ederim.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tabii! Buradakiler böyle hayatta kalıyor. Biliyor musun, ne zaman kutlama yaparlar? Yeni bir gemi halkaya çarptığında.\nDış halkada hâlâ keşfedilmemiş, altın ve mallarla dolu birçok enkaz var, ama oraları araştırmak çok tehlikeli. Ortalık karmakarışık, tek başına gitmek istemezsin. Bir halata dolanırsan ya da kayıp düşersen, işin biter. Birçok insan bu şekilde öldü.";
			link.l1 = "Hm... O zaman dikkatli olacağım.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hey, ellerini ganimetimden çek, hırsız!","Bu adada kimseye güvenilmez! Silahını çek, hırsız!","Deniz sandığıma dokunma, seni alçak!");
			link.l1 = "Defol!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Masum bir kadını soymak mı?! Bununla paçayı sıyıramazsın!";
			link.l1 = "Aptal kız!";
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
			dialog.text = LinkRandPhrase("Silahını indir. Beni tedirgin ediyorsun.","Eğer o kılıcı kullanmayı düşünmüyorsan, yerine koysan iyi olur.","Şu silahı indir, insanları korkutuyorsun - beni de dahil!");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Üzgünüm...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Eğer o kılıcı kullanmayı düşünmüyorsan, yerine koysan iyi olur.","Silahını indir. Beni tedirgin ediyorsun.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Silahını indir. Beni tedirgin ediyorsun.","Şu silahı indir, insanları korkutuyorsun – beni de dahil!");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıp götürüyorum.");
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
