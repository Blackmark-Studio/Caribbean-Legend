// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você precisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "O senhor coronel está no campo em um exercício militar neste momento. O que deseja com ele, capitão?";
				link.l1 = "Desta vez, Ben, é de você que eu preciso. Tenho más notícias sobre sua irmã Molly. Aquela moça linda parece estar em apuros. Ela foi capturada pelos piratas de Tortuga. Ela precisa de ajuda e pediu que eu te avisasse. O homem que se encarregou de trazer a mensagem foi morto, mas antes de morrer, conseguiu me contar sobre sua irmã.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Se você veio ver o Coronel Fox, pode entrar — ele vai recebê-lo..";
				link.l1 = "Muito bem então.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "O coronel não está aqui. Volte mais tarde.";
				link.l1 = "Tudo bem...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! Você é o primeiro homem que já chamou minha irmã de 'bonita'. Deus deu a ela o corpo de um granadeiro e, no lugar de uma voz, o berrante de Jericó. Nossa Molly sabe se defender. Mas a criatividade do Senhor não parou só no que está abaixo do queixo dela. Não, não, o melhor de tudo foi colar o rosto peludo e cheio de marcas do nosso falecido pai logo acima dos seios dela. E devo dizer, senhor, o rosto do meu velho fazia até cavalo desmaiar de susto.";
			link.l1 = "Vejo que você não está particularmente chateado...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "E por que ela apareceria em Tortuga? Molly é criada de Catherine Fox, filha do nosso valente coronel. Catherine estava vindo da Europa para visitar o pai no aniversário dele. Mas o esquadrão com o qual o navio dela viajava se atrasou\nSe quiser ver a verdadeira Molly Jones e sua senhora, que aliás é muito bonita, venha aqui daqui a um mês. Nem um dia antes.";
			link.l1 = "Acontece que sua irmã Molly Jones tem trabalhado para a Srta. Fox e, neste momento, está morando do outro lado do Atlântico?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Exactly so! The last courier informed us that a navy squadron dispatched by Lord Protector Cromwell himself was supposed to leave London only a month ago. The brig 'Albatross', with Catherine aboard, was to accompany them. We shall learn if this is truly the case from the next mail packet boat. Although the ships haven't arrived yet, and the colonel had strictly forbidden the 'Albatross' to sail alone.\nDid you know that his beloved wife died during an attack by French corsairs? It was not easy for the colonel, and he still dreads the dangers of the high seas... So I can't help you with Molly Jones, captain! There are a lot of colonist girls named Molly! Besides, having the surname Jones in Britain is as good as having no surname at all!\nEvery sea dog at Antigua knows me and my commander. I'm not surprised that some poor girl who got into trouble wants my help. I'd like to, but I haven't the coin for a ransom. The colonel owes me three months' wages; my salary, along with everyone else's, arrives with the 'Albatross'.";
			link.l1 = "Aparentemente eu estava enganado então. Mas obrigado mesmo assim pelo esclarecimento.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "De jeito nenhum, capitão.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "O que você quer?! Eu não quero conversar.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Tenho um negócio para você, capitão. Vejo que não está muito animado, então talvez minha proposta anime um pouco o seu humor.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Fique quieto, tome um pouco de rum. Foi mal, desculpe.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "O som disso é bem atraente! E seu rosto me parece familiar... Só não consigo lembrar onde já te vi. Vai, me conta!";
			link.l1 = "Eu sei dos seus negócios com o Thibaut... Calma, amigo! Não precisa ter medo de mim. Tenho uma proposta pra te fazer.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Maldição! Maldito seja aquele porco bêbado!... Eu não consegui...";
			link.l1 = "Está certo. Seu marinheiro era falastrão, mas os boatos dele não chegaram a mais ninguém além de mim. E não vão chegar, já que foi você quem resolveu isso, não é?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Caramba! Agora eu te reconheço! Você é o homem que acabou com o Coronel Doiley e tomou a ilha inteira dele! Se meteu em grandes negócios com a Companhia Holandesa das Índias Ocidentais, anda de braços dados com um barão do continente... Seu nome é... "+GetFullName(pchar)+", certo?";
			link.l1 = "Você tem informações corretas. Sim, sou eu. Mas poderia se acalmar um pouco, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! Ora, como é que eu vou me acalmar quando um dos corsários mais famosos do arquipélago resolveu se interessar por mim, e ainda por cima descobriu sobre os meus negócios também! Que diabos me deu na cabeça pra atacar aquele brigue! O que você quer de mim?";
			link.l1 = "Cale a boca e me escute. Pelo que vejo, nós dois queremos a cabeça do Levasseur numa bandeja. Aquele fanfarrão arrogante já se acha demais e irritou gente perigosa. Quero mudar o equilíbrio de poder na ilha e colocar de Poincy no devido lugar, mas não quero derramar mais sangue dos meus compatriotas, ainda mais por causa de um ladrão ordinário. Você pode me ajudar. E eu posso ajudar você e Thibaut a manterem seus privilégios.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Espere, espere! Não posso acreditar no que estou ouvindo! A sorte sorriu pra mim hoje. Você tem razão, nossos objetivos são os mesmos. Com você ao meu lado, as coisas podem ficar bem mais interessantes... Thibaut é bom de espada, mas não tem coragem pra cortar a garganta do próprio tio... Mas um tubarão astuto como você faria isso sem hesitar. Sua fama já corre por aí\nNão preciso das suas garantias, mas vou te ajudar em troca da garota. Preciso dela como refém até terminar meus assuntos no Caribe. Logo, as fragatas inglesas vão começar a me caçar. Que diabo me deu na cabeça de atacar aquele brigue! Parecia uma presa tão fácil, separada do esquadrão...";
			link.l1 = "O que ela tinha de tão especial? Aquela garota de quem você estava se escondendo do Levasseur?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Sim. Você precisa convencer Thibaut a se afastar da garota. Pedi que ele cuidasse dela enquanto eu descobria quem diabos ela era, mas essa 'Miss Jones', ou lá como se chama, virou a cabeça dele completamente e agora o Henry até está escondendo ela de mim! Traga essa sirena encantadora até mim e eu vou marcar um encontro pra você com Levasseur fora da cidade. Nesse momento, você vai ter a chance de armar uma emboscada pra ele. Estarei esperando na Praia do Olho de Peixe.";
			link.l1 = "Combinado. Agora me diga como pegar o Thibaut.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "As pessoas na taverna podem te mostrar o caminho até a casa dele. Henri é um sujeito bem notável. Ameaçe expô-lo e faça com que ele traga a garota para mim. No mesmo dia, avisarei Levasseur que seu sobrinho está escondendo uma bela raridade na masmorra da cidade\nMeu mensageiro vai te encontrar na taverna. Depois que ele não conseguir achar o Henri, o governador irá até a masmorra com um pequeno grupo e você terá uma ótima chance de conversar com ele.";
			link.l1 = "Onde devo entregar a garota?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Diga a ele para trazer ela até a praia ele mesmo. Vou trocar umas palavras com ele enquanto isso...";
			link.l1 = "Certo. Combinado. Te vejo em Tortuga!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Se tudo correr como planejado, nunca mais vamos nos ver. Assim espero, pelo menos. Adeus!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! Eu não vi isso chegando... Você veio buscar minha alma, não foi? Eu fiz tudo como combinado! Mas que diabos?!";
			link.l1 = "Você tem uma sentença sobre você, Robert. A sentença foi dada a mim para ser cumprida. Então estou apenas cumprindo minha missão.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Maldito! Isso é impossível! Ele não poderia ter descoberto tudo tão rápido! E como é que ele descobriu?!";
			link.l1 = "Você quer dizer o Fox? Não. Não foi ele que me mandou. O coronel ainda nem sabe que você salvou a filha dele. Quem quer te ver morto é seu velho camarada Henry Thibaut. Foi ele quem me contratou.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Aquele maldito catamita! Eu devia ter jogado ele pros caranguejos quando estava no 'Voltigeur'... Quanto aquele desgraçado te prometeu?";
			link.l1 = "Não é todo dia que um homem descobre quanto vale a própria cabeça, não é, Robert? Thibaut te avaliou em duzentos e cinquenta mil, mas eu o convenci de que você valia mais. Você vale trezentos mil pesos de prata, meu amigo. Não está feliz?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Espere um segundo... Vamos fazer um acordo! Eu te pago mais!";
			link.l1 = "Com que dinheiro, Robert? Tenho certeza absoluta de que você está mentindo. Você não tem tanto dinheiro quanto o Henry me prometeu. E isso nem é o mais importante. Se não fosse por um detalhe, eu teria recusado a proposta dele de te caçar e acabar com seus negócios sujos com o Thibaut.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Que fato é esse?";
			link.l1 = "Você matou Catherine Fox. A única culpa daquela pobre garota era ser filha do Coronel Fox. Eu desprezo covardes desprezíveis como você, que condenam mulheres indefesas à morte! Não vou fazer acordo nenhum com você. Nem vou considerar essa ideia. Não perca seu tempo.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Porra! O que mais eu podia fazer?! Eu não podia deixá-la viva e escondida pra sempre no navio! E quem é você... seu canalha, seu desgraçado, seu assassino, pra me dar lição de moral! Olhe pra si mesmo! Pros seus 'métodos'! Você não é melhor do que eu!";
			link.l1 = "Chega. Martene, saque sua espada! Está na hora de acabarmos com isso.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Te vejo no inferno!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "O que o senhor está fazendo na minha casa?";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Estou aqui em nome de um homem que o senhor conhece, o capitão Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hum. E? Então?";
			link.l1 = "O capitão Martene solicita a sua presença imediatamente na Praia Fisheye. Mas não sozinho. Ele também gostaria de ver Molly Jones com você. Entende o que quero dizer?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Infelizmente, senhor, não conheço. Nunca ouvi falar de nenhuma Molly Jones, e Robert nunca teve motivo para me enviar um... plenipotenciário que eu nunca vi antes. Para sua informação, monsieur, sou o segundo homem mais importante nesta ilha depois do meu tio, o governador, então...";
			link.l1 = "A vida é uma fera imprevisível, Henry... Agora você é o segundo homem mais importante da ilha, e daqui a algumas horas pode acabar acorrentado nas masmorras... Tudo isso pela vida de alguém que não te daria nem um mísero peso. Você desobedeceu a ordem do seu tio, não foi, monsieur Thibaut? O que é mais importante pra você: uma garota leviana ou a sua própria vida?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Como assim... Você está mentindo! Está falando besteira!";
			link.l1 = "Você, como qualquer outra pessoa, sabe bem como o temperamento do seu tio pode ser explosivo. Levasseur vai descobrir que você está escondendo a garota antes do pôr do sol. Não me pergunte como o Robert ficou sabendo disso, apenas escute o que eu digo: ele está morrendo de medo e pronto pra zarpar a qualquer momento. Ele nem teve coragem de entrar na cidade e me pagou uma boa quantia só pra eu entregar esse recado pra você.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Droga... Não pode ser!";
			link.l1 = "Você decide, senhor. Martene não vai esperar por você mais do que duas horas. Ele preza muito a própria cabeça. Só está ainda na costa de Tortuga, e não escondido com os holandeses, por consideração à amizade dele com você.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Caramba! Como é que meu tio descobriu isso?";
			link.l1 = "Línguas, Henry. Línguas afiadas. Até eu sei que você e o Robert pegaram a bela moça que desembarcou do brigue inglês capturado pelo seu camarada. Esconderam ela do Levasseur... tsc, tsc. Você realmente acha que só eu estou sabendo dessa história?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Parece que está dizendo a verdade, senhor. Diga a Martene...";
			link.l1 = "Eu acho que você não está entendendo, Henry. Martene não vai esperar por você. Sua única chance é tirar aquela garota daqui, a razão pela qual você e o Robert estão com a corda no pescoço. Corre lá onde você está escondendo ela, pega ela pelas mãos delicadas e leva direto para o Voltigeur. Encontre ela rápido, e traga ainda mais depressa. Seu tio não vai ouvir nada disso de mim.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "Certo. Faremos isso então. Obrigado pela sua gentileza, senhor!";
			link.l1 = "Não precisa me agradecer, monsieur. Meu trabalho já foi pago... Só quero que você saia dessa enrascada antes de virar prato principal.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "O que o senhor está fazendo aqui? Eu não o convidei.";
			link.l1 = TimeGreeting()+", Monsieur Thibaut. Vim em nome de um homem que o senhor conhece. O nome dele é Capitão Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. E? Então?";
			link.l1 = "O capitão Martene solicita a sua presença imediatamente na Praia do Olho de Peixe. Mas não sozinho. Ele também gostaria que Molly Jones o acompanhasse. Você entende o que quero dizer?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Infelizmente, senhor, não sei.";
			link.l1 = "That's what I was expecting you to say. Of course, I doubt you could have previously been introduced to Colonel Fox's daughter; you know Colonel Fox, of course, commander of the notorious Sea Foxes... the terror of England's enemies in the Caribbean? You and Robert have stirred up such a hornet's nest it's a miracle you haven't been stung yet! The girl Molly Jones that you captured from the English brig, that you've been concealing from Levasseur, is the daughter of Colonel Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "O-o quê?";
			link.l1 = "Você ficou bem pálido, senhor. Agora me escute com atenção, Henry, e preste atenção: você e seu parceiro Robert estão encrencados até o pescoço. A qualquer momento, o esquadrão naval de Cromwell vai chegar ao Caribe. Eles vão caçar vocês. Só a nau capitânia deles é capaz de transformar seu tão falado La Roche e a tripulação em lascas e carne moída em poucas horas. O que acha? Valeu a pena atacar aquele brigue inglês e sequestrar a filha do Fox?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Mas isso não é tudo. Suas tramas já não são segredo só para mim. Seu querido tio, o governador, vai descobrir que você desobedeceu suas ordens rígidas e escondeu dele uma moça que o velho tarado certamente gostaria de tomar para si. O que acha, Henry? O que seu tio vai fazer com você? Você deve saber melhor do que ninguém como é explosivo o temperamento dele...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Tudo mentira!";
			link.l1 = "É mesmo? Meu caro Henry, pode perguntar ao seu amigo Martene. Foi ele quem me enviou. Levasseur vai descobrir que você está escondendo a moça antes do pôr do sol. Não me pergunte como o Robert soube disso, apenas escute o que eu digo: ele está apavorado e pronto para levantar âncora e zarpar imediatamente. Ele nem teve coragem de entrar na cidade. Por isso pediu que eu trouxesse este recado para você.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene não vai te esperar por mais de duas horas. Ele preza muito a própria cabeça. Só está na costa de Tortuga ainda por consideração à sua amizade, em vez de se esconder com os holandeses. Mas aquele pobre Robert nem imagina quem é a verdadeira Molly Jones. Sabe, vocês dois realmente me surpreendem com essa incrível ignorância sobre moda e aparência feminina! Não conseguem nem distinguir uma dama de sua criada!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "O que você quer?";
			link.l1 = "Finalmente, algumas palavras sensatas desse jovem atrevido! Muito bem, Thibaut: vá até onde está escondendo ela agora, pegue-a delicadamente pelas mãos alvas como lírios, e leve-a depressa até a Praia do Olho-de-Peixe, onde está o Voltigeur do Martene. Diga a ele que seus planos mudaram...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene deve cumprir a promessa que fez a mim, ele nem deve pensar em levar a garota para o próprio navio. Ela vai ficar na praia e me esperar. Diga ao Robert que, se ele não cumprir com as obrigações dele, ou levar a Catherine, ou se um fio de cabelo cair da cabecinha dela, eu vou passar o resto da vida procurando por ela. E quando eu encontrá-la, vou entregá-la ao Coronel Fox... viva. Mas quanto a vocês dois... eu trago de volta em pedaços. Ah, e isso vale pra você também, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Quem eu sou e quais são as minhas oportunidades, pode perguntar ao Robert. Ele sabe muito bem. Se vocês dois fizerem o que eu mandar, todos saímos ganhando. Robert vai poder continuar com seus negócios de pirata e você mantém todos os seus privilégios e ainda recebe a herança do seu querido tio quando ele bater as botas. Quanto a mim... também não saio perdendo. Está tudo claro?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Prefiro queimar no fogo eterno do inferno do que obedecer às suas ordens... "+GetFullName(pchar)+"!   Como é que eu não te reconheci logo de cara? Seu carniceiro! Você não pretende deixar nem a mim nem ao Robert vivos! Seus 'métodos' são bem conhecidos! De jeito nenhum vou entregar a Molly... ou a Catherine, aliás, pra um lixo como você! Você não vai sair vivo de Tortuga, desgraçado!";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Pare, covarde!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Finalmente, hein! Capitão "+GetFullName(pchar)+", fico muito feliz que você tenha vindo. Entre, sente-se. Gostaria de beber alguma coisa? Tenho uma proposta de negócio bastante lucrativa para você, meu amigo...";
			link.l1 = " Ora, vejo que está de ótimo humor hoje, Monsieur Thibaut... Nada de enrolação. Vamos direto ao ponto.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "A proposta diz respeito ao meu antigo amigo e companheiro, que você conhece como Robert Martene, ex-capitão do galeão 'Voltigeur'...";
			link.l1 = "Então, você e o Robert não são mais amigos? Que interessante.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Capitão, por favor, ouça meus motivos para pedir sua ajuda e tudo ficará claro. Como você sabe, Martene abordou um brigue inglês e fez prisioneira uma inglesa, uma criada chamada Molly Jones, que é justamente a razão de toda essa confusão.";
			link.l1 = "Claro, eu sei. Pelo que entendi, você seguiu minhas recomendações e trouxe a garota para o navio do Martene?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Sim, fui eu. Mas me arrependo disso todos os dias. Saiba que a Molly é uma moça encantadora e linda, nunca conheci ninguém como ela. Preciso admitir, me apaixonei por ela. E ela também gostava de mim, disse isso com todas as letras! Eu não podia deixar meu tio ficar com ela. Quando a escoltei até o 'Voltigeur', pensei que meu tio ia sossegar assim que percebesse que ninguém estava escondendo moças dele, aquele velho tarado. Depois, o Robert a levaria de volta para Tortuga, e eu poderia levá-la para minha casa sem riscos. Esse era o acordo que fiz com Martene. Mas as coisas saíram de outro jeito. Quando soube que meu tio tinha sido morto, não fazia mais sentido esconder a Molly, então esperei pacientemente o 'Voltigeur' chegar com ela a bordo.";
			link.l1 = "Ela chegou?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Sim. Infelizmente, a Molly não estava no navio. O Robert ficou abalado, como se tivesse encarado o próprio Lúcifer. Durante sua breve expedição, ele acabou descobrindo um detalhe terrível: a garota, Molly, não era Molly Jones coisa nenhuma, mas sim Catherine Fox! Filha do próprio coronel Fox, comandante dos Sea Foxes, o regimento de elite dos fuzileiros ingleses! Você sabe o que isso significa!";
			link.l1 = "Maldição, veja só! Então, sem dúvida, Robert tem mesmo motivos para temer. Mas como é que isso pôde acontecer?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Quando Catherine foi capturada, ela escondeu sua identidade de propósito, fingindo ser Molly Jones, uma criada que morreu durante o ataque ao navio. Ela tinha medo de que Martene descobrisse quem ela realmente era. E conseguiu enganá-lo. Mas, na última viagem, Robert de alguma forma descobriu a verdade sobre ela. Ele disse que tinha encontrado algumas cartas ou documentos dela...";
			link.l1 = "E onde está a garota agora, se ela não embarcou no 'Voltigeur'?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Ela está morta. Assustada com a punição iminente de Fox por atacar o brigue inglês, Martene decidiu se livrar da única prova restante jogando-a na água. Ela era a última testemunha do ataque dele ao 'Albatross'.";
			link.l1 = "Então ele bem que poderia ter matado todos os marinheiros dele... Igual ao Fernand Luc. Do contrário, um dia eles vão se embebedar e acabar falando demais na taverna...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Ele acredita que toda a tripulação dele é ligada a ele pelo sangue. Talvez ele esteja certo, em parte. Mas eu conheço o Coronel Fox! Ele vai continuar procurando até o último dia de vida para descobrir quem sequestrou a filha dele!";
			link.l1 = "Eu não duvido disso. Principalmente depois que um pirata francês matou a esposa dele. Agora a filha também... Aliás, tem mesmo certeza, monsieur, de que Catherine está realmente morta? Talvez o Robert a tenha escondido de você em algum lugar.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Tenho certeza. Conversei com um marinheiro do 'Voltigeur'. Acreditei nele. Ele viu com os próprios olhos quando cortaram a garganta da moça, depois amarraram uma bala de canhão nos pés dela e a jogaram ao mar.";
			link.l1 = "Deus do céu! Aquela pobre mulher... o que você quer de mim, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Não consigo dormir à noite desde aquele dia. Vejo Molly diante dos meus olhos o tempo todo... Ou melhor, Catherine. Fui eu quem a levou para a morte, "+GetFullName(pchar)+"!   Eu não consigo me perdoar por isso.   Além disso, não me iludo com o Fox.   Aquele homem não é complacente e duvido que ele sequer durma.   Mais cedo ou mais tarde, ele vai acabar encontrando o rastro do Martene, fazer alguém falar, e quando descobrir quem matou a filha dele, o inferno vai se soltar.   Vai sobrar pra todo mundo que esteve envolvido nessa história.";
			link.l1 = "Isso me inclui.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Sim, eu também. É por isso que quero que você encontre Martene antes do Fox. Ache aquele desgraçado e mate-o. E faça ele sofrer antes, se puder. Pela pobre Catherine. Quando terminar, corte aquele anel gordo que ele usa na mão junto com o dedo e traga para mim como prova\nConheço bem o dedo torto dele e aquele anel. Se fizer isso, vou te pagar um quarto de milhão em prata.";
			link.l1 = "Parece que você recebeu uma bela herança do seu querido tio, que descanse em paz, hein? Me diga, Henry, por que decidiu me pedir ajuda com esse assunto?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Porque eu também aprendi algumas coisas sobre você, "+GetFullName(pchar)+". Foi fácil, você é um homem famoso. Ninguém sabe ao certo para quem você realmente trabalha, se é para de Poincy, para os holandeses, para os ingleses ou para o Barão Jan Svenson... Mas uma coisa é certa: você aceita trabalhos delicados, discretos, e sempre cumpre o que promete. Depois, recebe muito bem por isso. E o melhor de tudo, não tem ligação com os espanhóis. Afinal, você também esteve envolvido nos acontecimentos que me fizeram herdar a fortuna do meu tio. Não negue... Um quarto de milhão é uma bela quantia. Eu vou lhe dizer onde encontrar Martene. Só precisa interceptar o navio dele e subir a bordo.";
			link.l1 = "Mais cem mil e eu resolvo o Martene pra você.";
			link.l1.go = "tibo_34";
			link.l2 = "Lamento, Monsieur Thibaut, mas você terá que resolver seu problema com Martene e o Coronel Fox sem a minha participação. Da minha parte, prometo que não enviarei nenhuma notícia ao coronel sobre o destino de sua filha e daqueles que são culpados por sua morte. Tudo de bom, senhor.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Senhor, pelo amor de Deus... Eu não tenho milhões guardados em baús de tesouro, acredite! Eu entendo que seus serviços custam caro, por isso já ofereci duzentos e cinquenta mil de imediato... Tudo bem... Certo, que tal se eu acrescentar mais cinquenta mil em ouro. Não posso te oferecer mais nada!";
			link.l1 = "Certo. Temos um acordo. Onde foi a última vez que você viu Martene?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Ele navegou para o sul até a Costa Espanhola em Caracas e conseguiu uma audiência com Don Diego Francisco de Kerres, o governador. Parece que ele o subornou de alguma forma, porque Don Diego concedeu a Robert a proteção da coroa espanhola. Ele vendeu o 'Voltigeur' e agora é o capitão do pesado galeão 'Infanta'. Ele devia ter uma boa reserva de dinheiro, já que conseguiu subornar o governador e ainda comprar e equipar um navio de guerra desse porte\nEntão, o próximo passo dele será zarpar de Caracas para Santo Domingo em seu novo navio, como parte de um esquadrão espanhol. Isso foi tudo que meu informante conseguiu descobrir. A única chance de pegar Martene é alcançar esse esquadrão espanhol\nSe eles chegarem a Santo Domingo, acabou. Não faço ideia de onde Robert irá depois. Ele vai sumir como um coelho no seu buraco e nunca mais vamos encontrá-lo.";
			link.l1 = "Entendi. Vou interceptá-los.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "E não se esqueça do dedo com o anel! Essa é uma condição essencial do nosso acordo! Quero ter absoluta certeza de que Robert está morto!";
			link.l1 = "Certo. Não vamos perder tempo, vou zarpar imediatamente!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "O Martene ainda está empesteando o Caribe com a presença dele, capitão?";
			link.l1 = "Ele não tem muito tempo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "O Martene está empesteando o Caribe com a presença dele, capitão?";
			link.l1 = "Não mais. Você não precisa mais temer o Coronel Fox, e sua Catherine foi vingada. Aqui está a prova.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Sim... Esse é mesmo o dedo do Martene, sem dúvida. Você nunca deixa de me surpreender, Capitão "+GetFullName(pchar)+"! Você realmente merece a reputação que conquistou.";
			link.l1 = "Vamos direto ao pagamento, certo, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Está tudo pronto. Aqui, pegue sua recompensa.";
			link.l1 = "Minha gratidão. Fico feliz que você tenha conseguido preparar isso com antecedência. Bem, Henry, espero que você não se meta em mais encrencas como essa e que escolha amigos melhores no futuro. Tudo de bom!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Obrigado pela sua ajuda, capitão! Vou recomendar você a todos os meus amigos. Boa sorte!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Sim, monsieur "+GetFullName(pchar)+"? Você tem algum assunto comigo?";
			link.l1 = "Não, Monsieur Thibaut. Só decidi passar aqui por um instante. Adeus!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ah, "+GetFullName(pchar)+"...Vamos, o que está te demorando tanto! Agora, quem diabos sabe onde está o Robert Martene?! Se o Coronel Fox descobrir tudo, acho que vou estar encrencado até o pescoço...";
			link.l1 = "Entendo. Cheguei tarde demais. Me desculpe, Monsieur Thibaut, mas fui atrasado por assuntos realmente urgentes. Não vou tomar mais do seu tempo. Adeus.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "O que você quer, "+GetFullName(pchar)+"? Não tenho tempo para conversar. Tenho coisas mais importantes para resolver. Preciso encontrar Martene antes que Fox o faça...";
			link.l1 = "Sim, sim. Já estou indo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Você é o Capitão "+GetFullName(pchar)+"?";
			link.l1 = "Você veio falar com a pessoa certa, amigo. Estou todo ouvidos.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Seu devedor pediu para avisar que o serviço está feito e o peixe vai cair na rede em menos de uma hora. Então, apresse-se.";
			link.l1 = "Entendi. Obrigado!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Que diabos você está fazendo aqui? Quem é você? Responda agora!";
			link.l1 = "Quem diabos é você e por que está me fazendo perguntas tão idiotas?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "O quê?! Seu fedelho insolente! Quem sou eu? Eu sou o governador desta ilha, François Levasseur, Senhor de Renet de Boidouflet de Lettre! E tudo nesta ilha está sob minha jurisdição! Isso inclui você enquanto estiver no meu território, moleque!";
			link.l1 = "Então, então... O próprio lobo mau, hein? Você está um pouco perdido, Levasseur, Senhor de Renet de seja lá o que for. Seu tempo acabou. Por ordem do Governador-Geral François Longvilliers de Poincy, você foi destituído do seu cargo e condenado à morte imediata! Eu sou seu juiz e seu carrasco ao mesmo tempo! Últimas palavras?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Acho que você não vai desistir, e me pedir misericórdia não vai adiantar, então vamos lá, saque sua espada!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Maldição! É um agente do de Poincy! Saquem as espadas! Matem ele!";
			link.l1 = "Vamos dançar.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "O que diabos você está fazendo aqui? Quem é você? Responda, agora!";
			link.l1 = "Olha só! Essa eu não esperava... Monsieur Levasseur em pessoa, presumo?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Sim, eu sou o governador desta ilha, François Levasseur, Senhor de Renet de Boidouflet de Lettre! E tudo nesta ilha está sob minha jurisdição! Isso inclui você enquanto pisa no meu território, seu canalha! Responda às perguntas! Sargento, tranque esta porta. Este homem está tramando alguma coisa!";
			link.l1 = "Você é incrivelmente perspicaz, monsieur Levasseur, Senhor de Renet de seja-lá-o-que-for. Minha presença aqui não vai lhe agradar. Por ordem do Governador-Geral François Longvilliers de Poincy, você foi destituído do seu cargo e condenado à morte imediata! Eu sou seu juiz e seu carrasco ao mesmo tempo!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Imagino que você não vai desistir, e me pedir misericórdia não vai adiantar, então vamos lá, saque sua espada! Você é só meu trabalho, nada pessoal. Só estou servindo à Coroa, ha! Sargento, não aconselho que se meta enquanto cumpro as ordens do governador-geral!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Não escute ele, sargento! Ele é um agente espanhol! Matem ele! Guardas, ajudem! Tem espanhóis aqui!";
			link.l1 = "Na verdade, nunca estive na Espanha, só em Narbonne.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Ai! Socorro! Soldados!";
			link.l1 = "Fique quieto, seu idiota! Se você não gritar, eu não vou fazer nada com você!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Não me mate!";
			link.l1 = "Não seja ridículo! Um homem acabou de passar por aqui há dez minutos. Um nobre bem vestido. Onde ele está escondido? E nem pense em me dizer que não o viu!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Monsieur Thibaut?";
			link.l1 = "Então, você o conhece! Para onde ele foi? Vai responder, ou preciso sacudir sua cabeça pra ver se ela começa a funcionar?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Ah não, por favor, não me machuque! O senhor Thibaut fugiu, foi por ali em direção ao mar. E ele pulou do guindaste, direto na água. Ele provavelmente morreu, é muito alto...";
			link.l1 = "Não acho que sim. Ele não é do tipo que cometeria suicídio. Você deveria entrar. É perigoso ficar aqui fora esta noite.";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Ai! Ai! Não atire!";
			link.l1 = "O quê?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Quem é você? Veio me matar ou... fazer algo pior?";
			link.l1 = "Nada disso, madame. Vou levar você, Catherine Fox, de volta ao seu pai em St. John's. Se ele lhe der uma surra depois disso por desobedecer às ordens dele, aí minha culpa vai se repetir. Mas espero que o coronel fique feliz em ver a filha viva, apesar de toda a preocupação que ela lhe causou.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Graças a Deus! Só posso estar sonhando! Você não sabe quem eu sou? Você é francês e católico, e mesmo assim decidiu vir aqui me salvar das mãos dos meus próprios compatriotas? Arriscou a vida só pela filha do Coronel Fox?";
			link.l1 = "Meu motivo original para estar aqui em Tortuga era bem diferente. Mas eu também não podia deixar uma bela dama nas mãos de um bando de ladrões e salteadores.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Você é um verdadeiro cavalheiro! Qual é o seu nome, monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Capitão "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Me diga, capitão, você vai mesmo me levar até meu pai em St. John's?";
			link.l1 = "Sim, embora ele não goste muito de franceses. Bem, vou lembrar a ele que também há ingleses canalhas, inclusive oficiais ingleses! Eu mesmo fui testemunha de pelo menos um deles... Richard Fleetwood era o nome dele.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Se chegarmos a Antígua, farei de tudo para convencer meu pai de que há verdadeiros cavaleiros entre os franceses.";
			link.l1 = "Eu realmente agradeceria isso... Muito bem, espero que meus anjos da guarda tenham vigiado meu caminho pelos telhados da cidade e já estejam esperando nosso retorno.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Eu não acreditava que você realmente cumpriria sua promessa até agora! Tantas coisas terríveis e cruéis me aconteceram ultimamente... Agradeço a você, capitão, por restaurar minha fé nas pessoas e na cavalaria. Você deveria visitar meu pai quando puder!\nEle respeita homens como você. E não importa que você seja francês. Farei tudo o que puder para convencer meu pai a repensar sua opinião sobre sua nação.";
			link.l1 = "Obrigado, Catherine. Talvez eu aceite sua gentil oferta.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Espero mesmo que sim, capitão. Muito obrigada mais uma vez por tudo que fez por mim. Nunca vou esquecer.";
			link.l1 = "Vá, corra logo para o seu pai. Ele vai ficar feliz em te ver. Talvez já tenha voltado do campo. Bem, de qualquer forma, está na hora de eu ir. Adeus!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Aí está você, capitão! Você nos deixou preocupados demais! Correr daquele jeito pelos telhados e pular de uma altura dessas foi algo de tirar o fôlego! Deus é testemunha, achamos mesmo que você não ia conseguir... Bem-vindo de volta a bordo, capitão, o bote já está pronto!";
			link.l1 = "Ótimo. Catherine, venha comigo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Olá, monsieur. Você é o capitão "+GetFullName(pchar)+"?";
			link.l1 = "Sim, sou eu. O que está acontecendo?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Ufa, quase não consegui te alcançar... Vim até você a pedido de um cavalheiro que você conhece, chamado Henry Thibaut.";
			link.l1 = "Henry? E o que ele quer? Compartilhar a alegria de ter herdado tudo de repente, depois da morte do seu querido tio?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "O Monsieur Thibaut pediu com urgência que você o visite em sua mansão em Tortuga o quanto antes. Ele tem um trabalho muito bem pago para você. Também me pediu para mencionar um nome: Robert Martene. Isso deve despertar seu interesse.";
			link.l1 = "É mesmo? E o que fez o Henry pensar isso?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Além disso, se isso ainda não te convenceu a ir visitá-lo, ele também pediu que eu acrescentasse o seguinte: 'Robert Martene deve morrer'.";
			link.l1 = "Tá bom, tá bom... Agora a coisa ficou interessante. Dois amigos de fé acabam de brigar... Como você disse, vou tentar visitar o Henry quando tiver uma chance.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Monsieur Thibaut pediu que você não demore a fazer sua visita. 'O peixe vai escapar da rede em dez dias', foram as palavras exatas dele...";
			link.l1 = "Ele e Robert falam do mesmo jeito. Tudo bem, vou fazer uma visita ao Henry.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
