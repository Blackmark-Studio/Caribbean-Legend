// Джаспер Пратт - каторжник
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
				dialog.text = "Beni rahat bırak, bayım. Masumlara zarar verenlerle konuşmam! Sen benden daha büyük bir suçlusun!";
				link.l1 = "Ben...?";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selam, beyim. Bir şeye ihtiyacın var mı?";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+".   Ben buraya yeni geldim.   İsminizi öğrenebilir miyim?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun?";
				link.l1 = LinkRandPhrase("Merhaba Jasper. Son zamanlarda yeni bir haber duydun mu?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Başka bir zaman, Jasper!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ben mi? Ben Jasper Pratt. Belki de bana devlet mahkûmu dediklerini duymuşsundur – bu yüzden herkes bana yan gözle bakar. Ah, boş ver onları. Ben neysem oyum...";
			link.l1 = "Kim olduğun umurumda değil, kim olduğun önemli.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Herkes senin gibi düşünmüyor ne yazık ki, bayım.";
			link.l1 = "Eh, liberal tavrımla tanınırım...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Aferin sana. Merak etme. Geçmişime rağmen, Adanın sakinlerinin cüzdanlarına ya da sandıklarına göz dikmiş değilim. Sonunda huzur içinde yaşayabildiğim için mutluyum.";
			link.l1 = "Tanıştığıma memnun oldum, Jasper. Bir dahaki sefere görüşürüz!"link.l1.go ="exit";
			link.l2 = LinkRandPhrase("Merhaba Jasper. Son zamanlarda yeni bir haber duydun mu?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatacak mısın?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Sana ada hakkında birkaç soru sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sorabilirim, cevaplarım. Sor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Adaya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Bu yeri beğendin mi?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "İnsanların sana tuhaf baktığını söyledin. Bu geçmişinle mi ilgili?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Bu ada oldukça ilginç, sence de öyle değil mi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Küba'daki bir plantasyondan kaçtık. Beş kişiydik ve sırtımızı kırmaktansa ya da her gün dövülmektense ölmeyi tercih ettik. Gardiyanları kandırıp ormana karışmayı başardık. Kıyıya vardığımızda bir sal yaptık.\nTortuga'ya ulaşmaya çalıştık ama hiçbirimiz denizden anlamıyorduk, bu yüzden kaybolduk. Sonra su bitti... O kısmı hatırlamak istemiyorum. Her neyse, adaya ulaşıp hayatta kalan bir tek ben oldum.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Biliyor musun, burada olmayı seviyorum. Plantasyonda yaşadıklarımın ardından, burası bana yeryüzündeki cennet gibi geliyor. Fazla bir şeye ihtiyacım yok... biraz yemek, su, akşamları bir bardak rom – ve burada kimse derimi kırbaçlamak istemiyor. Tüm bunlar kalmak için yeterli sebep. Vaktim geldiğinde burada ölmeye razıyım.";
			link.l1 = "Sanırım öyle...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Şu var ki, bu ada bir hırsızın oyun alanı oldu. Gece gelir, kilitler onu durduramaz. Genellikle Amiral'in odalarının civarında dolaşır, korsanların yaşadığı yerde; herkesin sandığı bir zamanlar altüst edilmiştir.\nKimse hırsızın kim olduğunu bilmiyor, bu yüzden... hımm... sabıkalı geçmişi olanlardan şüpheleniyorlar.\nAma hırsız biraz tuhaf: sadece içki şişeleriyle bazı küçük süs eşyalarını alıyor - gerçekten değerli hiçbir şeyi almıyor. Komik, değil mi?";
			link.l1 = "Evet, komik...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "'Tis. Swam a lot 'round the inner ships o' th'island. Not many exits from the water: San Augustine, on the canted deck either side o' the rope bridge; Gloria, up the fallen mast...\nIf'n you swim close to the Phoenix and then 'round the Ceres you can reach Mary Casper's cabin through the ship's bow.\nThe hole in Tartarus's belly will lead you to the prison. There's a hole in the San Augustine's bow what opens into th'Admiral's storage room, but don't go in there - the guards'll cut you down; remember, the lowest door of Tartarus is locked for a reason.\nAn' o' course you can get aboard the Fernanda, the lone fluyt. They say no one lives there but I've often seen lights inside the cabin, and sometimes I can hear drinking songs... and a man cryin' out, in pain or grief.";
			link.l1 = "İlginç... keşfedilecek çok şey var.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ah! İşte hırsız! Tam orada!","Ve bana suçlu diyorlar?! Çek ellerini, beyefendi!","Hırsızı buldum! Burada! Burada!");
			link.l1 = "Dur, hayır!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Parmaklarını göğsümden çek! İmdaaat!";
			link.l1 = "Siktir!";
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
			dialog.text = LinkRandPhrase("Beyim, Allah aşkına, kılıcınızı yerine koyun! İnsanları korkutuyorsunuz.","Bunu ortalıkta salladığını kimseye gösterme... yoksa kendini Tartarus'ta bulursun.","Burada kılıç sallamana gerek yok. Dostlar arasındasın.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Üzgünüm.","Pekala...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, beyim, onu yerine koy. Burada kılıca gerek yok.","Burası benim evim ve burada kimse kılıç sallamadığı için güvenli. Onu indir.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ, o zaman.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyefendi, Allah aşkına, kılıcınızı yerine koyun! İnsanları korkutuyorsunuz.","Burası benim evim ve burada kimse kılıç sallamadığı için güvendeyiz. Onu indir.");
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
