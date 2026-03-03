// Таннеке Эверс - просто девушка
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
				dialog.text = "Beni rahat bırak, efendim. Barışçıl insanlara saldıran biriyle konuşmak istemiyorum!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "İyi günler! Sizi tanıyor muyum? Sanırım sizi daha önce hiç görmedim...";
				link.l1 = TimeGreeting()+". Evet, yeniyim. Benim adım Kaptan "+GetFullName(pchar)+"";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Bir şey mi istiyorsun?";
				link.l1 = LinkRandPhrase("Merhaba, Tanneke. Adada ne var ne yok?","Adada yeni bir şey oldu mu?","Bana son dedikoduları anlatır mısın?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Sana ada hakkında birkaç soru sormak istiyorum.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Sadece nasıl olduğunu görmek istedim. İyi günler!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Eski kaptan. (kıkırdar)";
			link.l1 = "What do you...? A-ha, I understand. No, I'm still a captain; my ship is moored off the shores of the Spanish Main. I reached this place on a barque - or, almost reached it; the barque was hold and sunk two miles offshore.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Peki fırtınalardan nasıl sağ çıktın?";
			link.l1 = "Hangi fırtınalar? Hiçbir fırtına hatırlamıyorum...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Nasıl bilmezsin? Adanın etrafında her zaman fırtınalar olur. Herkes böyle söylüyor.";
			link.l1 = "Pekâlâ... Sanırım ben o tehlikeyi atlatacak kadar şanslıydım. Deniz tamamen sakindi... affedersiniz, böylesine güzel bir hanımefendinin adını öğrenebilir miyim?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ah! Affedersin, kendimi tanıtmayı unuttum... Benim adım Tanneke. Tanıştığımıza memnun oldum.";
			link.l1 = "Ben de memnun oldum, Tanneke... Gerçekten çok memnun oldum.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ve neden gemini bir barque ile takas ettin?";
			link.l1 = "Adalet Adası hakkında söylentiler duydum ve kendi gözlerimle görmek istedim. Gemimi riske atmak istemediğim için onu Blueweld'de demirledim ve bu bölgeyi keşfetmek için bir barque satın aldım...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Şimdi anladım. Sen de Adolf Barbier gibisin: Kaptan Alvarado'nun hikayelerini fazla okumuşsun ve Amiral de Betancourt'un altınını aramaya karar vermişsin. Ne yazık ki, Barbier gibi kurnaz bir düzenbaz bile onu bulamadıysa, senin bulacağına pek inanmıyorum.\nHem, amiralin altını diye bir şeyin olduğuna da inanmıyorum. Bence Antonio, dedesini önemli göstermek için bunu uydurdu.\nNeyse, o zaman bizimle kalacaksın! Buraya gelmek kolaydı, ama buradan çıkmak imkansız - en azından sağ salim çıkmak.";
			link.l1 = "Altın mı? Amiral de Betancourt mu? Bunu ilk kez duyuyorum... Neyse, adadan ayrılmayı düşünüyorum - hem de sağ salim. Seninle konuşmak güzeldi, Tanneke. Hoşça kal!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sorunuzu sorun, Kaptan...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Buraya nasıl geldin?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adadan hiç ayrılmayı denedin mi?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Buradaki hayatın nasıl?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Şey... hanımlar yiyeceği Amiral'den mi almak zorunda, yoksa bedava mı veriliyor?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Hiçbir sorum yok. Affedersiniz...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ben Hollandalıyım, ama Santiago'da yaşadım. Ailem beni oraya Geraldi banka ailesine hizmetçi olarak çalışmaya gönderdi. Onları duydun mu? Üç yıl önce onlardan biri bir kurye luggeriyle Yeni İspanya'ya yelken açtı. Bana da ona eşlik etmem söylendi.  Yolculuğumuzun ikinci gününde, İspanyol bayrağı taşıyan bir brigantine tarafından yakalandık. Subayları gemimize çıktı ve kaptanımızla konuştu—ne hakkında konuştuklarını bilmiyorum. Kaptan çok öfkelendi ve subayı luggerden kovdu. Subay kendi gemisine dönerken, üzerimize ateş açtılar.  Kaçmaya çalıştık, ama sonunda bizi ele geçirdiler. Sanırım Geraldi olan efendimin peşindeydiler, çünkü doğrudan kamarasına koştular, onu zincire vurdular ve götürdüler. Ben ve mürettebat ambarın içine kapatıldık.  Bizi batıracaklarını sandım, ama sadece uzaklaştılar. Denizciler ambarın kapısını açmayı başardı. Güvertede kaptanı ölü bulduk. Hiçbirimiz doğru düzgün seyir bilmiyorduk.  Rastgele yol aldık, ta ki şiddetli bir fırtına bizi yakalayana dek. Birkaç saat sonra luggerimiz dış halkaya savruldu. Hâlâ orada. Şafakta, ben ve hayatta kalan birkaç kişi luggerin filikasına binip adaya kürek çektik.";
			link.l1 = "Ne hikaye ama!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Hayır. Nasıl olabilirdim ki? Burada denize elverişli bir gemi yok, filikayla çıkmaya çalışmak ise intihar olur. Dediğim gibi, ada fırtınalarla çevrili.\nBir zamanlar beş yerli tam da bu şekilde kaçmayı denedi. Sağlam kerestelerden ve batık bir Hint gemisinden kurtardıkları iyi yelkenlerden düzgün bir filika yaptılar. Akıntıya karşı dokuz saat savaştılar ve sonunda açık denize çıktılar. Birkaç gün sonra, içlerinden biri direklerinin enkazına bağlı halde dış halkaya geri döndü... taş gibi ölüydü.\nO günden sonra ayrılmak isteyen pek kalmadı.";
			link.l1 = "Dehşet verici...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Endişelenme. O şişkin tefeci ailesinin uşağı olmaktan daha kötü değil burası. Sadece buraya alışman gerek, alışınca belki seversin bile. Birçok kişi böyle hissediyor. Klanlar da bana dokunmuyor.";
			link.l1 = "İlginç...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Elbette satın alıyoruz. Bir kız için burada yeterince iş var: temizlik, yemek yapmak, başkalarına yardım etmek... boş durmuyoruz ama kendimizi de paraladığımız yok. Korsanlar yiyeceği sıradan halka ucuza satıyor, klanlara ise acımasızca kazık atıyorlar. Bu yüzden aç kalmıyoruz. Gillian ve Natalie'ye yardım ediyorum, onlar da gerekirse bana yardım ediyor. Arkadaşız. Adada başka bir kız daha var, bir İspanyol: Ramona. Ama o genellikle kendi halinde ve biz de onunla arkadaş olmaya pek istekli değiliz.";
			link.l1 = "Ve nedenmiş o?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Pekâlâ... diyelim ki hayata bakışımız biraz farklı. Onunla konuşursan anlarsın.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Kim... aman Tanrım, hırsız! Yardım edin!","Bir dakikalığına arkamı döndüm, hemen beni soymaya mı kalkıştın?! Yardım edin!","Sandıklarımı yağmalamaya mı karar verdin? Bunun hesabını vereceksin!");
			link.l1 = "Kahretsin!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Eşyalarıma nasıl dokunursun! Birisi yardım etsin!";
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
			dialog.text = LinkRandPhrase("Lütfen silahınızı indirin, efendim. Beni tedirgin ediyorsunuz.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.","Beyim, yiğit olduğunuzu biliyorum. Bunu kılıç sallayarak kanıtlamanıza gerek yok...");
			link.l1 = LinkRandPhrase("Pekâlâ.","Dediğiniz gibi...","Dediğiniz gibi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Lütfen silahınızı indirin, efendim. Beni tedirgin ediyorsunuz.","Biliyor musun, burada elinde bıçakla dolaşmana izin verilmez. Onu yerine koy.");
				link.l1 = LinkRandPhrase("Peki.","Nasıl istersen...","Dediğiniz gibi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Lütfen silahınızı indirin, efendim. Beni tedirgin ediyorsunuz.","Beyim, cesur olduğunuzu biliyorum. Bunu kılıç sallayarak kanıtlamanıza gerek yok...");
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
