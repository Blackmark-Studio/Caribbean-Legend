// официантка Наталия Бушелл
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
				dialog.text = "Ah! Bana senin boğulduğunu söylemişlerdi... Yalancılar!";
				link.l1 = "Tabii ki yaptılar! Ha! İyiyim!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler, "+GetAddress_Form(NPChar)+" ! İlk defa mı buradasın? Seni daha önce görmedim... Umarım bizi daha sık ziyaret edersin, Sancho harika içkiler sunar. Evet, bu arada adım Nathalie ve Sancho'ya meyhanenin işleriyle yardımcı oluyorum.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+" . Tanıştığımıza memnun oldum. Beni daha önce görmüş olamazsın. Buraya daha yeni geldim.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun? ";
				link.l1 = LinkRandPhrase("Söyleyecek ilginç bir şeyin var mı?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Son zamanlarda mı? Başka bir gemi mi battı? Hiçbir şey duymadım... Yoksa buraya monsieur Turam gibi mi geldiniz, direğin enkazında? Affedin merakımı, kadınların doğasında var, bilirsiniz.";
			link.l1 = "Hayır, sorun yok Nathalie. Buraya bir bark ile geldim ama battı. Tanıştığımıza memnun oldum. Görüşürüz!";
			link.l1.go = "exit";
			link.l2 = "Hayır, sorun yok. Sadece ada hakkında sana birkaç soru sormak istedim.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Dinliyorum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Meyhanede çalışıyorsun. Bana sahibi hakkında ne söyleyebilirsin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Peki, buraya nasıl düştün?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Burada kaç kişi yaşıyor?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Burada yeni yüzler gördüğünde hiç şaşırmıyor musun?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Hiçbir sorum yok. Müsaadenizle...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sadece güzel şeyler,  "+GetAddress_Form(NPChar)+" Sancho'nun her zaman geniş bir içki seçkisi vardır – eski şaraplardan sade biralara ve romlara kadar. Birkaç yıl önce, büyük bir eski şarap stoğu buldu. Sancho, iki ay boyunca şişe kasalarını dükkânına taşımakla uğraştı.\nVe şimdi, takımadalarda sadece valilerin ulaşabildiği kadar kaliteli şaraplarla iyi donanımlıyız. Rom da eksik olmaz. Sancho sana yalnızca içki değil, taze haberler, iyi bir tavsiye ve geceyi geçirecek sıcak bir yatak da sağlayabilir.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ah, bu gerçekten hüzünlü bir hikaye. Yedi yıl önce, sevgilimle birlikte ailemin evinden kaçtım ve Santiago'dan Belize'ye taşınmaya karar verdik. Ancak, rotacı Main yakınlarında bir hata yaptı, bu yüzden kuzeye yanlış yöne gittik ve fırtınaya yakalandık. Gemimiz dış halkaya yakın bir yerde battı.\nO gün sevgilim ve çoğu yolcu hayatını kaybetti. Hayatta kalanlarla birlikte burada, Adalet Adası'nda yeni bir hayata başladık.";
			link.l1 = "Hüzünlü bir hikaye...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Quite a lot. The Rivados and Narwhal clans are strong in numbers; they've been living here for decades. There aren't many common folk, but the tavern is full every night. I barely manage to serve drinks.";
			link.l1 = "Gerçekten mi? İlginç.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ve neden yapalım ki? Buraya sık sık yeni yüzler geliyor. Burada kaç kişi yaşadığını bile bilmiyorum. Bazen bir adamı ilk kez görüyorum, bana bir yıldır burada yaşadığını söylüyor.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Orada ne yapıyorsun, ha? Hırsız!","Şuna bak! Ben düşüncelere dalar dalmaz, sandığımı karıştırmaya kalktın!","Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ne?! Sandıklarımı mı kurcalamaya karar verdin? Bunu yanına bırakmam!";
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
			dialog.text = LinkRandPhrase("Dinle, silahlarını indirsen iyi olur. Onlar beni tedirgin ediyor.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Dinle, elinde silahla dolaşan bir ortaçağ şövalyesi gibi davranma. Koy onu yerine, sana yakışmıyor...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekala.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı rica ediyorum.","Dinle, ben bu şehrin bir vatandaşıyım ve senden kılıcını kınına sokmanı rica ediyorum.");
				link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dikkatli ol dostum, elinde silahla dolaşmak beni tedirgin ediyor...","İnsanların silahlarını çekmiş halde önümden geçmelerini hiç sevmem. Bu beni korkutuyor...");
				link.l1 = RandPhraseSimple("Anladım.","Bunu alıyorum.");
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
