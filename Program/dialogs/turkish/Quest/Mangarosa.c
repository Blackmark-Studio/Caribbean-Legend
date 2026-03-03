// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "Evimde ne istiyorsun?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Adın Amelia, değil mi? Sana bir bitki hakkında bir şey sormaya geldim. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Sana henüz anlatacak bir şeyim yok. Ama bir gün geri döneceğim...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "İlginç! Peki sana benden kim bahsetti, cesur genç adam?";
			link.l1 = "Senin insanlarından biri. Bu bitkinin sırlarını bildiğini ve ondan özel iksirler yapmayı bana öğretebileceğini söyledi...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Önce, bahsettiğin bitkiyi bana göster. Belki de hakkında hiçbir şey bilmiyorsun ve sadece vaktimi harcıyorsun. Manga Rosa'n nerede?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Al, bir bak.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "Ve bana ne gösterecektin? Manga Rosa sende yok. O yüzden defol git dostum, sinirlerimi bozmadan önce. Bu konuşma burada bitti.";
			link.l1 = "Ama...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Yine sen mi? Sakın sorun çıkarma, oğlum...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Sakin ol, Amelia. Geçen sefer bir yerde düşürmüş olmalıyım. Bak, sana Manga Rosa getirdim. Bir bak istersen.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Bakalım... Görünen o ki bu konuda bir şeyler biliyorsun. Peki, iksirlerimin sırlarını sana anlatmamı ister misin?";
			link.l1 = "Aynen öyle. Ve anladığım kadarıyla, bu bedava olmayacak...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Doğru anladın, delikanlı! Tam bir aptal gibi de görünmüyorsun. Bilgi arayan ve bu nadir bitkiyi boş sigara işlerine harcamayan birine bir şeyler öğretebilirim...";
			link.l1 = "Amelia, pazarlığa başlamadan önce... bana Manga Rosa'dan yapabileceğim iksirler hakkında temel birkaç bilgi verir misin?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Pazarlık yok, dostum. Fiyatı ben söyleyeceğim ve ödeyip ödememek sana kalmış. İndirim ya da pazarlık bekleme, burası pazar değil. Soruna gelince... Manga Rosa'nın özel iksirlerini hazırlayabilirsin, bunlar fiziksel yeteneklerini güçlendirir. Daha güçlü, daha dayanıklı ya da daha hızlı olmanı sağlayabilirler, ya da bedenini tamamen değiştirip her açıdan daha kuvvetli yapabilirler, fakat böyle bir iksir önceki ikisinden daha zayıf etki gösterir.";
			link.l1 = "Çok ilginç. Fiyatını söyle.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Sana üç tarif öğretebilirim. Her tarif için bir bitki ve beş yüz altın isterim.";
			link.l1 = "Bana bu iksirler hakkında daha fazla anlat. Her biri ne işe yarıyor?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "You must be a master of the art of alchemy if you wish to brew even a single potion. Each potion lasts for two days or less, depending on when you drink it; if you take it at midnight, it will last nearly two full days\nThe first potion increases your strength and endurance. You will fight better, take less damage, and carry more weight\nThe second potion will make you swifter, more agile, tireless, and it will also improve your aim\nThe third potion has effects half as strong as both previous potions. But it also grants you charm, self-confidence, and luck as well\nAll Manga Rosa-based potions have a positive effect on your health. You must drink only one potion at a time; never mix them, otherwise they will do you no good—on the contrary, you will suffer severe poisoning\nSo, handsome, are you ready to pay for the knowledge right now, or do you need time to think?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Evet, hazırım.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Biraz düşünmem lazım. Bu, verilecek büyük bir karar.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ah, demek sensin, delikanlı! Peki, iksirlerim sana yardımcı oldu mu?";
				link.l1 = "Gerçekten öyle yaptılar, Amelia. Teşekkür ederim!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, sen misin, delikanlı! Biraz tarif almak ister misin?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Kesinlikle. İşte bu yüzden buradayım.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Henüz değil, Amelia. Sadece seni ziyarete geldim.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Pekala. Ne tür bir tarif almak istersiniz?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "Güç ve dayanıklılık iksirinin tarifi.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "Çeviklik ve yorulmazlık iksirinin tarifi.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "Karmaşık bir iksir tarifi.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Pekâlâ. Ona 'Gelgit Dalgası' adını verdim. Al, talimatlar burada. Dikkatlice oku. Ve doğru kullanmayı sakın unutma!";
			link.l1 = "Teşekkür ederim, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Pekala. Ona 'Fırtına' adını verdim. Al, talimatlar burada. Dikkatlice oku. Ve doğru kullanmayı sakın unutma!";
			link.l1 = "Teşekkür ederim, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Pekâlâ. Ona 'Deniz Sarılması' adını verdim. Al, bu talimatları da yanında götür. Dikkatlice oku. Ve doğru kullanmayı sakın unutma!";
			link.l1 = "Teşekkür ederim, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Gerçekten de adder! Pek bir değeri yok, ama bilenler için işe yarayabilir. Bana yüz on üç tane getir, sana sandıklarımdan birini açayım.";
			link.l1 = "Bu kadar taşı ne yapacaksın? Önce neden ihtiyacın olduğunu anlatsan?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "Hayır, canım, eğer bunu sorman gerekiyorsa, bu bilgi henüz sana bir fayda sağlamaz.";
			link.l1 = "Ve açmaya bu kadar cömertçe söz verdiğin sandığın içinde ne var?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "Pek çok şey, el emeğinden kaçınmayan kaptanlar için faydalı. Zamanımı boşa harcama canım, o kadar çakıl taşını zaten toplayamazsın.";
			link.l1 = "Bunu göreceğiz!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ha-ha-ha! Şaka yaptım, canım!";
			link.l1 = "Sana gülecekler, cadı, seni kendi kulübende yaktıklarında!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "Bu benim kaderim değil, sevgili... Beni gururlandırdın! Al, bu sandık artık senin.";
			link.l1 = "Teşekkür ederim, Amelia. Ama umarım orada eski iç çamaşırlarından başka işe yarar bir şeyler de vardır...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
