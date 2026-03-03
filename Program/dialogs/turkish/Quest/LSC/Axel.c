// торговец Аксель Йост
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Şuna bak sen..."+GetFullName(pchar)+" ! Ölümden mi döndün? Bunu nasıl başardın?";
				link.l1 = "Basit: Hiç ölmedim, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, dostum, Narvallarla aranı düzeltmeden seninle iş yapmam. Onlardan başıma dert gelsin istemem. Fazio ile konuş, sana yardımcı olabilir.";
				link.l1 = "Pekala, hemen onunla görüşeceğim.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Seninle konuşmak istemiyorum, dostum. Masum insanlara sebepsiz yere saldırıyor ve onları kavgaya kışkırtıyorsun. Defol git!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, yeni bir yüz! Seni buraya ne getirdi? Gerçi, belki de sormak bana düşmez... Kendimi tanıtayım: Benim adım Axel Yost ve burası da dükkanım. Hoşuna giden bir şey var mı?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+". Ne tür mallar satıyorsun?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! Sizi görmek ne güzel. Almak mı istiyorsunuz, yoksa satmak mı?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Dinle Axel, satılık iyi bir tüfeğin var mı? Sıradan bir askerin misketi değil, yüksek isabetli ve menzilli bir şey arıyorum.";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Dinle Axel, Chad Kapper senden bir fıçı viski getirmeni istedi mi? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Dinle Axel, o aptalla konuşmamı duymuş olmalısın. Hangi boncuğu istedi? Anlamadım.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Evet. Hadi takas yapalım, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Adada yeni bir haber var mı, Axel?","Son zamanlarda adada neler oluyor?","Son zamanlarda ne dedikodular duydun?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Henüz değil. Sadece merhaba demek istedim.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Her türlü şey: iksirler, bıçaklar, ateşli silahlar, cephane, zırhlar, mücevherler, mineraller, büyülü muskalar, tılsımlar, ıvır zıvır, işçilik malzemeleri...\nİnsanlar bana batıklardan buldukları, kendilerine lazım olmayan her şeyi getirirler - sen de aynısını yapabilirsin, çekinme. Tabii ki erzak ya da gemi malzemeleri satmıyorum.";
			link.l1 = "Kulağa hoş geliyor, Axel. Ne göstereceksin bakalım.";
			link.l1.go = "Trade_items";
			link.l2 = "Teşekkürler, Axel, bunu aklımda tutacağım. Hizmetlerine ihtiyacım olduğunda görüşürüz.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Bu herhalde bir şaka olmalı. Bunu soran üçüncü kişisin!\nBende öyle bir silah yok, ama birkaç ay önce Adolf Barbier bana dürbünlü av tüfeğini satmaya çalıştı. Sana söyleyeyim, harika bir silahtı, tam da aradığın şey.\nAma Barbier ona deli gibi bir fiyat biçti, ben de teklifini reddettim.";
			link.l1 = "Gerçekten mi! Peki, Barbier'i nerede bulabilirim?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Hiçbir fikrim yok. Muhtemelen şehirde dolaşıyordur. Sık sık Sancho'nun meyhanesine uğrar, her akşam bir şeyler içmeyi sever.";
			link.l1 = "Teşekkürler! Sanırım onu orada arayacağım. Söylesene Axel, tüfek hakkında senden başka kim bilgi aldı? İlgilenen başkaları olduğunu söylemiştin, kimlerdi onlar?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper and Marcello - also known as Cyclops.\nI have no idea why that girl would be in need of a rifle, but then, our Red Mary is a well-known madcap. A year ago, she bought out tons of gun powder to make mines - 'To stun crabs,' she said. Thank the Lord Donald talked her out of it.\nAnd Marcello wanted to buy a rifle for bird hunting; says he got tired of salted beef. I referred them both to Adolf. I don't know if he sold the rifle to one of them or not.\nAlso... that sly dog Giuseppe Fazio inquired about Adolf recently. Perhaps he wants to buy the stutzen, too.";
			link.l1 = "Görünüşe bakılırsa, epey rakibim var. Peki, gidip Adolf'u bulayım – umarım stutzen'i henüz satmamıştır.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Heh, ona göre büyük inci dediği bu! Herkesten ister durur. Bir tane verirsen, en yakın dostun olursun.";
			link.l1 = "Anladım. Büyük inciler... Teşekkür ederim, Axel. Sıradan boncuklar arayarak kendimi perişan ederdim!";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Evet dostum, aldı. Ama eğer sen de bir fıçı Bushmills almak istiyorsan, seni hayal kırıklığına uğratacağım. Sadece bir fıçım vardı ve onu Chad aldı. Sana İskoç viskisi sunabilirim – en az İrlanda viskisi kadar iyidir, hatta tadını daha çok seviyorum.";
			link.l1 = "Başka bir zaman. Chad senden başka bir şey daha aldı mı?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "No. Oh! He was interested in arsenic, said that there are too many rats on the Tartarus and he wants to get rid of them.\nI don't carry arsenic anymore, haven't needed it since I hired Ole to clean my shop. I gave my reserve to poor Sancho; the rats seemed to have picked up and moved into his tavern. I don't know why rats fear Ole so much...";
			link.l1 = "Belki babası bir kediydi.";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Belki... Neyse, eğer ihtiyacın olursa Sancho'nun arsenik şişesi var.";
			link.l1 = "Pekala, teşekkürler. Hemen onun yanına gideceğim.";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
