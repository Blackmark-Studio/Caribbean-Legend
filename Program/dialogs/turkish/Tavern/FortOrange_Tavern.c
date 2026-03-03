// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne sormak istiyorsun?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Kasabanıza François Gontier adında bir adam uğradı mı? Ona gerçekten ihtiyacım var.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Dinle dostum, Port Royal'den bir gemi tersanesi için özel bir ipek satın alıyor... öyle sıradan bir ipek değil, sen de duymuşsundur mutlaka. Söylentilere göre, bu ipeği satan biri şu yerleşimde bir yerde yaşıyormuş. Onu bulmak için bir ipucun var mı? Ona bir iş teklifim olacak.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "Yanımda elli doblonum var. Al ve konuşmaya başla.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Evet, vardı. Birkaç gündür burada oda kiralıyordu. Pek hoş biri değildi, söyleyeyim. Ayrıca, sürekli birilerinin onu aradığından şüpheleniyordu. Hep korkulu ve tedirgindi, etrafına bakınıp duruyordu. Onun bu kadar korktuğu kişi siz misiniz?";
			link.l1 = "Hayır, o ben değilim. Biliyorsun, korsanların çok düşmanı olur. Peki, onu nerede bulabilirim? Kendisiyle bir anlaşma yapmaya karar vermiştik ama sanki yer yarıldı da içine girdi.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Kendi gemisiyle denize açıldı. Nereye gittiğini bilmiyorum. Bana bundan bahsetmedi.";
			link.l1 = "Ah, ne yazık! Şimdi onu nerede arayacağım?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Bilmem, dostum. Bilseydim söylerdim.";
			link.l1 = "Pekala, anladım. Başkasına soracağım...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Hıh, eğer dükkânı işleten tüccarımızdan şüpheleniyorsan, sana söyleyeyim, o değil, ipek yelken beziyle işi olmaz. Kaçakçılar da buraya uğramaz, gümrük binası olmayınca onlara gerek yok. Hem zaten burada tüccarımızdan başka kimse ticaret yapmaz. Etrafa bir bak, biz öyle insanlar değiliz, ha-ha!";
			link.l1 = "Ama birisi Port Royal'a ipek sağlıyor - bu inkâr edilemez. Tedarikçinin kim olabileceğine dair bir fikrin var mı?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Port Royal'den kaçakçılar mı dersin? Yoksa başıboş korsanlar mı? Muhtemelen ganimetlerini gizli bir koyda boşaltıyorlardır... Ha! Bir fikrim var, dostum. Buralarda olup biten her şeyi bilen biri var. Eğer onun şüphesi yoksa, ipek tüccarları da yok demektir.";
			link.l1 = "Harika! O adamın adı ne?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Hm... İsmini hatırlamaya çalışıyorum ama nedense bir türlü aklıma gelmiyor...";
			link.l1 = "Hafızanı tazelemek için birkaç akçe nasıl olur?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Bunun yardımcı olabileceğini düşünüyorum... Elli altın dublon bu yaşlı kafayı kesinlikle aydınlatacaktır.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "Anladım. Al, şu paraları.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Anladım. Geri döneceğim...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "Husky Billy is the man you need. He has been living on Jamaica for ages, knows every dog on the streets. Used to be a pirate and a pain in the Brits' asses until he got wounded about three years ago. Now he mostly fishes, hunts sharks, and gathers amber in Jamaica's bays. He leaves his old longboat only to buy more rum and crackers\nYou should look for him in the waters around Jamaica. They say he's sailing on the northern side, all the way to the easternmost point. But chasing a longboat is a fool's errand; you'd better stake out around the southwest corner—they say he's been seen near Cape Negril about once a week. His cockleboat is called 'The Fly Fish'.";
			link.l1 = "Teşekkürler dostum. Altınını hak ettin.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Bol şans, dostum! Umarım aradığını bulursun!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
