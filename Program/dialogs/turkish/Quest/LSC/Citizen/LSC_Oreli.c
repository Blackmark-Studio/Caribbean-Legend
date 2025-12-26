// Орели Бертин - просто жительница
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
				dialog.text = "Beni rahat bırakın, efendim. Birine zarar verdiniz! Uzaklaşın!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler, efendim.";
				link.l1 = TimeGreeting()+" . Benim adım "+GetFullName(pchar)+",   Buraya yeni geldim, o yüzden buradaki insanları tanımaya çalışıyorum.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun?";
				link.l1 = LinkRandPhrase("İyi günler, Madame Bertine. Adada neler var, yeni bir şeyler oldu mu?","Adada yeni bir şey oldu mu?","Bana en son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu merak ettim. Görüşürüz!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Anladım. Benim adım Orelie Bertine. Buraya nasıl geldin?";
			link.l1 = "Efsanevi Adalet Adası'nı görmek istediğimi söyleyelim.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Demek kendi isteğiyle buraya gelen o delilerden birisin... Pekâlâ, şimdi Adalet Adası'nı görmeye ve onun 'adaletini' fazlasıyla tatmaya bolca vaktin olacak.";
			link.l1 = "Alaycılığınıza bakılırsa, onun adalet anlayışında bir sorun görüyor musunuz?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Hayır, her şey yolunda - ama nedense artık yiyecek için korsanlara para ödemek zorundayız, oysa daha geçenlerde herkes için ücretsizdi. Ve klanlar kavgalarını Adanın bizim tarafımıza taşıdığında, vurulup bıçaklanmamak için gemilerimizin içinde oturmamız gerekiyor.\nYani, kendi bölgemizde istediklerini yapabiliyorlar ama biz onlarınkinde aynısını yapamıyoruz. Ama sorun yok, hiçbir sıkıntım yok... hiç yok...";
			link.l1 = "Anladım... Sizi tanıdığıma memnun oldum. Şimdilik hoşça kalın, Madame Bertine!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Şimdi konuş.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Burada uzun zamandır mı yaşıyorsun?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adada ilginç bir şey var mı?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Klanlar hakkında ne düşünüyorsun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Korsanlar seni rahatsız ediyor mu?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yoksa, affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Çok uzun zaman oldu. Yılları saymayı bıraktım... herhalde on yedi... yok, belki on sekiz... ya da yirmi mi? Bugünün tarihi ne?";
			link.l1 = "Yani, sen eski topraklardan mısın?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Şöyle söyleyeyim: Hâlâ hatırlıyorum, Küba'dan korsanlar bizimle ticaret yapardı ve en zeki, en gözü kara Narvaller, ana karaya gidip gemilerin ambarlarından kurtardıkları malları yiyecekle takas ederdi.\nAma şimdi burada doğmuş, başka hiçbir yeri bilmeyen pek çok insan var. Onlar sadece eski toprak değil, artık adanın yerlisi.";
			link.l1 = "İlginç!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tabii. Ada ilginç bir yer. Etrafta dolaş, enkazların arasında yüz, meyhaneye, dükkâna ve kiliseye uğra. Ama sana söz veriyorum, bu yenilik hissi bir hafta içinde kaybolur.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Ne söylememi istiyorsun? Onlardan uzak durmaya çalışıyorum. En azından Narvaller adaya biraz fayda sağlıyor - aralarında çok yetenekli zanaatkârlar var - ama Rivadoslar tam anlamıyla vahşi ve putperestler. \nAfrika’dan getirdikleri yasalarla yaşıyorlar, tıpkı ataları gibi yüzlerce yıl önce olduğu gibi. Hayvanlar. Tek öğrendikleri şey ateşli silah kullanmak. Bazılarına göre Rivadoslar ritüel olarak yamyamlık yapıyormuş!";
			link.l1 = "Ne kabus ama...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Bize kendi yiyeceğimizi satmaları canımı sıkıyor, ama asla bize, adalı vatandaşlara zarar vermiyorlar. Tam tersine, klanları dizginleyip sürekli savaşlara son verdiler.\nBir keresinde, insanlara bela olan bir vatandaş vardı – kılıcını sallamayı pek severdi. İki yerliyi yaraladı. Korsanlar onu birkaç hafta Tartarus'a kapattı, şimdi ise adam gayet sakin biri oldu. Onu artık pek görmüyoruz – dış halka yeni evi oldu...";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ne yaptığını sanıyorsun, hırsız?!","Ben arkamı döner dönmez sandığımı mı talan ediyorsun?!","Sandığımı mı karıştırıyorsun, ha? Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Sen hırsızsın! Bunun bedelini Tartarus'ta çürüyerek ödeyeceksin!";
			link.l1 = "Kapa çeneni!";
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
			dialog.text = LinkRandPhrase("Lütfen silahınızı yerine koyar mısınız, efendim. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde kılıçla dolaşmana izin verilmez. Onu yerine koy.","Eminim korsanlar elinde kılıçla ortalıkta dolaşmandan hoşlanmazlar. Açıkçası ben de pek memnun değilim...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Lütfen silahınızı yerine koyar mısınız, efendim. Bu beni tedirgin ediyor.","Biliyor musun, burada elinde kılıçla dolaşmana izin verilmez. Onu yerine koy.");
				link.l1 = LinkRandPhrase("Pekala.","Pekala.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Lütfen silahınızı yerine koyun, efendim. Bu beni tedirgin ediyor.","Eminim korsanlar elinde kılıçla ortalıkta dolaşmandan hoşlanmazlar. Açıkçası ben de hoşlanmıyorum...");
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
