// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Git buradan, señor. İşine gücüne bakmaya çalışan sıradan insanlara saldırıyorsun.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Vay canına! Ya buraya yeni geldin ya da şimdiye kadar yük ambarlarından birinde saklanıyordun, çünkü seni ilk kez görüyorum.";
				link.l1 = TimeGreeting()+". Kargo ambarlarında saklanmak bana göre değil. Ben kaptan kamarasını tercih ederim... Ama evet, burada yeniyim.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+"!   Seni gördüğüme sevindim!   Ne dersin?";
				link.l1 = LinkRandPhrase("Sevgili Ramona! Adada işler nasıl gidiyor?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece güzel yüzünü görmek istedim. Bir dahaki sefere, Ramona!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "O zaman birbirimizi tanıyalım... Kaptan. Ben Ramona Lozano'yum - ve sakın bana 'Señora' Lozano demeye kalkma. Bundan nefret ederim. Senin adın ne?";
			link.l1 = ""+GetFullName(pchar)+". Sizinle tanıştığıma memnun oldum, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Gerçekten memnun musun, yoksa sadece kibarlık mı ediyorsun, "+GetFullName(pchar)+"? Söylesene, gerçekten kaptan mısın yoksa şaka mı yaptın?";
			link.l1 = "O-ho, so many questions! May I answer them in order? First, I am truly delighted; I don't meet such pretty girls every day. Second, I am indeed a captain, but my ship is anchored on the coast of the Spanish Main right now.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Komikmiş! Peki kaptan, sen buradasın ama gemin ana karanın kıyısında. Mürettebatının dağılmasından ve geminin elinden alınmasından korkmuyor musun?";
			link.l1 = "Buraya bir barkla geldim... bu denizi keşfetmek için. Kendi gemimi riske atmak istemedim - o benim gururum ve neşem. Ama gece olunca, bark karanlıkta bir resife ya da batığa çarptı, alabora oldu, işte böyle! Buradayım şimdi.\nGemim beni bekler, ne kadar gerekirse. Dannie Hawk tayfayı bir arada tutar.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk mı? Yani... Danielle Hawk mı? Onunla mı denize açıldığını söylüyorsun?";
			link.l1 = "My hand to God, Ramona, I tell no lie; Dannie serves as my officer. I left her in command while I set out in my barque... How do you know her?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! İspanyol kolonilerindeki herkes korsan Danielle Hawk'u ve kocası Nathaniel'i tanır. Evet, sen, señor "+GetFullName(pchar)+", demek ki sert bir adamsın... O zaman korsan mısın? Merak etme, senin gibilerle iyi anlaşırım. Sert adamları severim.";
			link.l1 = "Şey, aslında korsan sayılmam... şu anda Jan Svenson için çalışıyorum – Dannie'nin kayıp kocasını bulmasına yardım etmeye çalışıyorum.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Ve sen korsan olmadığını mı söylüyorsun? Orman Şeytanı için çalışıyorsun, birinci subayın Danielle Hawk, Nathaniel'i arıyorsun... ve eminim ki buraya Amiral için geldin. Doğru mu?";
			link.l1 = "Ramona, bana korsan diyebilirsin istersen. Hatta bana çapa bile diyebilirsin — yeter ki beni gerçekten çapa olarak kullanmaya kalkma!";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Anlaşılan sen gerçekten o dayanıklı adamlardan birisin, "+pchar.name+". Pekala, gitmem gerek. Umarım adada tekrar karşılaşırız, içimde bir his var, belki de arkadaş oluruz... yakın arkadaşlar.";
			link.l1 = "Neden olmasın? İyi günler!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Gerçekten mi? Peki, sor. Cevaplayabilirsem yanıtlarım...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Elbette adadan ayrılmayı denedin, değil mi?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Burada nasıl yaşıyorsun?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Burada ne yapıyorsun? Sanırım yemek bedava değil, değil mi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sorunuz yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Bu uzun bir hikaye... Suçlu üvey babam.\nDört yıl önce Havana'da mutlu bir hayatım vardı. Annem öldü ve servetinin tek varisi ben oldum. Zengin değildik ama paramız vardı – rahat yaşamak için fazlasıyla yeterliydi.\nÜvey babam bundan hoşlanmadı ve beni ortadan kaldırmaya karar verdi. Tabii ki bunu ancak şehir kapısında iki kiralık haydut bana saldırınca öğrendim. O aptallar, kendilerini tutamayıp kimin ve neden onları tuttuğunu bana söylediler.\nNeyse ki profesyonel değillerdi, yoksa şimdi boğazı kesilmiş halde çalılıkların arasında yatıyor olurdum. Aptallar önce biraz eğlenmek istemişler.\nKader beni kurtardı: senin gibi bir kaptan tesadüfen oradan geçiyordu. Olanları gördü ve pislikleri anında öldürdü – hiç şansları olmadı. Durumumu anlattım, biraz ağladım... Gidecek hiçbir yerim olmadığını biliyordu, bu yüzden beni üvey babamdan korumak için gemisine aldı – önce geçici olarak, ama sonra...\nSanırım onunla kalırdım, ama iki ay sonra bir devriye ile karşılaştı, bir direğini kaybetti, şiddetli bir fırtınaya yakalandı ve dış halkada huzuru buldu. Her şeye rağmen hayatta kaldım ve Adalet Adası topluluğuna katıldım.";
			link.l1 = "Üzücü bir hikaye, söyleyecek söz bulamıyorum.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tabii ki hayır, çünkü bu imkânsız. Buradan bir sandalla ayrılmaya çalışan bir adam gördüm... İki gün sonra geri döndü. Boğulmamak için kendini batık bir direğe bağlamıştı, ama mosmor ve taş gibi ölüydü.\nVe söyle bana, "+pchar.name+", kaçmayı başarsam bile ne yapacağım ki? Havana benim için çok tehlikeli - üvey babam kesinlikle beni tekrar öldürmeye çalışacak. Ne evim var, ne de param. Nereye gideceğim? Bir geneleve mi?";
			link.l1 = "Yine de, Karayipler'e geri dönmek ister misin?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "Ne düşünüyorsun? Elbette isterim. Ama bu imkânsız ve nedenini az önce anlattım. Üvey babamdan bir şekilde kurtulabilseydim — ister kılıçla ister kurşunla — eski hayatıma dönmek için bir umut olurdu. Ama kim böyle bir şeye cesaret eder ki, üvey babam Havana valisinin yakın dostuyken? Yani neyi konuşuyoruz? Buradan çıkış yok...";
			link.l1 = "Göreceğiz. Belki zamanı gelir...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Ben sadece yaşıyorum. Başka bir seçeneğim yok. Arkadaşlarımın çoğu erkek, çünkü evlenilecek iki güzelimiz - Gillian ve Tanneke - benden hoşlanmıyor. Natalie iyi bir kızdı, ta ki o iki aptalla çok vakit geçirmeye başlayana kadar. Aptallık bulaşıcıdır.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I work like the other girls, mostly helping the men. There's a lot of work for women on the island so I keep busy. And I often get gifts - it's a usual thing here. But don't think I am some wench; I was well educated and come from a good family. I just don't play the saint... like some women...";
			link.l1 = "Sana karşı asla kötü bir şey düşünmedim...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ne yapıyorsun - ah! Hırsız!","Şuna bak! Daha arkamı döner dönmez, sandığımı yağmalamaya kalkışıyorsun!","Sandıklarımı mı talan ediyorsun?! Bunu yanına bırakmam!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "İt oğlu it! Sırtım dönükken sandığımı mı kurcalıyorsun?!";
			link.l1 = "Sessiz ol!";
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
			dialog.text = LinkRandPhrase("Beyim, silahınızı indirir misiniz? Beni tedirgin ediyorsunuz.","Aptalların kılıçlarını çekip ortalıkta dolaşmasından hoşlanmayız. Kılıcını indir.","Kılıcını çekmiş halde etrafta koşuştururken tam bir aptal gibi görünüyorsun. Onu yerine koy...");
			link.l1 = LinkRandPhrase("Pekala.","Tabii.","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Dinle, kılıcını indir. İnsanları huzursuz ediyorsun.","Aptalların kılıçlarını çekip etrafta dolaşmasından hoşlanmayız. Onu yerine koy.");
				link.l1 = LinkRandPhrase("Pekala.","Tabii.","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Beyim, silahınızı indirir misiniz? Beni tedirgin ediyor.","Kılıcını çekmiş halde etrafta koştururken aptal gibi görünüyorsun. Onu yerine koy...");
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
