// Оеларт Котеел - канонир
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
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Gözüm görmesin, efendi. Masum insanlara saldıranlarla konuşacak bir sözüm yok.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Güzel bir gün, efendim! Bu havayı nasıl buluyorsunuz?";
				link.l1 = TimeGreeting()+". Açık denizdeki fırtınalar dışında her türlü havayı severim...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" Bir şey mi istiyorsun? ";
				link.l1 = LinkRandPhrase("Günaydın, efendim. Son haberler nedir?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istedim. İyi günler, efendim!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ha-ha! Ben de aynı şekilde hissediyorum. Seni daha önce hiç görmemiştim... Benim adım Oelart Koteel. Hollanda savaş gemisinde topçu subayıydım.";
			link.l1 = ""+GetFullName(pchar)+".   Buraya yeni geldim, daha yeniyim.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Ben de yeniyim, burada bir yıldan az kaldım – ve umarım burada daha fazla kalmak zorunda kalmam, gerçi herkes aksini söylemeye çalışıyor. Tanıştığımıza sevindim!";
			link.l1 = "Ben de seninle tanıştığıma memnun oldum, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Günaydın, efendim. Son haberler neler?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
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
				link.l3 = "Adanın nasıl oluştuğu hakkında bir fikrin var mı?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Kabilelerin gemilerini hiç ziyaret ettin mi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedin...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Oldukça sıradan bir hikaye. Bir İngiliz şilebiyle çarpıştık ve neredeyse kazanıyorduk. Onlar kaçtı, biz peşlerine düştük. Bir gün geçti, yakalamamıza ramak kalmıştı ki, ana direğimizi vurdular ve kaçmayı başardılar.\nSonra, şiddetli bir fırtına neredeyse bizi batırıyordu, ardından bir akıntıya kapıldık ve sonunda gemimiz dış halkaya yakın bir resife çarptı. Çok azımız hayatta kalabildi...";
			link.l1 = "Üzgünüm...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Bu benim hayalim. Buradaki hayattan ne kadar sıkıldığımı hayal bile edemezsin. Ama nasıl gideceğim? Hiçbir fikrim yok.\nBurada yüzen bir gemi yok ve yenisini inşa etme imkânı da yok – ayrıca bir filikayla denize açılmak intihar olurdu. Fırtınalar böyle küçük bir şeyi paramparça eder.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Adada gördüğüm en eski enkaz yaklaşık yüz yıllık, ama dış halka yüzünden adanın çok daha eski olma ihtimali var. Baştan sona gemilerden oluşuyor – suyun derinliklerinde, gözden birkaç kulaç uzakta, gerçekten çok eski gemiler olabilir. Adanın oluşumuna gelince... Akıntıların ve fırtınaların sürüklenen gemileri buraya getirdiğine inanıyorum, bu yüzden yapay bir sığlık yapılmış. Dış halka da onun üzerine inşa edilmiş. Bizim yaşadığımız içteki gemiler... ya ilk gelenlerdi ya da bir şekilde dış halkadan sızmayı başardılar. Bu gayet mümkün, sonuçta Amiral ve korsanları da buraya kendi brigleriyle ulaşmıştı.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Koruyucu ve Velasco'yu Rivados bölgesinde ziyaret ettim. Black Eddy bir keresinde geminin toplarıyla ilgili bir danışmanlığa ihtiyaç duymuştu - nedenini sorma, bana asla söylemedi. O yüzden siyahlardan biri beni buldu ve bana parolayı verdi.\nMuhafızlar serttir, bu yüzden parolan olmadan yanlarından geçmeye kalkışma bile.";
			link.l1 = "Bunu aklımda tutacağım.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Beyefendi, ne yapıyorsunuz... Ah! Soyuyorsunuz beni! Durun!","Ben arkamı döner dönmez beni soymaya mı kalkışıyorsun?! Buna nasıl cüret edersin!","Deniz sandığımdan ellerini çek, hırsız!");
			link.l1 = "Lanet olsun...";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandığımı mı yağmalamaya karar verdin? Bunun hesabını vereceksin!";
			link.l1 = "Orospu!";
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
			dialog.text = LinkRandPhrase("Beyefendi, lütfen silahınızı indirin. Beni tedirgin ediyorsunuz.","Elinde bıçakla orada burada dolaşma, kendini yaralayabilirsin.","Masum insanların etrafında kılıçla dolaşmak, sandığınız kadar asilce bir davranış değil, efendim. Kılıcınızı indirin.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, lütfen silahınızı indirin. Beni tedirgin ediyorsunuz.","Bıçağı eline alıp etrafta koşuşturma, kendini yaralayabilirsin.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, lütfen silahınızı indirin. Beni tedirgin ediyorsunuz.","Elinde bıçakla orada burada dolaşma, kendini yaralayabilirsin.");
				link.l1 = RandPhraseSimple("Üzgünüm.","Onu kaldırıyorum.");
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
