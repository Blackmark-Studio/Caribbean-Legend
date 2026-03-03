void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "O que você quer?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ei, beleza, que tal um ornamento requintado para a coleção da sua dama? Um verdadeiro tesouro! Pra você – olhares de admiração, e pra mim – algumas moedas pro pão e um gole de rum.";
			}
			else
			{
				dialog.text = "Ei, capitão, que tal um presente especial para sua dama? Um verdadeiro tesouro! Pra você – a gratidão calorosa dela, e pra mim – algumas moedas pro pão e um gole de rum.";
			}
			link.l1 = "Pra que daqui a uma hora os soldados venham me buscar e me joguem na prisão por roubo? Onde você conseguiu isso, vagabundo?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "Um presente requintado? E onde alguém como você, um sem-teto, conseguiria algo assim?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Capitão, eu","Eu")+" achei este pingente lindo com um camafeu, juro por tudo! Que eu afunde se estiver mentindo! Ele estava lá, largado, sem dono. Eu não podia simplesmente deixar uma beleza dessas jogada na lama, podia?";
			link.l1 = "Certo. Mostre o que você tem aí.";
			link.l1.go = "Poorman_3";
			link.l2 = "Quem acreditaria na palavra de um cavalheiro tão respeitável como você? Procure alguém mais ingênuo.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Capitão, eu","Eu")+" encontrei este pingente lindo com um camafeu, palavra de honra! Que eu afunde se estiver mentindo! Ele estava lá, largado, sem dono. Eu não podia simplesmente deixar tanta beleza jogada na lama, podia?";
			link.l1 = "Certo. Mostre o que você tem aí.";
			link.l1.go = "Poorman_3";
			link.l2 = "Quem acreditaria na palavra de um cavalheiro tão respeitável como você? Procure alguém mais ingênuo.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Olha... é uma coisa e tanto! Achei isso no canteiro de flores, perto daquela casa com a lanterna, perto da taverna. Mas faz tempo que ninguém aparece por lá, então não tem pra quem devolver.";
			link.l1 = "Curioso esse pequeno enfeite. E quanto você quer por ele?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Apenas cem pesos"+GetSexPhrase(", Cap","")+"... meros trocados para alguém como você! E para mim – uma semana inteira sem me preocupar de onde vai sair o pão. Olha só pra isso – que coisa linda!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Certo, aqui estão seus cem pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "Acho que vou deixar passar. Tente a sorte com outra pessoa.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Obrigado, "+GetAddress_Form(NPChar)+"! Agora a sorte com certeza vai sorrir pra você! Dá pra ver que você é uma boa pessoa.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-oh, quem veio nos visitar? Parece que você não errou a porta, querida... entre, entre! Tire a roupa, fique à vontade.";
				link.l1 = "Ora, ora... Quem temos aqui? Não são vocês os canalhas que deixaram aquele 'carinhoso' recado ameaçador para a Betsy?";
			}
			else
			{
				dialog.text = "E-e-e que tipo de lula é essa?! Entrou na porta errada, seu cabeça de bode? Cai fora daqui antes que eu te abra no meio!";
				link.l1 = "Ora, ora... Quem temos aqui? Não são vocês os mesmos idiotas que deixaram aquele belo recado ameaçador para a Betsy?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? Que se dane essa Betsy! O que me interessa mesmo é o que você está fazendo aqui, querida... Já que está aqui – não precisa sair correndo, vamos dar um jeito de te manter ocupada...";
			}
			else
			{
				dialog.text = "Que diabos, Betsy? Não desafie o destino, sua tola. Enquanto ainda pode sair andando – vá embora. Caso contrário, vamos ter que juntar seus pedaços e te levar embora num balde!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Socorro! Socorro, eu imploro!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "E aí está ela. Você está encrencado até o pescoço, amigo, e se não quiser que esse seja seu último erro, eu aconselho que a solte. Imediatamente.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Ouviu isso, Reggie? "+GetSexPhrase("Ele está","Ela está")+" até nos ameaçando. "+GetSexPhrase("Que sujeito arrogante","Que lixo arrogante")+". Ei, vamos mostrar "+GetSexPhrase("esse metido, quero ver de que cor são as tripas dele","esse metido vai aprender o que é dor de verdade")+".";
			link.l1 = "É problema seu.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Agora solte a garota. Ou vai acabar deitado ao lado do seu amigo.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Malditos cães! Vocês achavam que eu ia ficar calado?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "E você... Você não parece ser um deles. Quem é você?";
			link.l1 = "Capitão "+GetFullName(pchar)+", ao seu dispor.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "Então, eu te devo a minha vida?";
			link.l1 = "Parece que sim. Mas agora tem algo mais importante – quem são essas pessoas e no que você se meteu?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "Essas pessoas... Foram enviadas por um importante oficial inglês. Houve um tempo em que ele era muito próximo de mim... e agora, como pode ver, deseja a minha morte.";
			link.l1 = "Acho que estou começando a entender sua história. Você era amante dele, mas em algum momento decidiu que poderia usar isso a seu favor. Queria assustá-lo... contar para a família dele?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "Você está surpreendentemente perto"+GetSexPhrase(" para a verdade, bonitão"," para a verdade, gatinha")+"... e ao mesmo tempo muito distante disso. Se fosse esse o caso, eu já estaria morta agora. Sim, fui amante dele, mas nunca me passou pela cabeça criar dramas familiares\nTudo era muito mais complicado: um dia descobri que ele tinha arranjado um novo brinquedinho e decidiu se livrar de mim, me deixando de mãos vazias. Simplesmente me descartar como algo sem valor. Bem, não sou do tipo que sai de mãos abanando\nEntão peguei o que realmente tinha valor – papéis que poderiam arruinar a vida dele – e fugi para o Novo Mundo. E então propus um acordo: os segredos dele em troca da minha segurança e uma compensação generosa\nÉ por isso que ainda estou viva – eles precisam dos documentos. E eu não tinha pressa nenhuma em revelar onde estavam escondidos.";
			link.l1 = "Bem, você não é só bonita, mas também diabolicamente astuta. Jogou com ousadia, mas sejamos sinceros – esse jogo já saiu do seu controle. Talvez seja hora de pensar em outra opção, enquanto ainda há chance de sair dessa? Se te encontraram aqui, dificilmente vai conseguir se esconder em outro lugar. Mais cedo ou mais tarde, sua sorte vai acabar.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "O que você está sugerindo? Entregar os documentos para ele e ficar de mãos abanando? Depois de tudo que eu passei?";
			link.l1 = "Você entende que, para eles, você não passa de um problema a ser eliminado. Eles não vão parar até conseguirem o que querem. Mas você ainda tem uma escolha. Entregue os documentos para aquele idiota ali. Deixe que ele os leve ao chefe dele e diga que você desistiu dos seus planos e só quer que tudo isso acabe.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "Se essa é minha única chance... Tudo bem, estou pronta para arriscar. Sempre mantive os documentos comigo. Costurei eles no meu espartilho para não me separar deles nem por um instante. Espere, só um segundo...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Aqui, pegue. Estes são todos os documentos que eu tinha. Vai dizer algumas palavras de despedida para aquela criatura? Você sabe como ser convincente, não sabe?";
			link.l1 = "Acho que ele já aprendeu a lição principal. Agora só precisamos deixar claro para ele o que deve fazer.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Levante-se. E me escute com atenção, seu desgraçado. Aqui estão os documentos que você veio buscar. Leve-os para o seu patrão e diga a ele: se continuar mandando assassinos atrás da Betsy, eles vão acabar como seus amigos. Diga que ela está saindo da vida dele para sempre – e que ele não tem mais motivo para persegui-la. Que ele veja isso como um gesto dela para tentar a paz. Espero que ele tenha juízo suficiente para acabar com isso aqui. Entendeu tudo, ou preciso enfiar essa informação na sua cabeça?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "Eu entendi tudo, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Então caia fora daqui. E nem pense em ficar rondando – se eu te vir aqui de novo, não vai ter outra chance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Bem, "+GetSexPhrase("meu herói","minha fúria")+", acho que até esqueci de te agradecer... É que foi tanta emoção. Não é todo dia que a gente acaba prisioneiro, e depois recupera a liberdade graças a alguém tão corajoso "+GetSexPhrase("salvador","salvadora")+". Me diga, é um hábito seu – resgatar damas em apuros, ou eu que dei uma sorte danada?";
			link.l1 = "O que posso dizer, Betsy, tenho uma queda por entradas dramáticas e "+GetSexPhrase("belas damas","todo tipo de aventura")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "Meu nome é Miranda. Miranda Bell. Adotei o nome Betsy quando precisei sumir – vida nova, nome novo, você entende. Fugi da Europa tão depressa que só consegui pegar umas poucas moedas e algumas joias\nO resto provavelmente ficou com aqueles canalhas que estavam me caçando. Agora, em vez de recepções luxuosas e vestidos caros – um casebre miserável na periferia e trabalho numa taverna. Nunca imaginei que um dia estaria servindo rum em vez de saborear vinho em boa companhia...";
			link.l1 = "Mesmo com tudo isso, você parece alguém que tem o destino nas mãos. Talvez seja aí que está seu verdadeiro talento.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Puxa-saco. Mas, sabe, combina com você","Você me lisonjeia")+"... Depois de tudo isso, estou me sentindo meio inquieto. E se eles já estiverem me esperando na próxima esquina? Me acompanhe até em casa, seja meu "+GetSexPhrase("salvador","savioress")+" por mais um tempinho. ";
			link.l1 = "Não sou de deixar as coisas pela metade. Então, senhora, estou ao seu dispor. Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Aqui estamos. Sabe, eu nem perguntei o que te trouxe àquela casa?";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "Eu não estava lá por acaso. Este pingente me levou até lá. Fique com ele.​ O dono da taverna parecia realmente preocupado com o seu desaparecimento e me pediu para descobrir o que aconteceu. Bem, eu tinha escolha de recusar? Abandonar uma dama em apuros é um ato indigno de um capitão.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
			else
			{
			link.l1 = "Eu não estava lá por acaso. O dono da taverna parecia realmente preocupado com o seu desaparecimento e me pediu para descobrir o que aconteceu. Bem, eu tinha escolha de recusar? Abandonar uma dama em apuros é um ato indigno de um capitão.";
			link.l1.go = "BetsiPrice_12";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, isso é tão nobre, Capitão "+pchar.name+"! Embora eu tenha certeza de que o dono da taverna estava mais preocupado com os lucros dele do que comigo. Infelizmente, hoje não posso te convidar para entrar – preciso me recuperar. O tempo que passei no porão não me deixou mais bonita, não. Mas se a gente não se encontrar de novo – não vou te perdoar por isso. Então venha à taverna amanhã, vou ter um... presente pra você.";
			link.l1 = "Bem, agora tenho mais um motivo para passar aqui. Até logo, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, isso é tão nobre, Capitão "+pchar.name+"! Embora eu tenha certeza de que o dono da taverna estava mais preocupado com os lucros dele do que comigo. Infelizmente, hoje não posso te convidar para entrar – preciso me recuperar. O tempo que passei no porão não me deixou mais bonita, não. Mas se a gente não se encontrar de novo – isso eu não vou te perdoar. Então venha à taverna amanhã, vou ter um... presente para você.";
			link.l1 = "Bem, agora tenho mais um motivo para passar aqui. Até logo, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Ora, ora... Que despedida mais doce. Quem é essa dama desgrenhada? Parece que ficou trancada num porão por uma semana, mas nem isso te impediu de devorá-la com os olhos, não é, "+pchar.name+"?";
			link.l1 = "Não é o que você pensa. A moça se meteu numa situação difícil, e eu só a ajudei a sair dela. Só isso.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "E você, claro, decidiu virar o cavaleiro de armadura reluzente dela?";
			link.l1 = "Sabe, não consigo ficar de braços cruzados quando alguém está em perigo.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Certo. Mas da próxima vez, "+pchar.name+", seja mais cuidadoso... e não me dê motivos para sentir ciúmes.";
			link.l1 = "Claro, querida. Vamos sair daqui, ainda temos muito o que fazer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Olha só... Que despedida mais doce. Tanto carinho, tantas promessas ternas... Você até chama ela pelo nome com tanto afeto, tá certo. Quem sabe eu também devesse sumir uns dias, pra ver se você me procuraria com a mesma vontade?";
			link.l1 = "Mary, você sabe que é meu talismã, e ela... é só uma garota que se meteu em encrenca.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ah, claro! Só uma pobrezinha precisando de um cavaleiro! E aquele seu olhar – foi só por educação também? Você quase despiu ela com os olhos!";
			link.l1 = "Mary, você está exagerando! Olha como eu olho pra você? Vê a diferença? Ou vou ter que te lembrar... de perto?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Certo, "+pchar.name+", desta vez você escapou dessa, tudo bem. Mas se eu vir uma cena dessas de novo...";
			link.l1 = "Então vou ter que te lembrar de novo quem ocupa o primeiro e único lugar no meu coração. Vamos, querido, ainda temos muito o que fazer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... Você não faz ideia dos pensamentos que passam pela minha cabeça quando estou tão perto de você... E o quanto eu quero transformar tudo isso em realidade.";
					link.l1 = "Então pare de só pensar nisso... e me mostre cada um deles.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, meu querido"+GetSexPhrase("","")+"... você não faz ideia do quanto é difícil pra mim me controlar quando você está por perto...";
					link.l1 = "Então chega dessa doce tortura... Vem pra mim...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("meu doce capitão","meu doce "+pchar.name+"")+"... ainda estou preso nessa doce loucura.";
					link.l1 = "Talvez essa loucura valha a pena ser lembrada... ou até repetida algum dia.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"... Se eu disser que foi incrível, você não vai ficar se achando demais"+GetSexPhrase(", vai?",". vai fazer isso?")+"?";
					link.l1 = "Só se você prometer dizer de novo... em um sussurro.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}